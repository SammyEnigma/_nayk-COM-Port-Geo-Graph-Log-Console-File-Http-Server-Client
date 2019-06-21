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
#include <QTextStream>
#include <QTextCodec>

#include "console.h"

namespace nayk {
//==================================================================================================
void Console::clear()
{
    QTextStream out(stdout);
    out << QString("\033[2J");
}
//==================================================================================================
void Console::savePos()
{
    QTextStream out(stdout);
    out << QString("\033[s");
}
//==================================================================================================
void Console::restorePos()
{
    QTextStream out(stdout);
    out << QString("\033[u");
}
//==================================================================================================
void Console::setPos(int row, int col)
{
    QTextStream out(stdout);
    out << QString("\033[%1;%2H").arg(row).arg(col);
}
//==================================================================================================
void Console::write(int row, int col, const QString &text)
{
    setPos(row, col);
    write(text);
}
//==================================================================================================
void Console::write(const QString &text)
{
    QTextStream out(stdout);
    out << text;
}
//==================================================================================================
QVariant Console::read(const QVariant &defaultValue)
{
    QTextStream in(stdin);
    QString str = in.readLine();
    return (str.isEmpty() ? defaultValue : str);
}
//==================================================================================================
void Console::hideCursor()
{
    QTextStream out(stdout);
    out << QString("\033[?25l");
}
//==================================================================================================
void Console::showCursor()
{
    QTextStream out(stdout);
    out << QString("\033[?25h");
}
//==================================================================================================
void Console::setCursorVisible(bool visible)
{
    if(visible)
        showCursor();
    else
        hideCursor();
}
//==================================================================================================
void Console::resetAttributes()
{
    QTextStream out(stdout);
    out << QString("\033[0m");
}
//==================================================================================================
void Console::setColors(int textColor, int bgColor)
{
    QTextStream out(stdout);
    bool bright = false;
    if(textColor > 7) {
        bright = true;
        textColor = textColor - 8;
    }
    if(bgColor > 7) {
        bright = true;
        bgColor = bgColor - 8;
    }
    out << QString("\033[%1;%2%3m").arg(30+textColor).arg(40+bgColor).arg(bright ? ";1" : "");
}
//==================================================================================================
void Console::setTextColor(int color)
{
    QTextStream out(stdout);
    bool bright = false;
    if(color > 7) {
        bright = true;
        color = color - 8;
    }
    out << QString("\033[%1%2m").arg(30+color).arg(bright ? ";1" : "");
}
//==================================================================================================
void Console::setBgColor(int color)
{
    QTextStream out(stdout);
    bool bright = false;
    if(color > 7) {
        bright = true;
        color = color - 8;
    }
    out << QString("\033[%1%2m").arg(40+color).arg(bright ? ";1" : "");
}
//==================================================================================================
void Console::blink(bool on)
{
    QTextStream out(stdout);
    out << QString("\033[%1m").arg(on ? 5 : 25);
}
//==================================================================================================
void Console::frame(int row, int col, int width, int height, bool doubleBorder)
{
    QTextStream out(stdout);
    out << QString("\033[%1;%2H").arg(row).arg(col);
    out << QString(doubleBorder ? "╔" : "┌");
    for (int i=0; i<width-2; ++i) {
        out << QString(doubleBorder ? "═" : "─");
    }
    out << QString(doubleBorder ? "╗" : "┐");
    for (int i=0; i<height-2; ++i) {
        out << QString("\033[%1;%2H").arg(row+1+i).arg(col);
        out << QString(doubleBorder ? "║" : "│");
        out << QString("\033[%1;%2H").arg(row+1+i).arg(col+width-1);
        out << QString(doubleBorder ? "║" : "│");
    }
    out << QString("\033[%1;%2H").arg(row+height-1).arg(col);
    out << QString(doubleBorder ? "╚" : "└");
    for (int i=0; i<width-2; ++i) {
        out << QString(doubleBorder ? "═" : "─");
    }
    out << QString(doubleBorder ? "╝" : "┘");
}
//==================================================================================================
void Console::rectangle(int row, int col, int width, int height, int bgColor, int frameColor,
                          bool showFrame, bool doubleBorder)
{
    QTextStream out(stdout);
    bool bright = false;
    if(bgColor > 7) {
        bright = true;
        bgColor = bgColor - 8;
    }
    out << QString("\033[%1%2m").arg(40+bgColor).arg(bright ? ";1" : "");
    for (int y=row; y<row+height; ++y) {

        out << QString("\033[%1;%2H").arg(y).arg(col);
        for (int i=0; i<width; ++i) {
            out << QString(" ");
        }
    }

    if(showFrame) {
        bright = false;
        if(frameColor > 7) {
            bright = true;
            frameColor = frameColor - 8;
        }
        out << QString("\033[%1;%2%3m").arg(30+frameColor).arg(40+bgColor).arg(bright ? ";1" : "");
        frame(row, col, width, height, doubleBorder);
    }
}
//==================================================================================================
} // namespace nayk

