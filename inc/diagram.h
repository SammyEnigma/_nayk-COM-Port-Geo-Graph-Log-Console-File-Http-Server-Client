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
#ifndef NAYK_DIAGRAM_H
#define NAYK_DIAGRAM_H
// Qt:
#include <QObject>
#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QEvent>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarCategoryAxis>
#include <QtPrintSupport/QPrinter>

namespace nayk {
//=======================================================================================
using namespace QtCharts;

//=======================================================================================
class MultiChart : public QChartView
{
    Q_OBJECT

public:
    MultiChart(QWidget * parent = nullptr, const QString &chartTitle = QString() );
    ~MultiChart();
    void addChart(const QVector<qreal> &values, const QString &title, QColor color = QColor());
    void delChart(int index);
    void setOptions(const QStringList &xCaptions, int precise = 2);
    void setChartTitleText(const QString &text);
    void setXTitleText(const QString &text);
    void setYTitleText(const QString &text);
    bool exportToFile(const QString &fileName = QString());
    void printPreview();
    void setBarChartVisible(bool visible);
    void setLineChartVisible(bool visible);
    void setPointLabelsVisible(bool visible);
    void resetGraphic();
    void clear();
    int chartCount() { return chartList.size(); }
    void zoomReset();
    void zoomIn();
    void zoomOut();
    void stepUp(qreal step = -1);
    void stepDown(qreal step = -1);
    void stepLeft(qreal step = -1);
    void stepRight(qreal step = -1);
    void setStep(qreal val) { _step = qBound(5.0, val, 200.0); }
    void setBaseFontSizePixels(int fontSize) { _fontSize = qBound(2, fontSize, 40); updateFontsAndColors(); }

private:

    typedef struct ChartStruct {
        QBarSeries* bs {nullptr};
        QLineSeries* ls {nullptr};
        bool visible {true};
    } ChartStruct;

    QBarCategoryAxis *axisX {nullptr};
    QValueAxis *axisY {nullptr};
    QChart *chart {nullptr};
    QList<ChartStruct> chartList;
    qreal maxVal {0.05};
    qreal minVal {0.0};
    int _precise {2};
    bool _lineChartVisible {true};
    bool _barChartVisible {true};
    bool actionDisable;
    QStringList _captions;
    bool m_isTouching {false};
    QPoint pos;
    qreal _step {20};
    int _fontSize {12};
    //
    void updateFontsAndColors();
    void updateLegend();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void print(QPrinter*);
    void on_legendMarkerClicked();
};
//=======================================================================================
} // namespace
#endif // NAYK_DIAGRAM_H
