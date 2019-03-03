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
#ifndef NAYK_COM_PORT_H
#define NAYK_COM_PORT_H

#include <QObject>
#include <QSerialPort>

#ifdef QT_GUI_LIB
#include <QComboBox>
#endif

#include "log.h"
//======================================================================================================
namespace nayk {
//======================================================================================================

typedef struct PortSettingsStruct {
    QString portName;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity parity;
    bool dtr;
    bool rts;
    qint32 bufSize;
} PortSettingsStruct;

//======================================================================================================
class ComPort : public QObject
{
    Q_OBJECT

public:
    explicit ComPort(QObject *parent = nullptr, bool autoRead = false );
    ~ComPort();
    QString lastError() const { return _lastError; }
    bool autoRead() { return _autoRead; }
    void setAutoRead( bool on ) { _autoRead = on; }
    bool open(QIODevice::OpenMode openMode = QIODevice::ReadWrite);
    bool close();
    bool isOpen() const { return port.isOpen(); }
    QString portName() const { return port.portName(); }
    qint32 baudRate() const { return port.baudRate(); }
    QSerialPort::DataBits dataBits() const { return port.dataBits(); }
    QSerialPort::StopBits stopBits() const { return port.stopBits(); }
    QSerialPort::Parity parity() const { return port.parity(); }
    PortSettingsStruct portSettings();
    bool isDtr() { return port.isDataTerminalReady(); }
    bool isRts() { return port.isRequestToSend(); }

    bool setPortSettings(const QString &portName, qint32 baudRate = 9600, QSerialPort::DataBits dataBits = QSerialPort::Data8,
                         QSerialPort::StopBits stopBits = QSerialPort::OneStop, QSerialPort::Parity parity = QSerialPort::NoParity,
                         qint64 bufSize = 1024);
    bool setPortSettings( const PortSettingsStruct &portSettings );
    bool setPortName(const QString &portName);
    bool setBaudRate(qint32 baudRate);
    bool setDataBits(QSerialPort::DataBits dataBits);
    bool setStopBits(QSerialPort::StopBits stopBits);
    bool setParity(QSerialPort::Parity parity);
    bool setBufferSize(qint64 bufSize);
    bool setDtr(bool on = true);
    bool setRts(bool on = true);
    bool clear(QSerialPort::Directions directions = QSerialPort::AllDirections);
    QByteArray readAll();
    qint64 write(const QByteArray &data);

    static QString dataBitsToStr(QSerialPort::DataBits dataBits);
    static QString stopBitsToStr(QSerialPort::StopBits stopBits);
    static QString parityToStr(QSerialPort::Parity parity);
    static QSerialPort::DataBits strToDataBits(const QString &dataBitsStr);
    static QSerialPort::StopBits strToStopBits(const QString &stopBitsStr);
    static QSerialPort::Parity strToParity(const QString &parityStr);
    static PortSettingsStruct readSettingsFromFile(const QString &fileName, const QString &sectionName, const PortSettingsStruct &defaultSettings);
    static bool writeSettingsToFile(const QString &fileName, const QString &sectionName, const PortSettingsStruct &portSettings);
    static PortSettingsStruct parseSettingsFromString(const QString &settingsString);
    static QString settingsString(const PortSettingsStruct &portSettings, bool withPortName = true);

#ifdef QT_GUI_LIB
    static void fillPortNameBox(QComboBox *box, const QString &defaultPortName = QString());
    static void fillBaudRateBox(QComboBox *box, qint32 defaultBaudRate = 9600);
    static void fillDataBitsBox(QComboBox *box, QSerialPort::DataBits defaultDataBits = QSerialPort::Data8);
    static void fillStopBitsBox(QComboBox *box, QSerialPort::StopBits defaultStopBits = QSerialPort::OneStop);
    static void fillParityBox(QComboBox *box, QSerialPort::Parity defaultParity = QSerialPort::NoParity);
#endif

private:
    QSerialPort port;
    QString _lastError {""};
    bool _autoRead {false};

signals:
    void toLog(LogType logType, QString text);
    void rxBytes(QByteArray rxBuf);
    void readyRead();
    void beforeOpen();
    void afterOpen();
    void beforeClose();
    void afterClose();
    void errorOccurred(QSerialPort::SerialPortError error);

private slots:
    void on_ReadyRead();
    void on_Error(QSerialPort::SerialPortError error);
};
//======================================================================================================
} // namespace nayk
#endif // NAYK_COM_PORT_H
