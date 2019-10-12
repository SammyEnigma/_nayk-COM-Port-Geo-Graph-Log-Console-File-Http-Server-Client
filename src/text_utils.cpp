/****************************************************************************
** Copyright (c) 2019 Evgeny Teterin (nayk) <sutcedortal@gmail.com>
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
#include <QLocale>
#include <QMap>
#include "convert.h"
#include "text_utils.h"

namespace nayk {
//==================================================================================================
const QMap<QString, QString> translitMap{

    {"ай", "ay"},
    {"ей", "ey"},
    {"ий", "iy"},
    {"ой", "oy"},
    {"уй", "uy"},
    {"ый", "yy"},
    {"эй", "ey"},
    {"юй", "yuy"},
    {"ей", "yay"},
    {"а", "a"},
    {"б", "b"},
    {"в", "v"},
    {"г", "g"},
    {"д", "d"},
    {"е", "ye"},
    {"ё", "ye"},
    {"ж", "zh"},
    {"з", "z"},
    {"и", "i"},
    {"й", "y"},
    {"к", "k"},
    {"л", "l"},
    {"м", "m"},
    {"н", "n"},
    {"о", "o"},
    {"п", "p"},
    {"р", "r"},
    {"с", "s"},
    {"т", "t"},
    {"у", "u"},
    {"ф", "f"},
    {"х", "kh"},
    {"ц", "ts"},
    {"ч", "ch"},
    {"ш", "sh"},
    {"щ", "shch"},
    {"ъ", "``"},
    {"ы", "y"},
    {"ь", "`"},
    {"э", "e"},
    {"ю", "yu"},
    {"я", "ya"}
};

//==================================================================================================
QString TextUtils::reverse(const QString &text)
{
    if(text.length() < 2) return text;

    QString result = text;
    for (int i=0; i < result.length()/2; ++i) result = swapChars(result, i, result.length() - 1 - i);
    return result;
}
//==================================================================================================
QString TextUtils::translit(const QString &text)
{
    if(text.isEmpty()) return text;

    QString result = text;
    for(int i=0; i < translitMap.keys().size(); ++i) {

        QString key = translitMap.keys().at(i);
        QString val = translitMap.value(key);

        while( result.toLower().contains( key.toLower() ) ) {

            int n = result.toLower().indexOf( key.toLower() );
            QString after = val;
            if(result[n] != key[0]) after[0] = after.at(0).toUpper();

            result = result.left( n ) + after + result.mid( n + key.length() );
        }
    }
    if(text.isUpper()) result = result.toUpper();
    return result;
}
//==================================================================================================
QString TextUtils::swapChars(const QString &text, int index1, int index2)
{
    if((index1 < 0) || (index1 >= text.length()) || (index2 < 0) || (index2 >= text.length()))
        return text;

    QString result = text;
    result[index1] = text[index2];
    result[index2] = text[index1];
    return result;
}
//==================================================================================================

//==================================================================================================
} // namespace nayk

