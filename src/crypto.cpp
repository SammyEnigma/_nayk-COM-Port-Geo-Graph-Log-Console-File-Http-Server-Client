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
#include <QCryptographicHash>
#include <QObject>

#include "crypto.h"

//==========================================================================================================
namespace nayk {

/*  AES-128 Texas Instruments Algorithm ================================================================= */

// foreward sbox
const unsigned char sbox[256] =   {
//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,   //0
0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,   //1
0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,   //2
0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,   //3
0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,   //4
0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,   //5
0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,   //6
0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,   //7
0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,   //8
0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,   //9
0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,   //A
0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,   //B
0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,   //C
0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,   //D
0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,   //E
0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F

// inverse sbox
const unsigned char rsbox[256] =
{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

// round constant
const unsigned char Rcon[10] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

// multiply by 2 in the galois field
unsigned char galois_mul2(unsigned char value)
{
  signed char temp;
  // cast to signed value
  temp = static_cast<signed char>(value);
  // if MSB is 1, then this will signed extend and fill the temp variable with 1's
  temp = temp >> 7;
  // AND with the reduction variable
  temp = temp & 0x1b;
  // finally shift and reduce the value
  return static_cast<unsigned char>((value << 1)^temp);
}

// AES encryption and decryption function
// The code was optimized for memory (flash and ram)
// Combining both encryption and decryption resulted in a slower implementation
// but much smaller than the 2 functions separated
// This function only implements AES-128 encryption and decryption (AES-192 and
// AES-256 are not supported by this code)
void aes_enc_dec(unsigned char *state, unsigned char *key, unsigned char dir)
{
  unsigned char buf1, buf2, buf3, buf4, round, i;

  // In case of decryption
  if (dir) {
    // compute the last key of encryption before starting the decryption
    for (round = 0 ; round < 10; round++) {
      //key schedule
      key[0] = sbox[key[13]]^key[0]^Rcon[round];
      key[1] = sbox[key[14]]^key[1];
      key[2] = sbox[key[15]]^key[2];
      key[3] = sbox[key[12]]^key[3];
      for (i=4; i<16; i++) {
        key[i] = key[i] ^ key[i-4];
      }
    }

    //first Addroundkey
    for (i = 0; i <16; i++){
      state[i]=state[i] ^ key[i];
    }
  }

  // main loop
  for (round = 0; round < 10; round++){
    if (dir){
      //Inverse key schedule
      for (i=15; i>3; --i) {
    key[i] = key[i] ^ key[i-4];
      }
      key[0] = sbox[key[13]]^key[0]^Rcon[9-round];
      key[1] = sbox[key[14]]^key[1];
      key[2] = sbox[key[15]]^key[2];
      key[3] = sbox[key[12]]^key[3];
    } else {
      for (i = 0; i <16; i++){
        // with shiftrow i+5 mod 16
    state[i]=sbox[state[i] ^ key[i]];
      }
      //shift rows
      buf1 = state[1];
      state[1] = state[5];
      state[5] = state[9];
      state[9] = state[13];
      state[13] = buf1;

      buf1 = state[2];
      buf2 = state[6];
      state[2] = state[10];
      state[6] = state[14];
      state[10] = buf1;
      state[14] = buf2;

      buf1 = state[15];
      state[15] = state[11];
      state[11] = state[7];
      state[7] = state[3];
      state[3] = buf1;
    }
    //mixcol - inv mix
    if ((round > 0 && dir) || (round < 9 && !dir)) {
      for (i=0; i <4; i++){
        buf4 = static_cast<unsigned char>(i << 2);
        if (dir){
          // precompute for decryption
          buf1 = galois_mul2(galois_mul2(state[buf4]^state[buf4+2]));
          buf2 = galois_mul2(galois_mul2(state[buf4+1]^state[buf4+3]));
          state[buf4] ^= buf1; state[buf4+1] ^= buf2; state[buf4+2] ^= buf1; state[buf4+3] ^= buf2;
        }
        // in all cases
        buf1 = state[buf4] ^ state[buf4+1] ^ state[buf4+2] ^ state[buf4+3];
        buf2 = state[buf4];
        buf3 = state[buf4]^state[buf4+1]; buf3=galois_mul2(buf3); state[buf4] = state[buf4] ^ buf3 ^ buf1;
        buf3 = state[buf4+1]^state[buf4+2]; buf3=galois_mul2(buf3); state[buf4+1] = state[buf4+1] ^ buf3 ^ buf1;
        buf3 = state[buf4+2]^state[buf4+3]; buf3=galois_mul2(buf3); state[buf4+2] = state[buf4+2] ^ buf3 ^ buf1;
        buf3 = state[buf4+3]^buf2;     buf3=galois_mul2(buf3); state[buf4+3] = state[buf4+3] ^ buf3 ^ buf1;
      }
    }

    if (dir) {
      //Inv shift rows
      // Row 1
      buf1 = state[13];
      state[13] = state[9];
      state[9] = state[5];
      state[5] = state[1];
      state[1] = buf1;
      //Row 2
      buf1 = state[10];
      buf2 = state[14];
      state[10] = state[2];
      state[14] = state[6];
      state[2] = buf1;
      state[6] = buf2;
      //Row 3
      buf1 = state[3];
      state[3] = state[7];
      state[7] = state[11];
      state[11] = state[15];
      state[15] = buf1;

      for (i = 0; i <16; i++){
        // with shiftrow i+5 mod 16
        state[i]=rsbox[state[i]] ^ key[i];
      }
    } else {
      //key schedule
      key[0] = sbox[key[13]]^key[0]^Rcon[round];
      key[1] = sbox[key[14]]^key[1];
      key[2] = sbox[key[15]]^key[2];
      key[3] = sbox[key[12]]^key[3];
      for (i=4; i<16; i++) {
        key[i] = key[i] ^ key[i-4];
      }
    }
  }
  if (!dir) {
  //last Addroundkey
    for (i = 0; i <16; i++){
      // with shiftrow i+5 mod 16
      state[i]=state[i] ^ key[i];
    } // enf for
  } // end if (!dir)
} // end function

/* AES-128 End Section ===================================================================================*/

quint8 reverse8(quint8 value)
{
    value = static_cast<quint8>((value & 0xF0) >> 4 | (value & 0x0F) << 4);
    value = static_cast<quint8>((value & 0xCC) >> 2 | (value & 0x33) << 2);
    value = static_cast<quint8>((value & 0xAA) >> 1 | (value & 0x55) << 1);
    return value;
}
//==========================================================================================================
const QString Err_Empty_InData          = QObject::tr("Нет входящих данных.");
const QString Err_Length_InData         = QObject::tr("Неверная длина входящих данных.");
const QString Err_Empty_Key             = QObject::tr("Не указан ключ шифрования.");

//==========================================================================================================
Crypto::Crypto(CryptoAlg algorythm)
{
    _algorythm = algorythm;
}
//==========================================================================================================
Crypto::~Crypto()
{

}
//==========================================================================================================
bool Crypto::encryptData(const QString &inData, const QString &key, QString &outData)
{
    QByteArray inDataBuf = inData.toUtf8();
    QByteArray outDataBuf;
    if (!encryptData(inDataBuf, key, outDataBuf)) return false;
    outData = QString(outDataBuf.toHex()).toLower();
    return true;
}
//==========================================================================================================
bool Crypto::decryptData(const QString &inData, const QString &key, QString &outData)
{
    QByteArray inDataBuf = QByteArray::fromHex( inData.toUtf8() );
    QByteArray outDataBuf;
    if (!decryptData(inDataBuf, key, outDataBuf)) return false;
    outData = QString::fromUtf8( outDataBuf ).trimmed();
    return true;
}
//==========================================================================================================
bool Crypto::encryptData(const QByteArray &inData, const QString &key, QByteArray &outData)
{
    _lastError = "";
    if (inData.isNull() || inData.isEmpty()) {
        _lastError = Err_Empty_InData;
        return false;
    }
    if (key.isNull() || key.isEmpty()) {
        _lastError = Err_Empty_Key;
        return false;
    }

    QByteArray md5Key = QCryptographicHash::hash( key.toUtf8(), QCryptographicHash::Md5 );
    outData.clear();

    switch (_algorythm) {
    case CryptoAlg_TexasAES128:
        outData = encryptAES128(inData, md5Key);
        break;
    //default:
    //    break;
    }

    return true;
}
//==========================================================================================================
bool Crypto::decryptData(const QByteArray &inData, const QString &key, QByteArray &outData)
{
    _lastError = "";
    if (inData.isNull() || inData.isEmpty() || ((inData.size() % 16) != 0)) {
        _lastError = Err_Length_InData;
        return false;
    }
    if (key.isNull() || key.isEmpty()) {
        _lastError = Err_Empty_Key;
        return false;
    }

    QByteArray md5Key = QCryptographicHash::hash( key.toUtf8(), QCryptographicHash::Md5 );
    outData.clear();

    switch (_algorythm) {
    case CryptoAlg_TexasAES128:
        outData = decryptAES128(inData, md5Key);
        break;
    //default:
    //    break;
    }

    return true;
}
//==========================================================================================================
QByteArray Crypto::encryptAES128(const QByteArray &data, const QByteArray &md5Key)
{
    if (data.isEmpty()) return QByteArray();
    QByteArray dataBuf(data);
    QByteArray resBuf;
    while (dataBuf.size() % 16 != 0) dataBuf.append( static_cast<char>(0) );
    for(int i=0; i<dataBuf.size(); i+=16) {
        resBuf.append( encryptAES128_Block( dataBuf.mid(i, 16), md5Key ) );
    }
    return resBuf;
}
//==========================================================================================================
QByteArray Crypto::decryptAES128(const QByteArray &data, const QByteArray &md5Key)
{
    if (data.isEmpty() || ((data.size() % 16) != 0)) return QByteArray();
    QByteArray resBuf;

    for(int i=0; i<data.size(); i+=16) {
        resBuf.append( decryptAES128_Block( data.mid(i, 16), md5Key ) );
    }
    return resBuf;
}
//==========================================================================================================
QByteArray Crypto::encryptAES128_Block(const QByteArray &dataBuf, const QByteArray &md5Key)
{
    unsigned char *ucBuf;
    unsigned char *ucKey;
    int keySize;
    int bufSize;

    keySize = md5Key.size(); // 16 байт = 128 бит
    ucKey = new unsigned char [ static_cast<unsigned long>(keySize) ];
    for(auto i=0; i<keySize; i++) {
        ucKey[i] = static_cast<unsigned char>( md5Key.at(i) & 0xFF );
    }

    bufSize = dataBuf.size();
    while (bufSize%16 != 0) bufSize++; // размер должен быть кратным 128 бит
    ucBuf = new unsigned char [ static_cast<unsigned long>(bufSize) ];
    for(int i=0; i<bufSize; i++) {
        ucBuf[i] = (i<dataBuf.size()) ? static_cast<unsigned char>( dataBuf.at(i) & 0xFF ) : 0;
    }

    // шифрование:
    aes_enc_dec( ucBuf, ucKey, 0 );

    QByteArray res;
    for(auto i=0; i<bufSize; i++) res.append( static_cast<char>( ucBuf[i] ) );

    delete [] ucBuf;
    delete [] ucKey;

    return res;
}
//==========================================================================================================
QByteArray Crypto::decryptAES128_Block(const QByteArray &dataBuf, const QByteArray &md5Key)
{
    unsigned char *ucBuf;
    unsigned char *ucKey;
    int keySize;
    int bufSize;

    keySize = md5Key.size(); // 16 байт = 128 бит
    ucKey = new unsigned char [ static_cast<unsigned long>(keySize) ];
    for(auto i=0; i<keySize; i++) {
        ucKey[i] = static_cast<unsigned char>( md5Key.at(i) & 0xFF );
    }

    bufSize = dataBuf.size();
    while (bufSize%16 != 0) bufSize++; // размер должен быть кратным 128 бит
    ucBuf = new unsigned char [static_cast<unsigned long>(bufSize)];
    for(int i=0; i<bufSize; i++) {
        ucBuf[i] = static_cast<unsigned char>( dataBuf.at(i) & 0xFF );
    }

    // дешифрование:
    aes_enc_dec( ucBuf, ucKey, 1 );

    QByteArray res;
    for(auto i=0; i<bufSize; i++) res.append( static_cast<char>(ucBuf[i]) );

    delete [] ucBuf;
    delete [] ucKey;

    return res;
}
//==========================================================================================================
QString Crypto::md5(const QString &data)
{
    return QString::fromUtf8(
                QCryptographicHash::hash( data.toUtf8(), QCryptographicHash::Md5 ).toHex()
           ).toLower();
}
//====================================================================================================
QByteArray Crypto::md5Bytes(const QString &data)
{
    return QCryptographicHash::hash( data.toUtf8(), QCryptographicHash::Md5 );
}
//====================================================================================================
/*
Name :   CRC-8 Dallas
Width :  8
Poly :   0x31 = x^8 + x^5 + x^4 + x^0
Init :   0x00
RefIn :  True
RefOut : True
XorOut : 0x00
Check :  0xA1 = "123456789"
*/
quint8 Crypto::crc8_Dallas(const QByteArray &data)
{
    quint8 crc = 0;
    for(auto n=0; n<data.size(); ++n) {
        quint8 inbyte = static_cast<quint8>( data.at(n) & 0xFF );
        for (quint8 i = 8; i; i--) {
            quint8 mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
//====================================================================================================
quint8 Crypto::crc8_Dallas(const QVector<quint8> &data)
{
    quint8 crc = 0;
    for(int n=0; n<data.size(); ++n) {
        quint8 inbyte = data.at(n);
        for (quint8 i = 8; i; i--) {
            quint8 mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
//==========================================================================================================
quint8 Crypto::crc8_Dallas(const quint8 * data, qint32 size)
{
    quint8 crc = 0;
    while (size--) {
        quint8 inbyte = *data++;
        for (quint8 i = 8; i; i--) {
            quint8 mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
//==================================================================================================
const quint8 crc8_Table[256] = {
    0x00, 0x31, 0x62, 0x53, 0xC4, 0xF5, 0xA6, 0x97,
    0xB9, 0x88, 0xDB, 0xEA, 0x7D, 0x4C, 0x1F, 0x2E,
    0x43, 0x72, 0x21, 0x10, 0x87, 0xB6, 0xE5, 0xD4,
    0xFA, 0xCB, 0x98, 0xA9, 0x3E, 0x0F, 0x5C, 0x6D,
    0x86, 0xB7, 0xE4, 0xD5, 0x42, 0x73, 0x20, 0x11,
    0x3F, 0x0E, 0x5D, 0x6C, 0xFB, 0xCA, 0x99, 0xA8,
    0xC5, 0xF4, 0xA7, 0x96, 0x01, 0x30, 0x63, 0x52,
    0x7C, 0x4D, 0x1E, 0x2F, 0xB8, 0x89, 0xDA, 0xEB,
    0x3D, 0x0C, 0x5F, 0x6E, 0xF9, 0xC8, 0x9B, 0xAA,
    0x84, 0xB5, 0xE6, 0xD7, 0x40, 0x71, 0x22, 0x13,
    0x7E, 0x4F, 0x1C, 0x2D, 0xBA, 0x8B, 0xD8, 0xE9,
    0xC7, 0xF6, 0xA5, 0x94, 0x03, 0x32, 0x61, 0x50,
    0xBB, 0x8A, 0xD9, 0xE8, 0x7F, 0x4E, 0x1D, 0x2C,
    0x02, 0x33, 0x60, 0x51, 0xC6, 0xF7, 0xA4, 0x95,
    0xF8, 0xC9, 0x9A, 0xAB, 0x3C, 0x0D, 0x5E, 0x6F,
    0x41, 0x70, 0x23, 0x12, 0x85, 0xB4, 0xE7, 0xD6,
    0x7A, 0x4B, 0x18, 0x29, 0xBE, 0x8F, 0xDC, 0xED,
    0xC3, 0xF2, 0xA1, 0x90, 0x07, 0x36, 0x65, 0x54,
    0x39, 0x08, 0x5B, 0x6A, 0xFD, 0xCC, 0x9F, 0xAE,
    0x80, 0xB1, 0xE2, 0xD3, 0x44, 0x75, 0x26, 0x17,
    0xFC, 0xCD, 0x9E, 0xAF, 0x38, 0x09, 0x5A, 0x6B,
    0x45, 0x74, 0x27, 0x16, 0x81, 0xB0, 0xE3, 0xD2,
    0xBF, 0x8E, 0xDD, 0xEC, 0x7B, 0x4A, 0x19, 0x28,
    0x06, 0x37, 0x64, 0x55, 0xC2, 0xF3, 0xA0, 0x91,
    0x47, 0x76, 0x25, 0x14, 0x83, 0xB2, 0xE1, 0xD0,
    0xFE, 0xCF, 0x9C, 0xAD, 0x3A, 0x0B, 0x58, 0x69,
    0x04, 0x35, 0x66, 0x57, 0xC0, 0xF1, 0xA2, 0x93,
    0xBD, 0x8C, 0xDF, 0xEE, 0x79, 0x48, 0x1B, 0x2A,
    0xC1, 0xF0, 0xA3, 0x92, 0x05, 0x34, 0x67, 0x56,
    0x78, 0x49, 0x1A, 0x2B, 0xBC, 0x8D, 0xDE, 0xEF,
    0x82, 0xB3, 0xE0, 0xD1, 0x46, 0x77, 0x24, 0x15,
    0x3B, 0x0A, 0x59, 0x68, 0xFF, 0xCE, 0x9D, 0xAC  };
/*
  Name  : CRC-8
  Poly  : 0x31    x^8 + x^5 + x^4 + 1
  Init  : 0xFF
  Revert: false
  XorOut: 0x00
  Check : 0xF7 ("123456789")
  MaxLen: 15 байт (127 бит) - обнаружение одинарных, двойных, тройных и всех нечетных ошибок
*/
quint8 Crypto::crc8(const QVector<quint8> &data)
{
    quint8 result = 0xFF;

    for(int i=0; i<data.size(); i++) {
        result = crc8_Table[ result ^ data.at(i) ];
    }
    return result;
}
//==================================================================================================
quint8 Crypto::crc8(const QByteArray &data)
{
    quint8 result = 0xFF;

    for(int i=0; i<data.size(); i++) {
        result = crc8_Table[ result ^ static_cast<quint8>(data.at(i)) ];
    }
    return result;
}
//==================================================================================================
quint8 Crypto::crc8(const quint8 *data, qint32 size)
{
    quint8 crc = 0xFF;
    while (size--) crc = crc8_Table[crc ^ *data++];
    return crc;
}
//==================================================================================================
const quint16 crc16_CCITT_Table[256] = {
    0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
    0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
    0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
    0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
    0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
    0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
    0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
    0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
    0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
    0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
    0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
    0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
    0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
    0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
    0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
    0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
    0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
    0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
    0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
    0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
    0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
    0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
    0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
    0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
    0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
    0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
    0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
    0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
    0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
    0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
    0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
    0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0 };
/*
  Name  : CRC-16 CCITT
  Poly  : 0x1021    x^16 + x^12 + x^5 + 1
  Init  : 0xFFFF
  Revert: false
  XorOut: 0x0000
  Check : 0x29B1 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение одинарных, двойных, тройных и всех нечетных ошибок
*/
quint16 Crypto::crc16_Ccitt(const QVector<quint8> &data)
{
    quint16 result = 0xFFFF;

    for(int i=0; i<data.size(); i++) {
        result = static_cast<quint16>(result << 8) ^ crc16_CCITT_Table[ (result >> 8) ^ static_cast<quint8>(data.at(i)) ];
    }
    return result;
}
//==================================================================================================
quint16 Crypto::crc16_Ccitt(const QByteArray &data)
{
    quint16 result = 0xFFFF;

    for(int i=0; i<data.size(); i++) {
        result = static_cast<quint16>(result << 8) ^ crc16_CCITT_Table[ (result >> 8) ^ static_cast<quint8>(data.at(i)) ];
    }
    return result;
}
//==================================================================================================
quint16 Crypto::crc16_Ccitt(const quint8 *data, qint32 size)
{
    quint16 crc = 0xFFFF;

    while (size--) crc = static_cast<quint16>(crc << 8) ^ crc16_CCITT_Table[(crc >> 8) ^ *data++];
    return crc;
}
//==================================================================================================
const quint16 crc16_Table[256] = {
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040 };
/*
  Name  : CRC 16
  Width : 16
  Poly  : 0x8005   x^16 + x^15 + x^2 + 1
  Init  : 0x0000
  RefIn : True
  RefOut: True
  XorOut: 0x0000
  Check : 0xBB3D  ("123456789")
*/
quint16 Crypto::crc16(const QVector<quint8> &data)
{
    quint16 result = 0x0000;

    for(int i=0; i<data.size(); i++) {
        result = static_cast<quint16>(result >> 8) ^ crc16_Table[ (result ^ data.at(i)) & 0xFF ];
    }
    return result;
}
//==================================================================================================
quint16 Crypto::crc16(const QByteArray &data)
{
    quint16 result = 0x0000;

    for(int i=0; i<data.size(); i++) {
        result = static_cast<quint16>(result >> 8) ^ crc16_Table[ (result ^ static_cast<quint8>(data.at(i))) & 0xFF ];
    }
    return result;
}
//==================================================================================================
quint16 Crypto::crc16(const quint8 *data, qint32 size)
{
    quint16 crc = 0xFFFF;
    while (size--) crc = (crc >> 8) ^ crc16_Table[(crc ^ *data++) & 0xFF];
    return crc;
}
//==================================================================================================
quint8 getIndexInCrc16Table(quint8 regValue)
{
    int i = 0;
    quint8 result = 0;

    while (i < 256) {
        if( static_cast<quint8>(crc16_Table[i] >> 8) == regValue ) {
            return static_cast<quint8>(i);
        }
        i++;
   }
   return result;
}
/*
  Нахождение нужных байт для восстановления CRC16
  needCRC - которую нужно получить
  newCRC - Текущая CRC
  результат - 2 байта, которые нужно дописать к данным, чтобы получилась нужная CRC
*/
quint16 Crypto::crc16_Restore(quint16 needCRC, quint16 newCRC)
{
    quint8 a1 = static_cast<quint8>((newCRC & 0xFF00) >> 8);
    quint8 a0 = static_cast<quint8>(newCRC & 0x00FF);
    quint8 d1 = static_cast<quint8>((needCRC & 0xFF00) >> 8);
    quint8 d0 = static_cast<quint8>(needCRC & 0x00FF);
    quint8 b0;
    quint8 c0, n, k, x, y;

    n = getIndexInCrc16Table(d1);
    c0 = static_cast<quint8>( crc16_Table[n] & 0x00FF);
    k = getIndexInCrc16Table(c0 ^ d0);
    b0 = static_cast<quint8>(crc16_Table[k] & 0x00FF);
    y = a1 ^ b0 ^ n;
    x = a0 ^ k;

    return static_cast<quint16>(static_cast<quint16>(x) << 8) | static_cast<quint16>(y);
}
//==================================================================================================
/*
  Name  : CRC-16
  Poly  : 0x8005    x^16 + x^15 + x^2 + 1
  Init  : 0xFFFF
  Revert: true
  XorOut: 0x0000
  Check : 0x4B37 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение одинарных, двойных, тройных и всех нечетных ошибок
*/
quint16 Crypto::crc16_Arc(const QVector<quint8> &data)
{
    quint16 result = 0xFFFF;

    for(int i=0; i<data.size(); i++) {
        result = (result >> 8) ^ crc16_Table[ (result & 0xFF) ^ data.at(i) ];
    }
    return result;
}
//==================================================================================================
quint16 Crypto::crc16_Arc(const QByteArray &data)
{
    quint16 result = 0xFFFF;

    for(int i=0; i<data.size(); i++) {
        result = (result >> 8) ^ crc16_Table[ (result & 0xFF) ^ static_cast<quint8>(data.at(i)) ];
    }
    return result;
}
//==================================================================================================
quint16 Crypto::crc16_Arc(const quint8 *data, qint32 size)
{
    quint16 crc = 0xFFFF;
    while (size--) crc = (crc >> 8) ^ crc16_Table[(crc & 0xFF) ^ *data++];
    return crc;
}
//==================================================================================================
const quint16 wmPoly = 0x3D65;
/*
  Name  : CRC-16 (Wireless MBus)
  Poly  : 0x3D65  x16 + x13 + x12 + x11 + x10 + x8 + x6 + x5 + x2 + 1
  Init  : 0x0000
  XorOut: 0xFFFF
*/
quint16 Crypto::crc16_Wmbus(const QVector<quint8> &data)
{
    quint16 result = 0x0000;

    for(int i=0; i<data.size(); i++) {
        result = result ^ static_cast<quint16>( (static_cast<quint16>(data.at(i)) & 0x00FF) << 8);
        for (int n = 0; n < 8; n++)
            result = static_cast<quint16>( result & 0x8000 ? (result << 1) ^ wmPoly : result << 1);
    }
    return result ^ 0xFFFF;
}
//==================================================================================================
quint16 Crypto::crc16_Wmbus(const QByteArray &data)
{
    quint16 result = 0x0000;

    for(int i=0; i<data.size(); i++) {
        result = result ^ static_cast<quint16>( (static_cast<quint16>(data.at(i)) & 0x00FF) << 8);
        for (int n = 0; n < 8; n++)
            result = static_cast<quint16>( result & 0x8000 ? (result << 1) ^ wmPoly : result << 1);
    }
    return result ^ 0xFFFF;
}
//==================================================================================================
quint16 Crypto::crc16_Wmbus(const quint8 *data, qint32 size)
{
    quint16 crc = 0x0000;
    while (size--) {
        crc = crc ^ static_cast<quint16>( static_cast<quint16>( *data++ )  << 8);
        for (int n = 0; n < 8; n++)
            crc = static_cast<quint16>(crc & 0x8000 ? (crc << 1) ^ wmPoly : crc << 1);
    }
    return crc ^ 0xFFFF;
}
//==================================================================================================
const quint32 crc32_Table[256] = {
    0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
    0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
    0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
    0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,
    0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
    0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
    0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
    0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,
    0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
    0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
    0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
    0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
    0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
    0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
    0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
    0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,
    0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
    0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
    0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
    0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,
    0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
    0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
    0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
    0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
    0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
    0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
    0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
    0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,
    0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
    0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
    0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
    0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,
    0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
    0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
    0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
    0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
    0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
    0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
    0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
    0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,
    0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
    0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
    0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
    0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,
    0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
    0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
    0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
    0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
    0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
    0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
    0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
    0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,
    0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
    0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
    0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
    0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,
    0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
    0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
    0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
    0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
    0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
    0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
    0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
    0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D };
/*
  Name  : CRC-32
  Poly  : 0x04C11DB7    x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x + 1
  Init  : 0xFFFFFFFF
  Revert: true
  XorOut: 0xFFFFFFFF
  Check : 0xCBF43926 ("123456789")
  MaxLen: 268 435 455 байт (2 147 483 647 бит) - обнаружение одинарных, двойных, пакетных и всех нечетных ошибок
*/
quint32 Crypto::crc32(const QVector<quint8> &data)
{
    quint32 result = 0xFFFFFFFF;

    for(int i=0; i<data.size(); i++) {
        result = (result >> 8) ^ crc32_Table[ (result ^ data.at(i)) & 0xFF ];
    }
    return result ^ 0xFFFFFFFF;
}
//==================================================================================================
quint32 Crypto::crc32(const QByteArray &data)
{
    quint32 result = 0xFFFFFFFF;

    for(int i=0; i<data.size(); i++) {
        result = (result >> 8) ^ crc32_Table[ (result ^ static_cast<quint8>(data.at(i))) & 0xFF ];
    }
    return result ^ 0xFFFFFFFF;
}
//==================================================================================================
quint32 Crypto::crc32(const quint8 *data, qint32 size)
{
    quint32 crc = 0xFFFFFFFF;
    while (size--) crc = (crc >> 8) ^ crc32_Table[(crc ^ *data++) & 0xFF];
    return crc ^ 0xFFFFFFFF;
}
//==================================================================================================

//==================================================================================================
} // namespace nayk

