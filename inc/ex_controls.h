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
#ifndef NAYK_EX_CONTROLS_H
#define NAYK_EX_CONTROLS_H

#include <QSpinBox>
#include <QKeyEvent>

//=========================================================================================================
namespace nayk {
//=========================================================================================================
class ExSpinBox: public QSpinBox
{
    Q_OBJECT

    Q_PROPERTY(int leadingZero READ leadingZero WRITE setLeadingZero)

public:
    explicit ExSpinBox( QWidget * parent = nullptr) : QSpinBox(parent) { }

    bool leadingZero() const { return _lZero; }
    void setLeadingZero(bool lZero);
    virtual QString textFromValue ( int value ) const override;

signals:
    void returnPressed();
    void keyPressed(int key);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    bool _lZero {false};
};
//=========================================================================================================


//=========================================================================================================
} // namespace nayk

//=========================================================================================================
#endif // NAYK_EX_CONTROLS_H
