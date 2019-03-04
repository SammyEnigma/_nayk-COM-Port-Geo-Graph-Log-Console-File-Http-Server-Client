#include <QtTest>
#include "convert.h"

using namespace nayk;

// add necessary includes here
//==================================================================================================
class testConvert : public QObject
{
    Q_OBJECT

public:
    testConvert();
    ~testConvert();

private slots:
    void initTestCase();
    void cleanupTestCase();
    // bcdEncode:
    void test_bcdEncode_qint8_data();
    void test_bcdEncode_qint8();
    void test_bcdEncode_quint8_data();
    void test_bcdEncode_quint8();
    void test_bcdEncode_qint16_data();
    void test_bcdEncode_qint16();
    void test_bcdEncode_quint16_data();
    void test_bcdEncode_quint16();
    void test_bcdEncode_qint32_data();
    void test_bcdEncode_qint32();
    void test_bcdEncode_quint32_data();
    void test_bcdEncode_quint32();
    void test_bcdEncode_qint64_data();
    void test_bcdEncode_qint64();
    void test_bcdEncode_quint64_data();
    void test_bcdEncode_quint64();
    // bcdDecode:
    void test_bcdDecode_qint8();
    void test_bcdDecode_qint16();
    void test_bcdDecode_qint32();
    void test_bcdDecode_qint64();
    void test_bcdDecodeUnsigned_quint8();
    void test_bcdDecodeUnsigned_quint16();
    void test_bcdDecodeUnsigned_quint32();
    void test_bcdDecodeUnsigned_quint64();
    // intToHex:
    void test_intToHex_qint8();
    void test_intToHex_qint16();
    void test_intToHex_qint32();
    void test_intToHex_qint64();
    void test_intToHex_quint8();
    void test_intToHex_quint16();
    void test_intToHex_quint32();
    void test_intToHex_quint64();
    // strToIntDef:
    void test_strToIntDef_qint8();
    void test_strToIntDef_qint16();
    void test_strToIntDef_qint32();
    void test_strToIntDef_qint64();
    void test_strToIntDef_quint8();
    void test_strToIntDef_quint16();
    void test_strToIntDef_quint32();
    void test_strToIntDef_quint64();
    // doubleToStr:
    void test_doubleToStr();
    // strToDouble:
    void test_strToDouble();
    // strToDateTime:
    void test_strToDateTime();
    // lo:
    void test_lo_quint16();
    void test_lo_quint32();
    void test_lo_quint64();
    // hi:
    void test_hi_quint16();
    void test_hi_quint32();
    void test_hi_quint64();
    // reverse:
    void test_reverse_quint16();
    void test_reverse_quint32();
    void test_reverse_quint64();
    // isASCII:
    void test_isASCII_qint8();
    void test_isASCII_quint8();
    void test_isASCII_char();
    // endLineToHTML:
    void test_endLineToHTML();
    // encodeXMLText:
    void test_encodeXMLText();
    // decodeXMLText
    void test_decodeXMLText();
    // changeDecimalSeparator:
    void test_changeDecimalSeparator();
    // changeLineFit:
    void test_changeLineFit();
};
//==================================================================================================
testConvert::testConvert()
{

}
//==================================================================================================
testConvert::~testConvert()
{

}
//==================================================================================================
void testConvert::initTestCase()
{

}
//==================================================================================================
void testConvert::cleanupTestCase()
{

}
//==================================================================================================
void testConvert::test_bcdEncode_qint8_data()
{
    QTest::addColumn<qint8>("value");
    QTest::addColumn<quint8>("result");

    QTest::newRow("zero") << static_cast<qint8>(0) << static_cast<quint8>(0x00);
    QTest::newRow("normal") << static_cast<qint8>(36) << static_cast<quint8>(0x36);
    QTest::newRow("negative") << static_cast<qint8>(-7) << static_cast<quint8>(0xF7);
    QTest::newRow("maximum") << static_cast<qint8>(99) << static_cast<quint8>(0x99);
}
//==================================================================================================
void testConvert::test_bcdEncode_qint8()
{
    QFETCH(qint8, value);
    QFETCH(quint8, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_quint8_data()
{
    QTest::addColumn<quint8>("value");
    QTest::addColumn<quint8>("result");

    QTest::newRow("zero") << static_cast<quint8>(0) << static_cast<quint8>(0x00);
    QTest::newRow("normal") << static_cast<quint8>(36) << static_cast<quint8>(0x36);
    QTest::newRow("maximum") << static_cast<quint8>(99) << static_cast<quint8>(0x99);
}
//==================================================================================================
void testConvert::test_bcdEncode_quint8()
{
    QFETCH(quint8, value);
    QFETCH(quint8, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_qint16_data()
{
    QTest::addColumn<qint16>("value");
    QTest::addColumn<quint16>("result");

    QTest::newRow("zero") << static_cast<qint16>(0) << static_cast<quint16>(0x00);
    QTest::newRow("normal") << static_cast<qint16>(3681) << static_cast<quint16>(0x3681);
    QTest::newRow("negative") << static_cast<qint16>(-666) << static_cast<quint16>(0xF666);
    QTest::newRow("maximum") << static_cast<qint16>(9999) << static_cast<quint16>(0x9999);
}
//==================================================================================================
void testConvert::test_bcdEncode_qint16()
{
    QFETCH(qint16, value);
    QFETCH(quint16, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_quint16_data()
{
    QTest::addColumn<quint16>("value");
    QTest::addColumn<quint16>("result");

    QTest::newRow("zero") << static_cast<quint16>(0) << static_cast<quint16>(0x0000);
    QTest::newRow("normal") << static_cast<quint16>(3678) << static_cast<quint16>(0x3678);
    QTest::newRow("maximum") << static_cast<quint16>(9999) << static_cast<quint16>(0x9999);
}
//==================================================================================================
void testConvert::test_bcdEncode_quint16()
{
    QFETCH(quint16, value);
    QFETCH(quint16, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_qint32_data()
{
    QTest::addColumn<qint32>("value");
    QTest::addColumn<quint32>("result");

    QTest::newRow("zero") << static_cast<qint32>(0) << static_cast<quint32>(0x00000000);
    QTest::newRow("normal") << static_cast<qint32>(12343681) << static_cast<quint32>(0x12343681);
    QTest::newRow("negative") << static_cast<qint32>(-12666) << static_cast<quint32>(0x00F12666);
    QTest::newRow("maximum") << static_cast<qint32>(99999999) << static_cast<quint32>(0x99999999);
}
//==================================================================================================
void testConvert::test_bcdEncode_qint32()
{
    QFETCH(qint32, value);
    QFETCH(quint32, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_quint32_data()
{
    QTest::addColumn<quint32>("value");
    QTest::addColumn<quint32>("result");

    QTest::newRow("zero") << static_cast<quint32>(0) << static_cast<quint32>(0x00000000);
    QTest::newRow("normal") << static_cast<quint32>(36781234) << static_cast<quint32>(0x36781234);
    QTest::newRow("maximum") << static_cast<quint32>(99999999) << static_cast<quint32>(0x99999999);
}
//==================================================================================================
void testConvert::test_bcdEncode_quint32()
{
    QFETCH(quint32, value);
    QFETCH(quint32, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_qint64_data()
{
    QTest::addColumn<qint64>("value");
    QTest::addColumn<quint64>("result");

    QTest::newRow("zero") << static_cast<qint64>(0) << static_cast<quint64>(0x0000000000000000);
    QTest::newRow("normal") << static_cast<qint64>(1234368112343681)   << static_cast<quint64>(0x1234368112343681);
    QTest::newRow("negative") << static_cast<qint64>(-123456712345678) << static_cast<quint64>(0xF123456712345678);
    QTest::newRow("maximum") << static_cast<qint64>(9999999999999999)  << static_cast<quint64>(0x9999999999999999);
}
//==================================================================================================
void testConvert::test_bcdEncode_qint64()
{
    QFETCH(qint64, value);
    QFETCH(quint64, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdEncode_quint64_data()
{
    QTest::addColumn<quint64>("value");
    QTest::addColumn<quint64>("result");

    QTest::newRow("zero") << static_cast<quint64>(0) << static_cast<quint64>(0x0000000000000000);
    QTest::newRow("normal") << static_cast<quint64>(3678123436781234) << static_cast<quint64>(0x3678123436781234);
    QTest::newRow("maximum") << static_cast<quint64>(9999999999999999) << static_cast<quint64>(0x9999999999999999);
}
//==================================================================================================
void testConvert::test_bcdEncode_quint64()
{
    QFETCH(quint64, value);
    QFETCH(quint64, result);
    QCOMPARE( Convert::bcdEncode(value), result );
}
//==================================================================================================
void testConvert::test_bcdDecode_qint8()
{
    QCOMPARE( Convert::bcdDecode( static_cast<quint8>(0x00) ), static_cast<qint8>(0) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint8>(0x54) ), static_cast<qint8>(54) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint8>(0xF8) ), static_cast<qint8>(-8) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint8>(0x99) ), static_cast<qint8>(99) );

    bool ok = true;
    qint8 result = Convert::bcdDecode( static_cast<quint8>(0xAC), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecode_qint16()
{
    QCOMPARE( Convert::bcdDecode( static_cast<quint16>(0x0000) ), static_cast<qint16>(0) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint16>(0x1254) ), static_cast<qint16>(1254) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint16>(0xF128) ), static_cast<qint16>(-128) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint16>(0x9999) ), static_cast<qint16>(9999) );

    bool ok = true;
    qint16 result = Convert::bcdDecode( static_cast<quint16>(0x12AC), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecode_qint32()
{
    QCOMPARE( Convert::bcdDecode( static_cast<quint32>(0x00000000) ), static_cast<qint32>(0) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint32>(0x54321254) ), static_cast<qint32>(54321254) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint32>(0x00F12128) ), static_cast<qint32>(-12128) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint32>(0x99999999) ), static_cast<qint32>(99999999) );

    bool ok = true;
    qint32 result = Convert::bcdDecode( static_cast<quint32>(0xABCD12AC), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecode_qint64()
{
    QCOMPARE( Convert::bcdDecode( static_cast<quint64>(0x0000000000000000) ), static_cast<qint64>(0) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint64>(0x1234567854321254) ), static_cast<qint64>(1234567854321254) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint64>(0x00F1212812345678) ), static_cast<qint64>(-1212812345678) );
    QCOMPARE( Convert::bcdDecode( static_cast<quint64>(0x9999999999999999) ), static_cast<qint64>(9999999999999999) );

    bool ok = true;
    qint64 result = Convert::bcdDecode( static_cast<quint64>(0x12345678ABCD12AC), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecodeUnsigned_quint8()
{
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint8>(0x00) ), static_cast<quint8>(0) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint8>(0x54) ), static_cast<quint8>(54) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint8>(0x99) ), static_cast<quint8>(99) );

    bool ok = true;
    quint8 result = Convert::bcdDecodeUnsigned( static_cast<quint8>(0xAB), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecodeUnsigned_quint16()
{
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint16>(0x0000) ), static_cast<quint16>(0) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint16>(0x1254) ), static_cast<quint16>(1254) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint16>(0x9999) ), static_cast<quint16>(9999) );

    bool ok = true;
    quint16 result = Convert::bcdDecodeUnsigned( static_cast<quint16>(0xF123), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecodeUnsigned_quint32()
{
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint32>(0x00000000) ), static_cast<quint32>(0) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint32>(0x54321234) ), static_cast<quint32>(54321234) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint32>(0x99999999) ), static_cast<quint32>(99999999) );

    bool ok = true;
    quint32 result = Convert::bcdDecodeUnsigned( static_cast<quint32>(0xF123ABCD), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_bcdDecodeUnsigned_quint64()
{
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint64>(0x0000000000000000) ), static_cast<quint64>(0) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint64>(0x5432123400000000) ), static_cast<quint64>(5432123400000000) );
    QCOMPARE( Convert::bcdDecodeUnsigned( static_cast<quint64>(0x9999999999999999) ), static_cast<quint64>(9999999999999999) );

    bool ok = true;
    quint64 result = Convert::bcdDecodeUnsigned( static_cast<quint64>(0x00000000F123ABCD), &ok );
    Q_UNUSED(result);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_intToHex_qint8()
{
    QCOMPARE( Convert::intToHex( static_cast<qint8>(0x00), 2, true ),  "0x00" );
    QCOMPARE( Convert::intToHex( static_cast<qint8>(0x04), 1, false ), "4"    );
    QCOMPARE( Convert::intToHex( static_cast<qint8>(0x1A), 2, true ),  "0x1A" );
    QCOMPARE( Convert::intToHex( static_cast<qint8>(0x7B), 2, false ), "7B"   );
}
//==================================================================================================
void testConvert::test_intToHex_qint16()
{
    QCOMPARE( Convert::intToHex( static_cast<qint16>(0x0000), 2, true ),  "0x00"   );
    QCOMPARE( Convert::intToHex( static_cast<qint16>(0x1204), 4, false ), "1204"   );
    QCOMPARE( Convert::intToHex( static_cast<qint16>(0x08F8), 4, true ),  "0x08F8" );
    QCOMPARE( Convert::intToHex( static_cast<qint16>(0x50AB), 4, false ), "50AB"   );
}
//==================================================================================================
void testConvert::test_intToHex_qint32()
{
    QCOMPARE( Convert::intToHex( static_cast<qint32>(0x00000000), 8, true ),  "0x00000000" );
    QCOMPARE( Convert::intToHex( static_cast<qint32>(0x00201204), 6, false ), "201204"     );
    QCOMPARE( Convert::intToHex( static_cast<qint32>(0x123408F8), 8, true ),  "0x123408F8" );
    QCOMPARE( Convert::intToHex( static_cast<qint32>(0x7FFF50AB), 8, false ), "7FFF50AB"   );
}
//==================================================================================================
void testConvert::test_intToHex_qint64()
{
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x0000000000000000), 8,  true ),  "0x00000000"         );
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x1234567800201204), 16, false ), "1234567800201204"   );
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x123408F812345678), 16, true ),  "0x123408F812345678" );
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x076543217FFF50AB), 16, false ), "076543217FFF50AB"   );
}
//==================================================================================================
void testConvert::test_intToHex_quint8()
{
    QCOMPARE( Convert::intToHex( static_cast<quint8>(0x00), 2, true ),  "0x00" );
    QCOMPARE( Convert::intToHex( static_cast<quint8>(0x04), 1, false ), "4"    );
    QCOMPARE( Convert::intToHex( static_cast<quint8>(0x8A), 2, true ),  "0x8A" );
    QCOMPARE( Convert::intToHex( static_cast<quint8>(0xFB), 2, false ), "FB"   );
}
//==================================================================================================
void testConvert::test_intToHex_quint16()
{
    QCOMPARE( Convert::intToHex( static_cast<quint16>(0x0000), 2, true ),  "0x00"   );
    QCOMPARE( Convert::intToHex( static_cast<quint16>(0x1204), 4, false ), "1204"   );
    QCOMPARE( Convert::intToHex( static_cast<quint16>(0x88F8), 4, true ),  "0x88F8" );
    QCOMPARE( Convert::intToHex( static_cast<quint16>(0xF0AB), 4, false ), "F0AB"   );
}
//==================================================================================================
void testConvert::test_intToHex_quint32()
{
    QCOMPARE( Convert::intToHex( static_cast<quint32>(0x00000000), 8, true ),  "0x00000000" );
    QCOMPARE( Convert::intToHex( static_cast<quint32>(0x00201204), 6, false ), "201204"     );
    QCOMPARE( Convert::intToHex( static_cast<quint32>(0x823408F8), 8, true ),  "0x823408F8" );
    QCOMPARE( Convert::intToHex( static_cast<quint32>(0xFFFF50AB), 8, false ), "FFFF50AB"   );
}
//==================================================================================================
void testConvert::test_intToHex_quint64()
{
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x0000000000000000), 8,  true ),  "0x00000000"         );
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x1234567800201204), 16, false ), "1234567800201204"   );
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0x823408F812345678), 16, true ),  "0x823408F812345678" );
    QCOMPARE( Convert::intToHex( static_cast<qint64>(0xF76543217FFF50AB), 16, false ), "F76543217FFF50AB"   );
}
//==================================================================================================
void testConvert::test_strToIntDef_qint8()
{
    QCOMPARE( Convert::strToIntDef( "0",     static_cast<qint8>(-1) ),  static_cast<qint8>(0)    );
    QCOMPARE( Convert::strToIntDef( "-10",   static_cast<qint8>(-1) ),  static_cast<qint8>(-10)  );
    QCOMPARE( Convert::strToIntDef( "error", static_cast<qint8>(-1) ),  static_cast<qint8>(-1)   );
    QCOMPARE( Convert::strToIntDef( "123",   static_cast<qint8>(-1) ),  static_cast<qint8>(123)  );
    QCOMPARE( Convert::strToIntDef( "0x12",   static_cast<qint8>(-1) ),  static_cast<qint8>(0x12));
}
//==================================================================================================
void testConvert::test_strToIntDef_qint16()
{
    QCOMPARE( Convert::strToIntDef( "0",      static_cast<qint16>(0) ),  static_cast<qint16>(0)      );
    QCOMPARE( Convert::strToIntDef( "-10500", static_cast<qint16>(0) ),  static_cast<qint16>(-10500) );
    QCOMPARE( Convert::strToIntDef( "error",  static_cast<qint16>(0) ),  static_cast<qint16>(0)      );
    QCOMPARE( Convert::strToIntDef( "12345",  static_cast<qint16>(0) ),  static_cast<qint16>(12345)  );
    QCOMPARE( Convert::strToIntDef( "0x1234", static_cast<qint16>(0) ),  static_cast<qint16>(0x1234) );
}
//==================================================================================================
void testConvert::test_strToIntDef_qint32()
{
    QCOMPARE( Convert::strToIntDef( "0",          static_cast<qint32>(-1) ),  static_cast<qint32>(0)         );
    QCOMPARE( Convert::strToIntDef( "-12345678",  static_cast<qint32>(-1) ),  static_cast<qint32>(-12345678) );
    QCOMPARE( Convert::strToIntDef( "error",      static_cast<qint32>(-1) ),  static_cast<qint32>(-1)        );
    QCOMPARE( Convert::strToIntDef( "12345678",   static_cast<qint32>(-1) ),  static_cast<qint32>(12345678)  );
    QCOMPARE( Convert::strToIntDef( "0x12345678", static_cast<qint32>(-1) ),  static_cast<qint32>(0x12345678));
}
//==================================================================================================
void testConvert::test_strToIntDef_qint64()
{
    QCOMPARE( Convert::strToIntDef( "0",          static_cast<qint64>(-1) ),  static_cast<qint64>(0)         );
    QCOMPARE( Convert::strToIntDef( "-12345678",  static_cast<qint64>(-1) ),  static_cast<qint64>(-12345678) );
    QCOMPARE( Convert::strToIntDef( "error",      static_cast<qint64>(-1) ),  static_cast<qint64>(-1)        );
    QCOMPARE( Convert::strToIntDef( "12345678",   static_cast<qint64>(-1) ),  static_cast<qint64>(12345678)  );
    QCOMPARE( Convert::strToIntDef( "0x123456789", static_cast<qint64>(-1) ),  static_cast<qint64>(0x123456789));
}
//==================================================================================================
void testConvert::test_strToIntDef_quint8()
{
    QCOMPARE( Convert::strToIntDef( "0",     static_cast<quint8>(10) ),  static_cast<quint8>(0)   );
    QCOMPARE( Convert::strToIntDef( "error", static_cast<quint8>(10) ),  static_cast<quint8>(10)  );
    QCOMPARE( Convert::strToIntDef( "123",   static_cast<quint8>(10) ),  static_cast<quint8>(123) );
    QCOMPARE( Convert::strToIntDef( "0x8A",  static_cast<quint8>(10) ),  static_cast<quint8>(0x8A));
}
//==================================================================================================
void testConvert::test_strToIntDef_quint16()
{
    QCOMPARE( Convert::strToIntDef( "0",     static_cast<quint16>(10) ),  static_cast<quint16>(0)    );
    QCOMPARE( Convert::strToIntDef( "error", static_cast<quint16>(10) ),  static_cast<quint16>(10)   );
    QCOMPARE( Convert::strToIntDef( "12345", static_cast<quint16>(10) ),  static_cast<quint16>(12345));
    QCOMPARE( Convert::strToIntDef( "0x8A00",static_cast<quint16>(10) ),  static_cast<quint16>(0x8A00));
}
//==================================================================================================
void testConvert::test_strToIntDef_quint32()
{
    QCOMPARE( Convert::strToIntDef( "0",         static_cast<quint32>(10) ), static_cast<quint32>(0)    );
    QCOMPARE( Convert::strToIntDef( "error",     static_cast<quint32>(10) ), static_cast<quint32>(10)   );
    QCOMPARE( Convert::strToIntDef( "12345",     static_cast<quint32>(10) ), static_cast<quint32>(12345));
    QCOMPARE( Convert::strToIntDef( "0xABCD8A00",static_cast<quint32>(10) ), static_cast<quint32>(0xABCD8A00));
}
//==================================================================================================
void testConvert::test_strToIntDef_quint64()
{
    QCOMPARE( Convert::strToIntDef( "0",           static_cast<quint64>(10) ), static_cast<quint64>(0)    );
    QCOMPARE( Convert::strToIntDef( "error",       static_cast<quint64>(10) ), static_cast<quint64>(10)   );
    QCOMPARE( Convert::strToIntDef( "123456789",   static_cast<quint64>(10) ), static_cast<quint64>(123456789));
    QCOMPARE( Convert::strToIntDef( "0xFFABCD8A00",static_cast<quint64>(10) ), static_cast<quint64>(0xFFABCD8A00));
}
//==================================================================================================
void testConvert::test_doubleToStr()
{
    QLocale c(QLocale::C);
    c.setNumberOptions( QLocale::OmitGroupSeparator );

    QCOMPARE( Convert::doubleToStr( 0.1, 1 ),  c.toString( 0.1, 'f', 1) );
    QCOMPARE( Convert::doubleToStr( 10.123, 3 ), c.toString( 10.123, 'f', 3) );
    QCOMPARE( Convert::doubleToStr( 999.999999, 4 ), c.toString( 999.999999, 'f', 4) );
    QCOMPARE( Convert::doubleToStr( 0.0002, 4 ), c.toString( 0.0002, 'f', 4) );
    QCOMPARE( Convert::doubleToStr( -10.5, 2 ), c.toString( -10.5, 'f', 2) );
}
//==================================================================================================
void testConvert::test_strToDouble()
{
    bool ok = false;
    double result = Convert::strToDouble("0.1", &ok);
    QCOMPARE( ok, true );
    QCOMPARE( qFuzzyCompare(result, 0.1), true );
    result = Convert::strToDouble("-10.5", &ok);
    QCOMPARE( ok, true );
    QCOMPARE( qFuzzyCompare(result, -10.5), true );
    result = Convert::strToDouble("error", &ok);
    QCOMPARE( ok, false );
}
//==================================================================================================
void testConvert::test_strToDateTime()
{
    QCOMPARE( Convert::strToDateTime("2019-03-04 16:43:10"), QDateTime(QDate(2019, 3, 4), QTime(16, 43, 10)) );
    QCOMPARE( Convert::strToDateTime("2033-10-20T10:00:00"), QDateTime(QDate(2033, 10, 20), QTime(10, 0, 0)) );
    QCOMPARE( Convert::strToDateTime("2019-13-32 16:43:10").isValid(), false );
    QCOMPARE( Convert::strToDateTime("22-01-01 12:30:00"), QDateTime(QDate(2022, 1, 1), QTime(12, 30, 0)) );
}
//==================================================================================================
void testConvert::test_lo_quint16()
{
    QCOMPARE( Convert::lo( static_cast<quint16>(0x0000) ), static_cast<quint8>(0x00) );
    QCOMPARE( Convert::lo( static_cast<quint16>(0x1234) ), static_cast<quint8>(0x34) );
    QCOMPARE( Convert::lo( static_cast<quint16>(0xABCD) ), static_cast<quint8>(0xCD) );
    QCOMPARE( Convert::lo( static_cast<quint16>(0xFFFF) ), static_cast<quint8>(0xFF) );
}
//==================================================================================================
void testConvert::test_lo_quint32()
{
    QCOMPARE( Convert::lo( static_cast<quint32>(0x00000000) ), static_cast<quint16>(0x0000) );
    QCOMPARE( Convert::lo( static_cast<quint32>(0x12345678) ), static_cast<quint16>(0x5678) );
    QCOMPARE( Convert::lo( static_cast<quint32>(0xABCDEF98) ), static_cast<quint16>(0xEF98) );
    QCOMPARE( Convert::lo( static_cast<quint32>(0xFFFFFFFF) ), static_cast<quint16>(0xFFFF) );
}
//==================================================================================================
void testConvert::test_lo_quint64()
{
    QCOMPARE( Convert::lo( static_cast<quint64>(0x0000000000000000) ), static_cast<quint32>(0x00000000) );
    QCOMPARE( Convert::lo( static_cast<quint64>(0xABCDEF9012345678) ), static_cast<quint32>(0x12345678) );
    QCOMPARE( Convert::lo( static_cast<quint64>(0x12345678ABCDEF98) ), static_cast<quint32>(0xABCDEF98) );
    QCOMPARE( Convert::lo( static_cast<quint64>(0xFFFFFFFFFFFFFFFF) ), static_cast<quint32>(0xFFFFFFFF) );
}
//==================================================================================================
void testConvert::test_hi_quint16()
{
    QCOMPARE( Convert::hi( static_cast<quint16>(0x0000) ), static_cast<quint8>(0x00) );
    QCOMPARE( Convert::hi( static_cast<quint16>(0x1234) ), static_cast<quint8>(0x12) );
    QCOMPARE( Convert::hi( static_cast<quint16>(0xABCD) ), static_cast<quint8>(0xAB) );
    QCOMPARE( Convert::hi( static_cast<quint16>(0xFFFF) ), static_cast<quint8>(0xFF) );
}
//==================================================================================================
void testConvert::test_hi_quint32()
{
    QCOMPARE( Convert::hi( static_cast<quint32>(0x00000000) ), static_cast<quint16>(0x0000) );
    QCOMPARE( Convert::hi( static_cast<quint32>(0x12345678) ), static_cast<quint16>(0x1234) );
    QCOMPARE( Convert::hi( static_cast<quint32>(0xABCDEF98) ), static_cast<quint16>(0xABCD) );
    QCOMPARE( Convert::hi( static_cast<quint32>(0xFFFFFFFF) ), static_cast<quint16>(0xFFFF) );
}
//==================================================================================================
void testConvert::test_hi_quint64()
{
    QCOMPARE( Convert::hi( static_cast<quint64>(0x0000000000000000) ), static_cast<quint32>(0x00000000) );
    QCOMPARE( Convert::hi( static_cast<quint64>(0xABCDEF9012345678) ), static_cast<quint32>(0xABCDEF90) );
    QCOMPARE( Convert::hi( static_cast<quint64>(0x12345678ABCDEF98) ), static_cast<quint32>(0x12345678) );
    QCOMPARE( Convert::hi( static_cast<quint64>(0xFFFFFFFFFFFFFFFF) ), static_cast<quint32>(0xFFFFFFFF) );
}
//==================================================================================================
void testConvert::test_reverse_quint16()
{
    QCOMPARE( Convert::reverse( static_cast<quint16>(0x0000) ), static_cast<quint16>(0x0000) );
    QCOMPARE( Convert::reverse( static_cast<quint16>(0x1234) ), static_cast<quint16>(0x3412) );
    QCOMPARE( Convert::reverse( static_cast<quint16>(0xFFFF) ), static_cast<quint16>(0xFFFF) );
}
//==================================================================================================
void testConvert::test_reverse_quint32()
{
    QCOMPARE( Convert::reverse( static_cast<quint32>(0x00000000) ), static_cast<quint32>(0x00000000) );
    QCOMPARE( Convert::reverse( static_cast<quint32>(0x12345678) ), static_cast<quint32>(0x78563412) );
    QCOMPARE( Convert::reverse( static_cast<quint32>(0xFFFFFFFF) ), static_cast<quint32>(0xFFFFFFFF) );
}
//==================================================================================================
void testConvert::test_reverse_quint64()
{
    QCOMPARE( Convert::reverse( static_cast<quint64>(0x0000000000000000) ), static_cast<quint64>(0x0000000000000000) );
    QCOMPARE( Convert::reverse( static_cast<quint64>(0x123456789ABCDEF0) ), static_cast<quint64>(0xF0DEBC9A78563412) );
    QCOMPARE( Convert::reverse( static_cast<quint64>(0xFFFFFFFFFFFFFFFF) ), static_cast<quint64>(0xFFFFFFFFFFFFFFFF) );
}
//==================================================================================================
void testConvert::test_isASCII_qint8()
{
    QCOMPARE( Convert::isASCII( static_cast<qint8>(0) ), false );
    QCOMPARE( Convert::isASCII( static_cast<qint8>(32) ), true );
    QCOMPARE( Convert::isASCII( static_cast<qint8>('A') ), true );
    QCOMPARE( Convert::isASCII( static_cast<qint8>(-10) ), false );
}
//==================================================================================================
void testConvert::test_isASCII_quint8()
{
    QCOMPARE( Convert::isASCII( static_cast<quint8>(0) ), false );
    QCOMPARE( Convert::isASCII( static_cast<quint8>(32) ), true );
    QCOMPARE( Convert::isASCII( static_cast<quint8>('A') ), true );
    QCOMPARE( Convert::isASCII( static_cast<quint8>(0xFF) ), false );
}
//==================================================================================================
void testConvert::test_isASCII_char()
{
    QString s = "Ж";
    QCOMPARE( Convert::isASCII( '0' ), true );
    QCOMPARE( Convert::isASCII( 'A' ), true );
    QCOMPARE( Convert::isASCII( 'x' ), true );
    QCOMPARE( Convert::isASCII( static_cast<char>( s.toUtf8().at(0) ) ), false );
}
//==================================================================================================
void testConvert::test_endLineToHTML()
{
    QCOMPARE( Convert::endLineToHTML( "This is\nmultiline\nstring." ), "This is<br>multiline<br>string." );
    QCOMPARE( Convert::endLineToHTML( "Текст с\nпереносом\nстрок." ), "Текст с<br>переносом<br>строк." );
}
//==================================================================================================
void testConvert::test_encodeXMLText()
{
    QCOMPARE( Convert::encodeXMLText( "Test convert <text> to \"XML\" format.\r\nUnit&test." ),
              "Test convert &lt;text&gt; to &quot;XML&quot; format.&#13;&#10;Unit&amp;test." );
}
//==================================================================================================
void testConvert::test_decodeXMLText()
{
    QCOMPARE( Convert::decodeXMLText( "Test convert &lt;text&gt; to &quot;XML&quot; format.&#13;&#10;Unit&amp;test." ),
              "Test convert <text> to \"XML\" format.\r\nUnit&test." );
}
//==================================================================================================
void testConvert::test_changeDecimalSeparator()
{
    QCOMPARE( Convert::changeDecimalSeparator("100" ), "100" );
    QCOMPARE( Convert::changeDecimalSeparator("100,500", '.' ), "100.500" );
    QCOMPARE( Convert::changeDecimalSeparator("0.100", '-' ), "0-100" );
    QCOMPARE( Convert::changeDecimalSeparator("100,500", '.' ), "100.500" );
}
//==================================================================================================
void testConvert::test_changeLineFit()
{
    QCOMPARE( Convert::changeLineFit( "This is\nmultiline\nstring.", "\r" ),
              "This is\rmultiline\rstring." );
    QCOMPARE( Convert::changeLineFit( "This is\r\nmultiline\r\nstring.", "\n" ),
              "This is\nmultiline\nstring." );
    QCOMPARE( Convert::changeLineFit( "This is\nmultiline\rstring.", "<br>" ),
              "This is<br>multiline<br>string." );
}
//==================================================================================================

QTEST_APPLESS_MAIN(testConvert)

#include "tst_testconvert.moc"
