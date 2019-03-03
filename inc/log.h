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
#ifndef NAYK_LOGSAVER_H
#define NAYK_LOGSAVER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
//======================================================================================================
namespace nayk {
//======================================================================================================
enum LogType { LogInfo, LogWarning, LogError, LogIn, LogOut, LogText, LogDbg, LogOther };
enum LogFormat { PlainLog, RichLog, HtmlLog };

//======================================================================================================
class Log : public QObject
{
    Q_OBJECT

public:
    explicit Log(QObject *parent = nullptr, QDateTime startTime = QDateTime(), const QString &logDir = QString(), bool startLogging = false );
    ~Log();
    bool startLog(const QString &fileName = QString(), bool saveDbg = true);
    void setDbgSave(bool on = true) { _dbg = on; }
    bool dbgSave() { return _dbg; }
    bool write(LogType logType, const QString &text);
    QString logFileName() const { return logPath + logFile; }
    QString lastError() const { return _lastError; }
    static QString highlightLog(LogFormat logFormat, const QString &logText, bool darkBackground = false);
    static QString highlightLogString(LogFormat logFormat, LogType logType, const QString &text, bool darkBackground = false);
    static QString readLog(LogFormat logFormat, const QString &fileName, bool darkBackground = false);
    static QStringList logFiles(const QString &logDir);
    static QStringList logFiles(const QString &rootLogDir, QDate date);

private:
    QDateTime startingTime;
    QString logFile {""};
    QString logPath {""};
    QFile file;
    QTextStream stream;
    QString _lastError {""};
    bool _dbg {true};

    bool writeFirstLine();
    bool writeLastLine();
    static QString getLogPrefix(LogType logType, const QDateTime &date = QDateTime::currentDateTime());

signals:
    void openFile(QString);
    void closeFile(QString);

public slots:
    void onLog(LogType logType, QString text);
};
//======================================================================================================
} // namespace nayk
#endif // NAYK_LOGSAVER_H
