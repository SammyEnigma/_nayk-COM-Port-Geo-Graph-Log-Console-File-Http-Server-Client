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
#ifndef NAYK_SYSUTILS_H
#define NAYK_SYSUTILS_H

#include <QObject>
#include <QDateTime>

//=========================================================================================================
namespace nayk {
//=========================================================================================================

//=========================================================================================================
class System
{
public:
    static void pause(int ms = 1000);
    static void pauseMS(int ms = 1000) { pause(ms); }
    static void pauseSec(int sec = 1) { pause(sec * 1000); }
    static void pauseMin(int min = 1) { pauseSec(min * 60); }
    static bool slotExists(QObject *obj, const char *slot_sign);
    static bool isSummerTime(QDateTime dateTime);
    static int dayOfWeek_Sakamoto(int year, int month, int day);
    static int dayOfWeek(int year, int month, int day);
    static QString generatePas(int len = 8, bool onlyNum = false);
    static qint32 generateId32();
    static qint64 generateId64();
    static qint64 floordiv(qint64 a, int b);
    static int floordiv(int a, int b);
    static qint64 julianDayFromDate(int year, int month, int day);
    static bool osCmd(const QString &cmd, QString &out, int timeout=5000);
    static QString osName();
    static QString osVersion();
    static bool os64bit();
    //
    System() = delete;
};

//=========================================================================================================
} // namespace nayk

//=========================================================================================================
#endif // NAYK_SYSUTILS_H
