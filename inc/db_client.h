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
#ifndef NAYK_DB_CLIENT_H
#define NAYK_DB_CLIENT_H

#include <QtCore>
#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDateTime>
//
#include "log.h"

//=========================================================================================================
namespace nayk {
//=========================================================================================================

//=========================================================================================================
class DBClient : public QObject
{
    Q_OBJECT

public:
    explicit DBClient(QObject *parent = nullptr, const QString &settingsFileName = QString(), const QString &sqlDriver = QString("QPSQL"));
    ~DBClient();
    void setSettings(const QString &server, quint16 port, const QString &userName, const QString &password, const QString &baseName);
    void setSettingsFileName(const QString &settingsFileName);
    void setSqlDriver(const QString &sqlDriver);
    bool readSettings(const QString &settingsFileName = QString());
    bool writeSettings(const QString &settingsFileName = QString());
    bool open(bool reconnect = false);
    bool close();
    bool isOpen(bool reconnect = false);

    const QString& lastError() { return _lastError; }
    const QString& settingsFileName() { return _settingsFileName; }
    const QString& sqlDriverName() { return _sqlDriver; }
    const QString& userName() { return _userName; }
    const QString& server() { return _server; }
    const QString& password() { return _password; }
    const QString& baseName() { return _baseName; }
    quint16 port() { return _port; }
    QSqlDatabase db() { return QSqlDatabase::database(_connectionName, false); }
    bool execSQL(const QString &sqlText, QSqlQuery *query, bool withTransaction = false);
    bool execSQL(const QString &sqlText);
    bool tableExist(const QString &tableName) { return isOpen() && db().tables().contains( tableName ); }
    bool getTables(QStringList *list);
    bool getTableFields(const QString &tableName, QStringList *list);

signals:
    void toLog(LogType logType, QString text);
    void dbOpen();
    void dbClose();

private:
    QString _connectionName {"connect_" + QString::number(QDateTime::currentMSecsSinceEpoch())};
    QString _lastError {""};
    QString _settingsFileName {""};
    QString _sqlDriver {"QPSQL"};
    QString _server {"localhost"};
    quint16 _port {5432};
    QString _userName {""};
    QString _password {""};
    QString _baseName {""};
};

//=========================================================================================================
} // namespace nayk

//=========================================================================================================
#endif // NAYK_DB_CLIENT_H
