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
#include <QPainterPath>

#include "graph.h"
#include "filesys.h"

namespace nayk {
//=======================================================================================================
bool Graph::drawImage(QPainter* painter, const QString &fileName, double x, double y, double width, double height)
{
    return drawImage(painter, fileName, QRectF(x, y, width, height) );
}
//=======================================================================================================
bool Graph::drawImage(QPainter* painter, const QString &fileName, const QRectF &rectF)
{
    if(!painter || fileName.isNull() || fileName.isEmpty()) return false;
    QImage img;
    if(!img.load( fileName )) return false;
    return drawImage(painter, img, rectF);
}
//=======================================================================================================
bool Graph::drawImage(QPainter* painter, const QImage &image, double x, double y, double width, double height)
{
    return drawImage(painter, image, QRectF(x, y, width, height) );
}
//=======================================================================================================
bool Graph::drawImage(QPainter* painter, const QImage &image, const QRectF &rectF)
{
    if(!painter) return false;
    painter->drawImage( rectF, image );
    return true;
}
//=======================================================================================================
bool Graph::drawRectangle(QPainter* painter, double x, double y, double width, double height,
                          const QColor &bgColor, const QColor &borderColor, double borderWidth,
                          double topRadius, double bottomRadius)
{
    return drawRectangle( painter, QRectF(x, y, width, height), bgColor, borderColor,
                          borderWidth, topRadius, bottomRadius);
}
//=======================================================================================================
bool Graph::drawRectangle(QPainter* painter, double x, double y, double width, double height,
                          const QJsonArray &bgColor, const QJsonArray &borderColor, double borderWidth,
                          double topRadius, double bottomRadius)
{
    return drawRectangle( painter, QRectF(x, y, width, height), colorFromArray(bgColor), colorFromArray(borderColor),
                          borderWidth, topRadius, bottomRadius);
}
//=======================================================================================================
bool Graph::drawRectangle(QPainter* painter, const QRectF &rect,
                          const QJsonArray &bgColor, const QJsonArray &borderColor, double borderWidth,
                          double topRadius, double bottomRadius)
{
    return drawRectangle( painter, rect, colorFromArray(bgColor), colorFromArray(borderColor),
                          borderWidth, topRadius, bottomRadius);
}
//=======================================================================================================
bool Graph::drawRectangle(QPainter* painter, const QRectF &rect,
                          const QColor &bgColor, const QColor &borderColor, double borderWidth,
                          double topRadius, double bottomRadius)
{
    if(!painter) return false;

    double topDiametr = 2.0 * topRadius;
    double bottomDiametr = 2.0 * bottomRadius;

    QPainterPath path;

    path.moveTo( rect.left() + topRadius, rect.top() );
    path.arcTo( rect.left(), rect.top(), topDiametr, topDiametr, 90.0, 90.0 );

    path.lineTo( rect.left(), rect.bottom() - bottomRadius );
    path.arcTo( rect.left(), rect.bottom() - bottomDiametr, bottomDiametr, bottomDiametr, 180.0, 90.0 );

    path.lineTo( rect.right() - bottomRadius, rect.bottom() );
    path.arcTo( rect.right() - bottomDiametr, rect.bottom() - bottomDiametr, bottomDiametr, bottomDiametr, 270.0, 90.0 );

    path.lineTo( rect.right(), rect.top() + topRadius );
    path.arcTo( rect.right() - topDiametr, rect.top(), topDiametr, topDiametr, 0.0, 90.0 );

    path.closeSubpath();

    painter->setPen( QPen(QBrush(borderColor), borderWidth) );
    painter->setBrush( QBrush(bgColor) );
    painter->fillPath(path, QBrush(bgColor));
    painter->drawPath(path);

    return true;
}
//=======================================================================================================
bool Graph::drawCircle(QPainter* painter, double x, double y, double radius,
                       const QColor &bgColor, const QColor &borderColor, double borderWidth )
{
    return drawCircle(painter, QPointF(x, y), radius, bgColor, borderColor, borderWidth );
}
//=======================================================================================================
bool Graph::drawCircle(QPainter* painter, double x, double y, double radius,
                       const QJsonArray &bgColor, const QJsonArray &borderColor, double borderWidth )
{
    return drawCircle(painter, QPointF(x, y), radius, colorFromArray(bgColor), colorFromArray(borderColor), borderWidth );
}
//=======================================================================================================
bool Graph::drawCircle(QPainter* painter, const QPoint &centerPoint, double radius,
                       const QJsonArray &bgColor, const QJsonArray &borderColor, double borderWidth )
{
    return drawCircle(painter, static_cast<double>(centerPoint.x()), static_cast<double>(centerPoint.y()), radius,
                      colorFromArray(bgColor), colorFromArray(borderColor), borderWidth );
}
//=======================================================================================================
bool Graph::drawCircle(QPainter* painter, const QPointF &centerPoint, double radius,
                       const QJsonArray &bgColor, const QJsonArray &borderColor, double borderWidth )
{
    return drawCircle(painter, centerPoint, radius, colorFromArray(bgColor), colorFromArray(borderColor), borderWidth );
}
//=======================================================================================================
bool Graph::drawCircle(QPainter* painter, const QPointF &centerPoint, double radius,
                       const QColor &bgColor, const QColor &borderColor, double borderWidth )
{
    if(!painter) return false;

    painter->setBrush( QBrush(bgColor) );
    painter->setPen( QPen( QBrush(borderColor), borderWidth ) );
    painter->drawEllipse(centerPoint, radius, radius);
    return true;
}
//=======================================================================================================
bool Graph::drawCircle(QPainter* painter, const QPoint &centerPoint, double radius,
                       const QColor &bgColor, const QColor &borderColor, double borderWidth )
{
    return drawCircle(painter, static_cast<double>(centerPoint.x()), static_cast<double>(centerPoint.y()), radius,
                      bgColor, borderColor, borderWidth );
}
//=======================================================================================================
bool Graph::drawText(QPainter* painter, double x, double y, const QString &text,
                     const QString &fontFace, double fontSize, double fontWeight, const QColor &color,
                     Qt::Alignment align, const QColor &shadowColor, int shadow_cx, int shadow_cy)
{
    if(!painter) return false;

    QFont font = painter->font();
    font.setFamily( fontFace );
    font.setPointSizeF( fontSize );
    font.setWeight( qRound( fontWeight * 100 ) );
    painter->setFont(font);

    QRectF rr = painter->boundingRect( QRect(0,0,10000,10000), text );

    if((align & Qt::AlignHCenter) == Qt::AlignHCenter) {
        x = x - rr.width()/2;
    }
    else if((align & Qt::AlignRight) == Qt::AlignRight) {
        x = x - rr.width();
    }

    if((align & Qt::AlignVCenter) == Qt::AlignVCenter) {
        y = y - rr.height()/2;
    }
    else if((align & Qt::AlignBottom) == Qt::AlignBottom) {
        y = y - rr.height();
    }

    QRectF textRect;
    textRect.setLeft( x );
    textRect.setTop( y );
    textRect.setWidth( rr.width() );
    textRect.setHeight( rr.height() );

    if(shadowColor.alpha() > 0.02) {
        QRectF textRectShadow = textRect;
        textRectShadow.setLeft( x + shadow_cx );
        textRectShadow.setTop( y + shadow_cy );
        painter->setPen( QPen(shadowColor) );
        painter->drawText(textRectShadow, static_cast<int>(align), text);
    }

    painter->setPen( QPen(color) );
    painter->drawText(textRect, static_cast<int>(align), text);

    return true;
}
//=======================================================================================================
bool Graph::drawText(QPainter* painter, double x, double y, const QString &text,
                     const QString &fontFace, double fontSize, double fontWeight, const QJsonArray &color,
                     Qt::Alignment align, const QJsonArray &shadowColor, int shadow_cx, int shadow_cy)
{
    return drawText(painter, x, y, text, fontFace, fontSize, fontWeight, colorFromArray(color),
                    align, colorFromArray(shadowColor), shadow_cx, shadow_cy);
}
//=======================================================================================================
bool Graph::drawText(QPainter* painter, QPointF pos, const QString &text,
                     const QString &fontFace, double fontSize, double fontWeight, const QColor &color,
                     Qt::Alignment align, const QColor &shadowColor, int shadow_cx, int shadow_cy)
{
    return drawText(painter, pos.x(), pos.y(), text, fontFace, fontSize, fontWeight, color,
                    align, shadowColor, shadow_cx, shadow_cy);
}
//=======================================================================================================
bool Graph::drawText(QPainter* painter, QPointF pos, const QString &text,
                     const QString &fontFace, double fontSize, double fontWeight, const QJsonArray &color,
                     Qt::Alignment align, const QJsonArray &shadowColor, int shadow_cx, int shadow_cy)
{
    return drawText(painter, pos.x(), pos.y(), text, fontFace, fontSize, fontWeight, color,
                    align, shadowColor, shadow_cx, shadow_cy);
}
//=======================================================================================================
QColor Graph::colorFromArray(const QJsonArray &arr)
{
    quint8 r = static_cast<quint8>(arr.size() > 0 ? arr.at(0).toInt() : 0);
    quint8 g = static_cast<quint8>(arr.size() > 1 ? arr.at(1).toInt() : 0);
    quint8 b = static_cast<quint8>(arr.size() > 2 ? arr.at(2).toInt() : 0);
    quint8 a = static_cast<quint8>(arr.size() > 3 ? arr.at(3).toInt() : 255);

    return QColor(r, g, b, a);
}
//=======================================================================================================
QColor Graph::colorFromArray(const QByteArray &arr)
{
    quint8 r = static_cast<quint8>(arr.size() > 0 ? arr.at(0) : 0);
    quint8 g = static_cast<quint8>(arr.size() > 1 ? arr.at(1) : 0);
    quint8 b = static_cast<quint8>(arr.size() > 2 ? arr.at(2) : 0);
    quint8 a = static_cast<quint8>(arr.size() > 3 ? arr.at(3) : 255);

    return QColor(r, g, b, a);
}
//=======================================================================================================
QColor Graph::colorFromArray(const QVector<quint8> &arr)
{
    quint8 r = arr.size() > 0 ? arr.at(0) : 0;
    quint8 g = arr.size() > 1 ? arr.at(1) : 0;
    quint8 b = arr.size() > 2 ? arr.at(2) : 0;
    quint8 a = arr.size() > 3 ? arr.at(3) : 255;

    return QColor(r, g, b, a);
}
//=======================================================================================================
} // namespace nayk

