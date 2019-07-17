/****************************************************************************
** Copyright (c) 2018 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
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
#include <QCoreApplication>
#include <QDir>

#include "log.h"
#include "filesys.h"

namespace nayk {
//=======================================================================================================
const QString clLogDateDark       = "#929292";
const QString clLogDateLight      = "#333333";

const QString clLogPrefixDark     = "#c88dee";
const QString clLogPrefixLight    = "#562873";

const QString clLogInfDark        = "#ffffff";
const QString clLogInfLight       = "#000000";

const QString clLogWrnDark        = "#ff9c54";
const QString clLogWrnLight       = "#8d3c00";

const QString clLogErrDark        = "#ff4040";
const QString clLogErrLight       = "#a50000";

const QString clLogInDark         = "#55d864";
const QString clLogInLight        = "#003706";

const QString clLogOutDark        = "#dd69bb";
const QString clLogOutLight       = "#53003b";

const QString clLogTxtDark        = "#d8d8d8";
const QString clLogTxtLight       = "#1f1f1f";

const QString clLogDbgDark        = "#00ddc6";
const QString clLogDbgLight       = "#006766";

const QString clLogOtherDark      = "#8f8f8f";
const QString clLogOtherLight     = "#888888";

//=======================================================================================================
Log::Log(QObject *parent, QDateTime startTime, const QString &logDir, bool startLogging) : QObject(parent)
{
    startingTime = startTime.isValid() ? startTime : QDateTime::currentDateTime();
    logPath = QDir::toNativeSeparators( logDir.isEmpty() ? QDir::currentPath() : logDir );
    if (logPath.right(1) != QDir::separator())
        logPath += QDir::separator();
    logPath += startingTime.toString("yyyy") + QDir::separator()
            + startingTime.toString("MM") + QDir::separator()
            + startingTime.toString("dd") + QDir::separator();
    if (startLogging)
        startLog();
}
//=======================================================================================================
Log::~Log()
{
    if (file.isOpen()) {
        writeLastLine();
        file.close();
        emit closeFile(logPath + logFile);
    }
}
//=======================================================================================================
bool Log::startLog(const QString &fileName, bool saveDbg)
{
    _dbg = saveDbg;

    if(file.isOpen()) {
        _lastError = tr("Лог-файл уже открыт на запись.");
        return false;
    }
    if(fileName.isEmpty()) {
        logFile = startingTime.toString("HHmmsszzz");
        int n = 99;
        while ( (n>10) && FileSys::fileExists( logPath + logFile + QString::number(n,10) + ".log" ))
            n--;
        logFile += QString::number(n) + ".log";
    }
    else {
        logPath = FileSys::extractFilePath(fileName);
        logFile = FileSys::extractFileName(fileName);
    }
    if(!FileSys::makePath(logPath)) {
        _lastError = tr("Не удалось создать каталог для лог-файла.");
        return false;
    }

    file.setFileName(logPath + logFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        _lastError = tr("Не удалось создать лог-файл.");
        return false;
    }
    emit openFile(logPath + logFile);
    stream.setDevice(&file);
    return writeFirstLine();
}
//=======================================================================================================
bool Log::writeFirstLine()
{
    if(!file.isOpen()) {
        _lastError = tr("Лог-файл не открыт для записи.");
        return false;
    }

    QString logStr = tr("----- Начало работы -----");
    return write(LogInfo, logStr.leftJustified(100,'-'));
}
//=======================================================================================================
bool Log::writeLastLine()
{
    if(!file.isOpen()) {
        _lastError = tr("Лог-файл не открыт для записи.");
        return false;
    }

    QCoreApplication::processEvents();

    QDateTime now = (startingTime.offsetFromUtc() != 0) ? QDateTime::currentDateTime() : QDateTime::currentDateTimeUtc();
    qint64 n = now.toMSecsSinceEpoch() - startingTime.toMSecsSinceEpoch();
    QString logStr = tr("----- Окончание. Время работы: ") + QString::number(n) + tr(" мсек. -----");

    return write(LogInfo, logStr.leftJustified(100,'-'));
}
//=======================================================================================================
QString Log::getLogPrefix(LogType logType, const QDateTime &date)
{
    QString prefix = "[" + date.toString("HH:mm:ss.zzz") + "]";

    switch (logType) {
    case LogInfo:
        prefix += "[inf] ";
        break;
    case LogWarning:
        prefix += "[wrn] ";
        break;
    case LogError:
        prefix += "[err] ";
        break;
    case LogIn:
        prefix += "[<<<] ";
        break;
    case LogOut:
        prefix += "[>>>] ";
        break;
    case LogText:
        prefix += "[txt] ";
        break;
    case LogDbg:
        prefix += "[dbg] ";
        break;
    default:
        prefix = "";
        break;
    }
    return prefix;
}
//=======================================================================================================
bool Log::write(LogType logType, const QString &text)
{
    if(!file.isOpen()) {
        _lastError = tr("Лог-файл не открыт для записи.");
        return false;
    }

    QDateTime now = (startingTime.offsetFromUtc() != 0) ? QDateTime::currentDateTime() : QDateTime::currentDateTimeUtc();
    QString prefix = getLogPrefix(logType, now);
    QStringList sl = text.split("\n");
    for(int i=0; i<sl.size(); i++) {
        stream << prefix << QString(sl.at(i)) << "\n";
    }

    stream.flush();
    file.flush();
    if (stream.status() != QTextStream::Ok) {
        file.close();
        _lastError = tr("Ошибка при записи в лог-файл.");
        emit closeFile(logPath + logFile);
        return false;
    }
    return true;
}
//=======================================================================================================
QString Log::highlightLogString(LogFormat logFormat, QDateTime dateTime, LogType logType, const QString &text, bool darkBackground)
{
    QString prefix = getLogPrefix(logType, dateTime);
    QString res = "";
    QStringList sl = text.split("\n");
    for(int i=0; i<sl.size(); i++) {
        res += Log::highlightLog(logFormat, prefix + QString(sl.at(i)), darkBackground ).trimmed();
    }

    QString endLine = (logFormat == PlainLog) ? "\n" : "<br>";
    if (res.right( endLine.length() ) == endLine) res.remove( res.length()-endLine.length(), endLine.length() );
    return res.trimmed();
}
//=======================================================================================================
QString Log::highlightLogString(LogFormat logFormat, LogType logType, const QString &text, bool darkBackground)
{
    return highlightLogString(logFormat, QDateTime::currentDateTime(), logType, text, darkBackground);
}
//=======================================================================================================
QString Log::highlightLog(LogFormat logFormat, const QString &logText, bool darkBackground)
{
    QString res = "";
    QStringList strList = logText.split("\n");
    if(strList.isEmpty()) return res;

    QString preDate = "", prePrefix = "", preInf = "", preWrn = "", preErr = "", preIn = "", preOut = "",
            preTxt = "", preDbg = "", preOther = "";
    QString suffix = "", endLine = "\n";

    if(logFormat == RichLog) {
        endLine = "<br>";
        suffix = "</font>";
        preDate = "<font color=\"" + (darkBackground ? clLogDateDark : clLogDateLight) + "\">";
        prePrefix = "<font color=\"" + (darkBackground ? clLogPrefixDark : clLogPrefixLight) + "\">";
        preInf = "<font color=\"" + (darkBackground ? clLogInfDark : clLogInfLight) + "\">";
        preWrn = "<font color=\"" + (darkBackground ? clLogWrnDark : clLogWrnLight) + "\">";
        preErr = "<font color=\"" + (darkBackground ? clLogErrDark : clLogErrLight) + "\">";
        preIn = "<font color=\"" + (darkBackground ? clLogInDark : clLogInLight) + "\">";
        preOut = "<font color=\"" + (darkBackground ? clLogOutDark : clLogOutLight) + "\">";
        preTxt = "<font color=\"" + (darkBackground ? clLogTxtDark : clLogTxtLight) + "\">";
        preDbg = "<font color=\"" + (darkBackground ? clLogDbgDark : clLogDbgLight) + "\">";
        preOther = "<font color=\"" + (darkBackground ? clLogOtherDark : clLogOtherLight) + "\">";
    }
    else if(logFormat == HtmlLog) {
        endLine = "<br>";
        suffix = "</span>";
        preDate = "<span style=\"color: " + (darkBackground ? clLogDateDark : clLogDateLight) + ";\">";
        prePrefix = "<span style=\"color: " + (darkBackground ? clLogPrefixDark : clLogPrefixLight) + ";\">";
        preInf = "<span style=\"color: " + (darkBackground ? clLogInfDark : clLogInfLight) + ";\">";
        preWrn = "<span style=\"color: " + (darkBackground ? clLogWrnDark : clLogWrnLight) + ";\">";
        preErr = "<span style=\"color: " + (darkBackground ? clLogErrDark : clLogErrLight) + ";\">";
        preIn = "<span style=\"color: " + (darkBackground ? clLogInDark : clLogInLight) + ";\">";
        preOut = "<span style=\"color: " + (darkBackground ? clLogOutDark : clLogOutLight) + ";\">";
        preTxt = "<span style=\"color: " + (darkBackground ? clLogTxtDark : clLogTxtLight) + ";\">";
        preDbg = "<span style=\"color: " + (darkBackground ? clLogDbgDark : clLogDbgLight) + ";\">";
        preOther = "<span style=\"color: " + (darkBackground ? clLogOtherDark : clLogOtherLight) + ";\">";
    }

    for(int i=0; i<strList.size(); ++i) {
        QString str = strList.at(i);
        QString dtStr = "", typeStr = "";
        while( (str.length()>0) && ( (str.right(1) == "\n") || (str.right(1) == "\r") ) ) str.remove( str.length()-1, 1 );

        if((str.length() > 20) && (str[0] == QChar('[')) && (str[13] == QChar(']')) &&
                (str[14] == QChar('[')) && (str[18] == QChar(']')) ) {
            dtStr = str.left(14);
            typeStr = str.mid(14, 5);
            str.remove(0,19);
        }

        QString line = "";
        if(!dtStr.isEmpty())
            line += preDate + ((logFormat == HtmlLog) ? dtStr.toHtmlEscaped() : dtStr) + suffix;
        if(!typeStr.isEmpty())
            line += prePrefix + ((logFormat != PlainLog) ? typeStr.toHtmlEscaped() : typeStr) + suffix;

        if(logFormat == HtmlLog) str = str.toHtmlEscaped();
        if(str.isEmpty()) str = (logFormat == PlainLog) ? " " : "&nbsp;";

        if(typeStr == "[inf]")
            line += preInf + str + suffix;
        else if(typeStr == "[wrn]")
            line += preWrn + ((logFormat == PlainLog) ? "" : "<i>") + str + ((logFormat == PlainLog) ? "" : "</i>") + suffix;
        else if(typeStr == "[err]")
            line += preErr + ((logFormat == PlainLog) ? "" : "<b><i>") + str + ((logFormat == PlainLog) ? "" : "</i></b>") + suffix;
        else if(typeStr == "[<<<]")
            line += preIn + str + suffix;
        else if(typeStr == "[>>>]")
            line += preOut + str + suffix;
        else if(typeStr == "[txt]")
            line += preTxt + str + suffix;
        else if(typeStr == "[dbg]")
            line += preDbg + str + suffix;
        else
            line += preOther + str + suffix;

        res += line + endLine;
    }
    return res;
}
//=======================================================================================================
QString Log::readLog(LogFormat logFormat, const QString &fileName, bool darkBackground)
{
    QString res;
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) return res;

    while(!f.atEnd()) {

        QString str = QString(f.readLine());
        while( (str.length()>0) && ( (str.right(1) == "\n") || (str.right(1) == "\r") ) ) str.remove( str.length()-1, 1 );
        res += str + "\n";
    }
    f.close();

    return highlightLog( logFormat, res, darkBackground);;
}
//=======================================================================================================
QStringList Log::logFiles(const QString &logDir)
{
    QDir dir(logDir);
    return dir.entryList(QStringList("*.log"), QDir::Files | QDir::NoSymLinks);
}
//=======================================================================================================
QStringList Log::logFiles(const QString &rootLogDir, QDate date)
{
    QString d = QDir::toNativeSeparators(rootLogDir);
    if(d.right(1) != QDir::separator()) d += QDir::separator();
    d += date.toString("yyyy") + QDir::separator() +
            date.toString("MM") + QDir::separator() +
            date.toString("dd") + QDir::separator();
    return logFiles(d);
}
//=======================================================================================================
void Log::onLog(LogType logType, QString text)
{
    if((logType == LogDbg) && !_dbg) return;
    write(logType, text);
}
//=======================================================================================================
} // namespace nayk
