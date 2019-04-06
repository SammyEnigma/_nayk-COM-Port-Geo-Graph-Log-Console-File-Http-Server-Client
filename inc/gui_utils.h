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
#ifndef NAYK_GUI_UTILS_H
#define NAYK_GUI_UTILS_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QLayout>

//=========================================================================================================
namespace nayk {
//=========================================================================================================

//=========================================================================================================
class Gui
{
public:
    static void clearTableWidget(QTableWidget *table);
    static void clearTableWidgetBody(QTableWidget *table);
    static void removeTableWidgetRow(QTableWidget *table, int row);
    static void resizeTableToContents(QTableWidget *table);
    static void swapTableRows(QTableWidget *table, int row1, int row2);
    static void copyTableToClipboard(QTableWidget *table);
    static bool searchTextInTable(QTableWidget *table, const QString &searchText);
    static void msgError(const QString &txt);
    static void msgWarning(const QString &txt);
    static void msgInfo(const QString &txt);
    static bool msgConfirm(const QString &txt);
    static int msgDialog(const QString &txt);
    static void msgError(QWidget *parent, const QString &txt);
    static void msgWarning(QWidget *parent, const QString &txt);
    static void msgInfo(QWidget *parent, const QString &txt);
    static bool msgConfirm(QWidget *parent, const QString &txt);
    static int msgDialog(QWidget *parent, const QString &txt);
    static QWidget* getMainWindowWidget();
    static void clearWidgets(QLayout *layout);
    static void swapWidgets(QWidget *w1, QWidget *w2);
    static bool saveControlValue(QWidget *w, const QString &fileName, const QString &prefixKey = QString());
    static bool loadControlValue(QWidget *w, const QString &fileName, const QString &prefixKey = QString());
    //
    Gui() = delete;
};

//=========================================================================================================
} // namespace nayk

//=========================================================================================================
#endif // NAYK_GUI_UTILS_H
