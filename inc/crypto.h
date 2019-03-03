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
#ifndef NAYK_CRYPTO_H
#define NAYK_CRYPTO_H

#include <QByteArray>
#include <QVector>
#include <QString>

namespace nayk {
//=========================================================================================================
enum CryptoAlg { CryptoAlg_TexasAES128 };
//=========================================================================================================
class Crypto
{
public:
    explicit Crypto(CryptoAlg algorythm = CryptoAlg_TexasAES128);
    virtual ~Crypto();
    virtual bool encryptData(const QString &inData, const QString &key, QString &outData);
    virtual bool decryptData(const QString &inData, const QString &key, QString &outData);
    virtual bool encryptData(const QByteArray &inData, const QString &key, QByteArray &outData);
    virtual bool decryptData(const QByteArray &inData, const QString &key, QByteArray &outData);
    //
    QString lastError() const { return _lastError; }
    static QString md5(const QString &data);
    static QByteArray md5Bytes(const QString &data);
    static quint8 crc8_Dallas(const QVector<quint8> &data);
    static quint8 crc8_Dallas(const QByteArray &data);
    static quint8 crc8_Dallas(const quint8 *data, qint32 size);

protected:
    QString _lastError {""};

private:
    CryptoAlg _algorythm;
    // шифрование aes128 (Texas Instruments alg.)
    QByteArray encryptAES128_Block(const QByteArray &dataBuf, const QByteArray &md5Key);
    QByteArray decryptAES128_Block(const QByteArray &dataBuf, const QByteArray &md5Key);
    QByteArray encryptAES128(const QByteArray &data, const QByteArray &md5Key);
    QByteArray decryptAES128(const QByteArray &data, const QByteArray &md5Key);
};
//=========================================================================================================
} // namespace nayk

#endif // NAYK_CRYPTO_H
