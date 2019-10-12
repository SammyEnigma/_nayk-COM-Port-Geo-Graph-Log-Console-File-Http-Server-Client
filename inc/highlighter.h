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
#ifndef NAYK_HIGHLIGHTER_H
#define NAYK_HIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
class QTextDocument;
class QTextCharFormat;
QT_END_NAMESPACE

namespace nayk {

enum HighlightSyntax { SyntaxSQL, SyntaxHTML, SyntaxCPP };

//========================================================================================================================
class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = nullptr, HighlightSyntax syntax = SyntaxSQL, bool darkBackground = false);

protected:
    void highlightBlock(const QString &text) override;

private:
    // Состояние подсветки, в которой находится текстовый блок на момент его закрытия
    enum States {
        None,       // Без подсветки
        Tag,        // Подсветка внутри тега
        Comment,    // Внутри комментария
        Quote       // Внутри кавычек, которые внутри тега
    };

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    HighlightSyntax _syntax;
    QVector<HighlightingRule> startTagRules;    // Правила форматирования для открывающих тегов
    QVector<HighlightingRule> endTagRules;      // Правила форматирования для закрывающих тегов
    QVector<HighlightingRule> highlightingRules;
    QRegularExpression openTag;                 // Символ открыватия тега - "<"
    QRegularExpression closeTag;                // Символ закрытия тег    - ">"
    QTextCharFormat edgeTagFormat;              // Форматирование символов openTag и closeTag
    QTextCharFormat insideTagFormat;            // Форматирование текста внутри тега
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;
    QRegularExpression quotes;                  // Регулярное выражение для текста в кавычках внутри тега
    QTextCharFormat tagsFormat;                 // Форматирование самих тегов
    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    //
    void highlightBlockHtml(const QString &text);
};
//========================================================================================================================
} // namespace
#endif // NAYK_HIGHLIGHTER_H
