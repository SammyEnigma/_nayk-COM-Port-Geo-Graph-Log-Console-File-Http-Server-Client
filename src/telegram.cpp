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
    _callback = CallbackStruct();

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

    if(_requestObj.contains("callback_query")) {

        QJsonObject callback_query = _requestObj.value("callback_query").toObject();

        _callback.id = callback_query.value("id").toString("");
        _callback.chat_instance = callback_query.value("chat_instance").toString("");
        _callback.data = callback_query.value("data").toString("");

        if(callback_query.contains("from"))
            parseUserObject(callback_query.value("from").toObject(), _user);

        if(callback_query.contains("message")) {
            QJsonObject message = callback_query.value("message").toObject();
            _callback.from_msg_id = message.value("message_id").toVariant().toLongLong();

            if(message.contains("chat")) {
                parseChatObject(message.value("chat").toObject(), _chat);
            }
        }
    }
    else if(_requestObj.contains("message")) {
        QJsonObject message = _requestObj.value("message").toObject();
        _msg.type = Msg_Text;

        if(message.contains("chat")) {

            QJsonObject chatObj = message.value("chat").toObject();
            parseChatObject(chatObj, _chat);

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

            parseUserObject(message.value("from").toObject(), _user);
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

                parseUserObject(reply_message.value("from").toObject(), _reply_user);
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
bool Telegram::parseUserObject(const QJsonObject &obj, UserStruct &user)
{
    user = UserStruct();

    if(obj.contains("first_name") && user.firstName.isEmpty()) {
        user.firstName = obj.value("first_name").toString();
    }
    if(obj.contains("last_name") && user.lastName.isEmpty()) {
        user.firstName = obj.value("last_name").toString();
    }
    if(obj.contains("username") && user.name.isEmpty()) {
        user.name = obj.value("username").toString();
    }
    if(obj.contains("is_bot") && obj.value("is_bot").toBool()) {
        user.type = User_Bot;
    }
    if(obj.contains("id")) {
        user.id = obj.value("id").toVariant().toLongLong();
    }

    return true;
}
//==================================================================================================
bool Telegram::parseChatObject(const QJsonObject &obj, ChatStruct &chat)
{
    chat = ChatStruct();

    chat.id = obj.value("id").toVariant().toLongLong();
    if(obj.contains("type")) {
        QString typeStr = obj.value("type").toString();
        if(typeStr == "private") {
            chat.type = Chat_Private;
        }
        else if(typeStr == "group") {
            chat.type = Chat_Group;
        }
        else if(typeStr == "supergroup") {
            chat.type = Chat_Supergroup;
        }
        else if(typeStr == "channel") {
            chat.type = Chat_Channel;
        }
    }
    if(obj.contains("title")) {
        chat.title = obj.value("title").toString();
    }

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
bool Telegram::sendMessage(qint64 chatId, const MsgStruct &message)
{
    return sendMessage(chatId, message.text);
}
//==================================================================================================
bool Telegram::sendMessage(const MsgStruct &message)
{
    return sendMessage(_chat.id, message);
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
bool Telegram::sendChatAction(qint64 chat_id, const QString &action)
{
    if(chat_id == 0) {

        emit toLog(LogError, "Не определен chatId");
        return false;
    }

    QString url = telegram_api_url + "bot" + _token + "/sendChatAction";
    QJsonObject obj;
    obj["chat_id"] = chat_id;
    obj["action"] = action;

    return sendToTelegram(url, obj);
}
//==================================================================================================
bool Telegram::sendChatAction(const QString &action)
{
    return sendChatAction(_chat.id, action);
}
//==================================================================================================
bool Telegram::sendChatActionTyping(qint64 chat_id)
{
    return sendChatAction(chat_id, "typing");
}
//==================================================================================================
bool Telegram::sendChatActionTyping()
{
    return sendChatActionTyping(_chat.id);
}
//==================================================================================================
bool Telegram::sendChatActionDocument(qint64 chat_id, DocType docType)
{
    QString action = "typing";
    switch (docType) {
    case Doc_Audio:
        action = "upload_audio";
        break;
    case Doc_Video:
        action = "upload_video";
        break;
    case Doc_Photo:
        action = "upload_photo";
        break;
    case Doc_Document:
        action = "upload_document";
        break;
    default:
        break;
    }
    return sendChatAction(chat_id, action);
}
//==================================================================================================
bool Telegram::sendChatActionDocument(DocType docType)
{
    return sendChatActionDocument(_chat.id, docType);
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
//==================================================================================================
bool Telegram::sendPhoto(qint64 chatId, const PhotoStruct &photo)
{
    return sendPhoto(chatId, photo.file_id, photo.caption);
}
//==================================================================================================
bool Telegram::sendPhoto(const PhotoStruct &photo)
{
    return sendPhoto(_chat.id, photo);
}
//==================================================================================================
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
bool Telegram::sendDocument(qint64 chatId, const DocumentStruct &document)
{
    return sendDocument(chatId, document.file_id, document.caption, document.docType);
}
//==================================================================================================
bool Telegram::sendDocument(const DocumentStruct &document)
{
    return sendDocument(_chat.id, document);
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
bool Telegram::deleteMessage(qint64 message_id)
{
    return deleteMessage(_chat.id, message_id);
}
//==================================================================================================
bool Telegram::deleteMessage(qint64 chat_id, qint64 message_id)
{
    if(chat_id == 0) {

        emit toLog(LogError, "Не определен chat_id");
        return false;
    }

    QString url = telegram_api_url + "bot" + _token + "/deleteMessage";
    QJsonObject obj;
    obj["chat_id"] = chat_id;
    obj["message_id"] = message_id;

    return sendToTelegram(url, obj);
}
//==================================================================================================
bool Telegram::deleteMessage(const QString &user_name, qint64 message_id)
{
    if(user_name.isEmpty()) {

        emit toLog(LogError, "Не определен user_name");
        return false;
    }

    QString url = telegram_api_url + "bot" + _token + "/deleteMessage";
    QJsonObject obj;
    obj["chat_id"] = "@" + user_name;
    obj["message_id"] = message_id;

    return sendToTelegram(url, obj);
}
//==================================================================================================
QString Telegram::getChatTypeText(ChatType chatType)
{
    switch (chatType) {
    case Chat_Private: return "Private";
    case Chat_Group: return "Group";
    case Chat_Supergroup: return "Supergroup";
    case Chat_Channel: return "Channel";
    default:
        break;
    }
    return "Unknown";
}
//==================================================================================================
} // namespace
