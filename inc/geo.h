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
#ifndef NAYK_GEO_H
#define NAYK_GEO_H

#include <QtCore>

//=========================================================================================================
namespace nayk {
//=========================================================================================================
const double earth_a            = 6378137.0;           // Большая полуось эллипсоида (Экваториальный радиус)
const double earth_b            = 6356752.3142;        // Малая полуось эллипсоида
const double earth_e            = 0.0818191908426;     // Эксцентриситет
const double earth_equator      = 40075016.685578488;  // Длина экватора в метрах
const double earth_half_equator = earth_equator / 2.0; // половина экватора
//=========================================================================================================
class Geo
{
public:
    static QPointF coordGeoToMap(double latitude, double longitude, double map_width, double cx=0, double cy=0);
    static QPointF coordMapToGeo(double x, double y, double map_width, double cx=0, double cy=0);
    //
    Geo() = delete;
};

//=========================================================================================================
} // namespace nayk

//=========================================================================================================
#endif // NAYK_GEO_H
