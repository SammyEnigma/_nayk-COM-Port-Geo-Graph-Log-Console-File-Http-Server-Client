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
#include <QtMath>

#include "geo.h"

namespace nayk {
//=======================================================================================================
QPointF Geo::coordGeoToMap(double latitude, double longitude, double map_width, double cx, double cy)
{
    double aa = map_width / earth_equator; // кол-во пикселей в метре
    double lat = qDegreesToRadians( latitude );
    double lon = qDegreesToRadians( longitude );
    double x = earth_a * lon;
    double y = earth_a * qLn( qTan( M_PI_4 + lat/2.0) *
                        qPow((1 - earth_e * qSin(lat))/(1 + earth_e * qSin(lat)), earth_e/2.0) );
    return QPointF( cx + (x + earth_half_equator) * aa, cy + map_width - (y + earth_half_equator) * aa );
}
//=======================================================================================================
QPointF Geo::coordMapToGeo(double x, double y, double map_width, double cx, double cy)
{
    double aa = map_width / earth_equator; // кол-во пикселей в метре
    x = (x - cx)/aa - earth_half_equator;
    y = (map_width + cy - y)/aa - earth_half_equator;
    double ts = qExp( -y / earth_a );
    double phi = M_PI_2 - 2.0 * qAtan(ts);
    int i = 0;
    double dphi = 1.0;
    while ((qAbs(dphi) > 0.000000001) && (i++ < 15)) {
        double con = earth_e * qSin(phi);
        dphi = M_PI_2 - 2.0 * qAtan(ts * qPow((1.0 - con) / (1.0 + con), earth_e)) - phi;
        phi += dphi;
     }
     return QPointF( qRadiansToDegrees( x / earth_a ),  qRadiansToDegrees(phi)  );
}
//=======================================================================================================
} // namespace nayk

