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
#include "convert.h"

#ifdef Q_OS_WIN
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#endif

namespace nayk {
//==================================================================================================
void Console::clear()
{
    QTextStream out(stdout);
    out << QString("\033[2J");
}
//==================================================================================================
void clearUp()
{
    QTextStream out(stdout);
    out << QString("\033[1J");
}
//==================================================================================================
void clearDown()
{
    QTextStream out(stdout);
    out << QString("\033[0J");
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
void Console::setPosUp(int step)
{
    QTextStream out(stdout);
    out << QString("\033[%1A").arg(step);
}
//==================================================================================================
void Console::setPosDown(int step)
{
    QTextStream out(stdout);
    out << QString("\033[%1B").arg(step);
}
//==================================================================================================
void Console::setPosBack(int step)
{
    QTextStream out(stdout);
    out << QString("\033[%1D").arg(step);
}
//==================================================================================================
void Console::setPosForward(int step)
{
    QTextStream out(stdout);
    out << QString("\033[%1C").arg(step);
}
//==================================================================================================
void Console::toNextLine(int col)
{
    QTextStream out(stdout);
    out << QString("\033[%1E").arg(col);
}
//==================================================================================================
void Console::toPrevLine(int col)
{
    QTextStream out(stdout);
    out << QString("\033[%1F").arg(col);
}
//==================================================================================================
void Console::eraseLine()
{
    QTextStream out(stdout);
    out << QString("\033[2K");
}
//==================================================================================================
void Console::eraseLineLeft()
{
    QTextStream out(stdout);
    out << QString("\033[1K");
}
//==================================================================================================
void Console::eraseLineRight()
{
    QTextStream out(stdout);
    out << QString("\033[0K");
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
    out << QString("\033[%1;%2%3m").arg(40+bgColor).arg(30+textColor).arg(bright ? ";1" : "");
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
void Console::frame(int row, int col, int width, int height, bool doubleBorder, int color)
{
    if(color >= 0) setTextColor(color);

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
void Console::rectangle(int row, int col, int width, int height, int color)
{
    if(color >= 0) setBgColor(color);

    QTextStream out(stdout);

    for (int y=row; y<row+height; ++y) {

        out << QString("\033[%1;%2H").arg(y).arg(col);
        for (int i=0; i<width; ++i) {
            out << QString(" ");
        }
    }
}
//==================================================================================================
void Console::frame(const QRect &rect, bool doubleBorder, int color)
{
    frame(rect.top(), rect.left(), rect.width(), rect.height(), doubleBorder, color);
}
//==================================================================================================
void Console::rectangle(const QRect &rect, int color)
{
    rectangle(rect.top(), rect.left(), rect.width(), rect.height(), color);
}
//==================================================================================================
QSize Console::getSize(const QSize &defaultSize)
{
    int columns = 0, rows = 0;
#ifdef Q_OS_WIN
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    columns = w.ws_col;
    rows = w.ws_row;
#endif

    if(columns <= 0) columns = defaultSize.width();
    if(rows <= 0) rows = defaultSize.height();
    return QSize(columns, rows);
}
//==================================================================================================
int Console::width()
{
    return getSize().width();
}
//==================================================================================================
int Console::height()
{
    return getSize().height();
}
//==================================================================================================
} // namespace nayk

