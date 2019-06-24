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
#ifndef NAYK_CONSOLE_H
#define NAYK_CONSOLE_H

#include <QtCore>
#include <QVariant>
#include <QRect>
#include <QSize>

//=========================================================================================================
namespace nayk {
//=========================================================================================================

//=========================================================================================================
class Console
{
public:
    static const int colorBlack         = 0;
    static const int colorRed           = 1;
    static const int colorGreen         = 2;
    static const int colorYellow        = 3;
    static const int colorBlue          = 4;
    static const int colorMagenta       = 5;
    static const int colorCyan          = 6;
    static const int colorWhite         = 7;
    static const int colorBrightBlack   = 8;
    static const int colorBrightRed     = 9;
    static const int colorBrightGreen   = 10;
    static const int colorBrightYellow  = 11;
    static const int colorBrightBlue    = 12;
    static const int colorBrightMagenta = 13;
    static const int colorBrightCyan    = 14;
    static const int colorBrightWhite   = 15;
    //
    static void clear();
    static void clearUp();
    static void clearDown();
    static void setPos(int row, int col);
    static void setPosUp(int step = 1);
    static void setPosDown(int step = 1);
    static void setPosForward(int step = 1);
    static void setPosBack(int step = 1);
    static void toNextLine(int col = 1);
    static void toPrevLine(int col = 1);
    static void eraseLine();
    static void eraseLineLeft();
    static void eraseLineRight();
    static void savePos();
    static void restorePos();
    static void hideCursor();
    static void showCursor();
    static void setCursorVisible(bool visible = true);
    static void write(int row, int col, const QString &text);
    static void write(const QString &text);
    static QVariant read(const QVariant &defaultValue = QVariant());
    static void resetAttributes();
    static void setColors(int textColor = colorWhite, int bgColor = colorBlack);
    static void setTextColor(int color = colorWhite);
    static void setBgColor(int color = colorBlack);
    static void blink(bool on = true);
    static void frame(int row, int col, int width, int height, bool doubleBorder = false, int color = -1);
    static void rectangle(int row, int col, int width, int height, int color = -1);
    static void frame(const QRect &rect, bool doubleBorder = false, int color = -1);
    static void rectangle(const QRect &rect, int color = -1);
    static QSize getSize(const QSize &defaultSize = QSize(80, 25));
    static int width();
    static int height();
    //
    Console() = delete;
};

//=========================================================================================================
} // namespace nayk

//=========================================================================================================
#endif // NAYK_CONSOLE_H
