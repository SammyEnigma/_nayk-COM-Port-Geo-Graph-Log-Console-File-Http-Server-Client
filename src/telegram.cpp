/****************************************************************************
** Copyright (c) 2019 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
** All right reserved.
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
** NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
** LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
** OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QUrl>
//
#include "Convert"
#include "SysUtils"
#include "HttpServer"
//
#include "telegram.h"
//==================================================================================================
namespace nayk {

//==================================================================================================
Telegram::Telegram(QObject *parent, const QString &token, const QString &name) : QObject(parent)
{
    setToken(token);
    setName(name);
    http = new HttpClient(this);
}
//==================================================================================================
Telegram::~Telegram()
{
    if(http) delete http;
}
//==================================================================================================
void Telegram::setToken(const QString &token)
{
    _token = token;
    emit toLog(LogDbg, QString("Установка токена: %1").arg(_token));
}
//==================================================================================================
void Telegram::setName(const QString &name)
{
    _name = name;
    emit toLog(LogDbg, QString("Установка имени: %1").arg(_name));
}
//==================================================================================================
bool Telegram::readRequest()
{
    _requestObj = QJsonObject();
    _chat = ChatStruct();
    _user = UserStruct();
    _msg = MsgStruct();
    _photo = PhotoStruct();
    _document = DocumentStruct();
    _update_id = 0;
    _is_reply = false;
    _reply_user = UserStruct();
    _reply_msg = MsgStruct();

    HttpServer *server = new HttpServer(this);
    server->setDbgLogging(true);
    connect(server, &HttpServer::toLog, this, &Telegram::toLog);

    bool ok = false;

    server->readRequest(&ok);
    if(ok) {

        QJsonParseError err;
        QJsonDocument doc = QJsonDocument::fromJson( server->requestContent(), &err );
        if(err.error == QJsonParseError::NoError) {

            _requestObj = doc.object();
        }
        else {
            _lastError = err.errorString();
            ok = false;
        }
    }
    else {
        _lastError = server->lastError();
    }

    if(ok) {
        ok = parseRequest();
    }
    else {
        emit toLog(LogError, _lastError);
    }

    QJsonObject obj;
    obj["ok"] = true;
    bool respOk;
    server->setResponseContentType( ContentTypeJSON );
    server->setResponseContent( QJsonDocument(obj).toJson(QJsonDocument::Compact) );
    server->writeResponse(&respOk);
    if(!respOk) {
        emit toLog(LogError, server->lastError());
    }

    delete server;
    return ok;
}
//==================================================================================================
bool Telegram::parseRequest()
{
    emit toLog(LogDbg, "Разбор Json запроса.");

    _update_id = _requestObj.value("update_id").toVariant().toLongLong();

    if(_requestObj.contains("message")) {
        QJsonObject message = _requestObj.value("message").toObject();
        _msg.type = Msg_Text;

        if(message.contains("chat")) {

            QJsonObject chatObj = message.value("chat").toObject();
            _chat.id = chatObj.value("id").toVariant().toLongLong();
            if(chatObj.contains("type")) {
                QString typeStr = chatObj.value("type").toString();
                if(typeStr == "private") {
                    _chat.type = Chat_Private;
                }
                else if(typeStr == "group") {
                    _chat.type = Chat_Group;
                }
                else if(typeStr == "supergroup") {
                    _chat.type = Chat_Supergroup;
                }
                else if(typeStr == "channel") {
                    _chat.type = Chat_Channel;
                }
            }
            if(chatObj.contains("title")) {
                _chat.title = chatObj.value("title").toString();
            }
            if(chatObj.contains("first_name")) {
                _user.firstName = chatObj.value("first_name").toString();
            }
            if(chatObj.contains("last_name")) {
                _user.lastName = chatObj.value("last_name").toString();
            }
            if(chatObj.contains("username")) {
                _user.name = chatObj.value("username").toString();
            }
        }

        if(message.contains("from")) {

            QJsonObject from = message.value("from").toObject();
            if(from.contains("first_name") && _user.firstName.isEmpty()) {
                _user.firstName = from.value("first_name").toString();
            }
            if(from.contains("last_name") && _user.lastName.isEmpty()) {
                _user.firstName = from.value("last_name").toString();
            }
            if(from.contains("username") && _user.name.isEmpty()) {
                _user.name = from.value("username").toString();
            }
            if(from.contains("is_bot") && from.value("is_bot").toBool()) {
                _user.type = User_Bot;
            }
            if(from.contains("id")) {
                _user.id = from.value("id").toVariant().toLongLong();
            }
        }
        if(message.contains("date")) {

            _msg.date = QDateTime::fromSecsSinceEpoch( message.value("date").toVariant().toLongLong(), QTimeZone(0) );
            emit toLog(LogDbg, "Message Date = " + _msg.date.toString("yyyy-MM-dd HH:mm:ss.zzz"));

        }
        if(message.contains("text")) {

            _msg.text = message.value("text").toString();
        }
        if(message.contains("message_id")) {

            _msg.id = message.value("message_id").toVariant().toLongLong();
        }
        if(message.contains("photo") && message.value("photo").isArray()) {
            QJsonArray photoArr = message.value("photo").toArray();
            for(int i=0; i<photoArr.size(); i++) {
                if(!photoArr.at(i).isObject()) continue;
                QJsonObject photoObj = photoArr.at(i).toObject();
                if( (photoObj.value("width").toInt() > _photo.width) && (photoObj.value("height").toInt() > _photo.height)) {
                    _photo.width = photoObj.value("width").toInt();
                    _photo.height = photoObj.value("height").toInt();
                    _photo.file_size = photoObj.value("file_size").toVariant().toLongLong();
                    _photo.file_id = photoObj.value("file_id").toString("");
                }
            }
            _photo.caption = message.value("caption").toString("");

            if(!_photo.file_id.isEmpty()) {
                _document.caption = _photo.caption;
                _document.docType = Doc_Photo;
                _document.file_id = _photo.file_id;
            }
        }
        if(message.contains("document") && message.value("document").isObject()) {
            QJsonObject docObj = message.value("document").toObject();
            _document.caption = message.value("caption").toString("");
            _document.docType = Doc_Document;
            _document.file_id = docObj.value("file_id").toString("");
        }
        if(message.contains("audio") && message.value("audio").isObject()) {
            QJsonObject docObj = message.value("audio").toObject();
            _document.caption = message.value("caption").toString("");
            _document.docType = Doc_Audio;
            _document.file_id = docObj.value("file_id").toString("");
        }
        if(message.contains("video") && message.value("video").isObject()) {
            QJsonObject docObj = message.value("video").toObject();
            _document.caption = message.value("caption").toString("");
            _document.docType = Doc_Video;
            _document.file_id = docObj.value("file_id").toString("");
        }

        if(message.contains("reply_to_message") && message.value("reply_to_message").isObject()) {
            _is_reply = true;
            QJsonObject reply_message = message.value("reply_to_message").toObject();
            if(reply_message.contains("from")) {

                QJsonObject from = reply_message.value("from").toObject();
                if(from.contains("first_name") && _reply_user.firstName.isEmpty()) {
                    _reply_user.firstName = from.value("first_name").toString();
                }
                if(from.contains("last_name") && _reply_user.lastName.isEmpty()) {
                    _reply_user.firstName = from.value("last_name").toString();
                }
                if(from.contains("username") && _reply_user.name.isEmpty()) {
                    _reply_user.name = from.value("username").toString();
                }
                if(from.contains("is_bot") && from.value("is_bot").toBool()) {
                    _reply_user.type = User_Bot;
                }
                if(from.contains("id")) {
                    _reply_user.id = from.value("id").toVariant().toLongLong();
                }
            }
            if(reply_message.contains("date")) {

                _reply_msg.date = QDateTime::fromSecsSinceEpoch( reply_message.value("date").toVariant().toLongLong(), QTimeZone(0) );
                emit toLog(LogDbg, "Reply Message Date = " + _reply_msg.date.toString("yyyy-MM-dd HH:mm:ss.zzz"));

            }
            if(reply_message.contains("text")) {

                _reply_msg.text = reply_message.value("text").toString();
            }
            if(reply_message.contains("message_id")) {

                _reply_msg.id = reply_message.value("message_id").toVariant().toLongLong();
            }
        }
    }

    if(!_photo.file_id.isEmpty() && (_photo.width > 0) && (_photo.height > 0)) _msg.type = Msg_Photo;
    else if(!_document.file_id.isEmpty()) _msg.type = Msg_Document;
    else if(!_msg.text.isEmpty() && (_msg.text.left(1) == "/")) _msg.type = Msg_Command;

    return true;
}
//==================================================================================================
bool Telegram::sendMessageMarkdown(const QString &text, const QJsonObject &replyMarkup)
{
    return sendMessageMarkdown(_chat.id, text, replyMarkup);
}
//==================================================================================================
bool Telegram::sendMessageMarkdown(qint64 chatId, const QString &text, const QJsonObject &replyMarkup)
{
    return sendMessage( chatId, text, "Markdown", replyMarkup );
}
//==================================================================================================
bool Telegram::sendMessageHTML(const QString &text, const QJsonObject &replyMarkup)
{
    return sendMessageHTML( _chat.id, text, replyMarkup );
}
//==================================================================================================
bool Telegram::sendMessageHTML(qint64 chatId, const QString &text, const QJsonObject &replyMarkup)
{
    return sendMessage( chatId, text, "HTML", replyMarkup );
}
//==================================================================================================
bool Telegram::sendMessage(const QString &text, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendMessage(_chat.id, text, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendMessage(qint64 chatId, const QString &text, const QString &parseMode, const QJsonObject &replyMarkup)
{
    if(chatId == 0) {

        emit toLog(LogError, "Не определен chatId");
        return false;
    }

    QString url = telegram_api_url + "bot" + _token + "/sendMessage";
    QJsonObject obj;
    obj["chat_id"] = chatId;
    obj["text"] = text;
    if(!parseMode.isEmpty()) obj["parse_mode"] = parseMode;
    if(!replyMarkup.isEmpty()) obj["reply_markup"] = replyMarkup;

    return sendToTelegram(url, obj);
}
//==================================================================================================
bool Telegram::sendPhotoFile(const QByteArray &data, const QString &caption, const QString &imgType )
{
    return sendPhotoFile( _chat.id, data, caption, imgType );
}
//==================================================================================================
bool Telegram::sendPhoto(qint64 chatId, const QString &file_id, const QString &caption, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendDocument(chatId, file_id, caption, Doc_Photo, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendPhoto(const QString &file_id, const QString &caption, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendPhoto(_chat.id, file_id, caption, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendPhotoHTML(qint64 chatId, const QString &file_id, const QString &caption, const QJsonObject &replyMarkup)
{
    return sendPhoto(chatId, file_id, caption, "HTML", replyMarkup);
}
//==================================================================================================
bool Telegram::sendPhotoHTML(const QString &file_id, const QString &caption, const QJsonObject &replyMarkup)
{
    return sendPhoto(file_id, caption, "HTML", replyMarkup);
}
//=========================================================================================
bool Telegram::sendPhotoFile(qint64 chatId, const QByteArray &data, const QString &caption, const QString &imgType )
{
    if(chatId == 0) {

        emit toLog(LogError, "Не определен chatId");
        return false;
    }

    QString url = telegram_api_url + "bot" + _token + "/sendPhoto?chat_id=" + QString::number(chatId);
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart captionPart;
    captionPart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    captionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"caption\""));
    captionPart.setBody(caption.toUtf8());

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/" + imgType));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"photo\"; filename=\"photo."+ imgType +"\""));
    imagePart.setRawHeader("Content-Transfer-Encoding", "binary");
    imagePart.setBody(data);

    multiPart->append(imagePart);
    multiPart->append(captionPart);

    return sendToTelegram(url, multiPart);
}
//==================================================================================================
bool Telegram::sendAudio(qint64 chatId, const QString &file_id, const QString &caption, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendDocument(chatId, file_id, caption, Doc_Audio, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendAudio(const QString &file_id, const QString &caption, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendAudio(_chat.id, file_id, caption, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendAudioHTML(qint64 chatId, const QString &file_id, const QString &caption, const QJsonObject &replyMarkup)
{
    return sendAudio(chatId, file_id, caption, "HTML", replyMarkup);
}
//==================================================================================================
bool Telegram::sendAudioHTML(const QString &file_id, const QString &caption, const QJsonObject &replyMarkup)
{
    return sendAudio(file_id, caption, "HTML", replyMarkup);
}
//==================================================================================================
bool Telegram::sendVideo(qint64 chatId, const QString &file_id, const QString &caption, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendDocument(chatId, file_id, caption, Doc_Video, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendVideo(const QString &file_id, const QString &caption, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendVideo(_chat.id, file_id, caption, parseMode, replyMarkup);
}
//==================================================================================================
bool Telegram::sendVideoHTML(qint64 chatId, const QString &file_id, const QString &caption, const QJsonObject &replyMarkup)
{
    return sendVideo(chatId, file_id, caption, "HTML", replyMarkup);
}
//==================================================================================================
bool Telegram::sendVideoHTML(const QString &file_id, const QString &caption, const QJsonObject &replyMarkup)
{
    return sendVideo(file_id, caption, "HTML", replyMarkup);
}
//==================================================================================================
bool Telegram::sendDocument(qint64 chatId, const QString &file_id, const QString &caption, DocType docType, const QString &parseMode, const QJsonObject &replyMarkup)
{
    if(chatId == 0) {

        emit toLog(LogError, "Не определен chatId");
        return false;
    }

    QString sendStr = "/sendDocument";
    QString keyName = "document";
    switch (docType) {
    case Doc_Photo:
        sendStr = "/sendPhoto";
        keyName = "photo";
        break;
    case Doc_Audio:
        sendStr = "/sendAudio";
        keyName = "audio";
        break;
    case Doc_Video:
        sendStr = "/sendVideo";
        keyName = "video";
        break;
    default:
        break;
    }

    QString url = telegram_api_url + "bot" + _token + sendStr;
    QJsonObject obj;
    obj["chat_id"] = chatId;
    obj[keyName] = file_id;
    if(!caption.isEmpty()) obj["caption"] = caption;
    if(!parseMode.isEmpty()) obj["parse_mode"] = parseMode;
    if(!replyMarkup.isEmpty()) obj["reply_markup"] = replyMarkup;

    return sendToTelegram(url, obj);
}
//==================================================================================================
bool Telegram::sendDocument(const QString &file_id, const QString &caption, DocType docType, const QString &parseMode, const QJsonObject &replyMarkup)
{
    return sendDocument(_chat.id, file_id, caption, docType, parseMode, replyMarkup);
}
//=========================================================================================
bool Telegram::sendDocumentHTML(qint64 chatId, const QString &file_id, const QString &caption, DocType docType, const QJsonObject &replyMarkup)
{
    return sendDocument(chatId, file_id, caption, docType, "HTML", replyMarkup);
}
//=========================================================================================
bool Telegram::sendDocumentHTML(const QString &file_id, const QString &caption, DocType docType, const QJsonObject &replyMarkup)
{
    return sendDocument(file_id, caption, docType, "HTML", replyMarkup);
}
//==================================================================================================
bool Telegram::sendToTelegram(const QString &url, const QJsonObject &obj)
{
    QJsonDocument doc(obj);
    emit toLog(LogDbg, QString("Отправка сообщения на сервер %1").arg(url));
    emit toLog(LogDbg, QString(doc.toJson()));

    http->setURL(url);
    http->setContentType(ContentTypeJSON);

    if(!http->sendRequest( doc.toJson(QJsonDocument::Compact) )) {

        emit toLog(LogError, http->lastError());
        return false;
    }

    QJsonParseError err;
    doc = QJsonDocument::fromJson( http->replyData(), &err );

    if(err.error != QJsonParseError::NoError) {

        emit toLog(LogError, err.errorString());
        return false;
    }

    if(doc.isNull() || !doc.isObject()) {

        emit toLog(LogError, "Ответ не объект Json");
        return false;
    }
    else {
        emit toLog(LogDbg, "Ответ:");
        emit toLog(LogDbg, QString(doc.toJson()));
    }
    return true;
}
//==================================================================================================
bool Telegram::sendToTelegram(const QString &url, QHttpMultiPart *multiPart)
{
    emit toLog(LogDbg, "Отправка сообщения.");

    http->setURL(url);
    if(!http->sendRequestMultipart( multiPart )) {

        multiPart->deleteLater();
        emit toLog(LogError, http->lastError());
        return false;
    }

    multiPart->deleteLater();

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson( http->replyData(), &err );

    if(err.error != QJsonParseError::NoError) {

        emit toLog(LogError, err.errorString());
        return false;
    }

    if(doc.isNull() || !doc.isObject()) {

        emit toLog(LogError, "Ответ не объект Json");
        return false;
    }
    else {
        emit toLog(LogDbg, "Ответ:");
        emit toLog(LogDbg, QString(doc.toJson()));
    }
    return true;
}
//==================================================================================================
QJsonObject Telegram::lastAnswer()
{
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson( http->replyData(), &err );

    if((err.error == QJsonParseError::NoError) && doc.isObject()) {

        return doc.object();
    }

    return QJsonObject();
}
//==================================================================================================
QString Telegram::userName()
{
    if(!_user.firstName.isEmpty()) return _user.firstName;
    if(!_user.name.isEmpty()) return _user.name;
    if(!_user.lastName.isEmpty()) return _user.lastName;
    return tr("User");
}
//==================================================================================================
} // namespace
