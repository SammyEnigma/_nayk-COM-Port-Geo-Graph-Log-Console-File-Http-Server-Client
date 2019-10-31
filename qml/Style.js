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
.pragma library

// theme variant:
var darkTheme              = true
// normal font settings:
var fontPointSize          = 13
var smallFontPointSize     = Math.max(8, fontPointSize - 4)
var bigFontPointSize       = fontPointSize + 4
// default controls settings:
var buttonWidth            = 140
var buttonHeight           = 48
var buttonIconSize         = 32
var disabledControlOpacity = 0.3
// color settings:
var accent                 = darkTheme ? "#0084ad" : "#0084ad"
var primary                = darkTheme ? "#072e3a" : "#8aa5ad"
var foreground             = darkTheme ? "#bbd1d6" : "#02222c"
var background             = darkTheme ? "#02222c" : "#b6bfc2"
var bgColor                = background
var bgDarkColor            = darkTheme ? "#02161c" : "#d7dddf"
var bgLightColor           = primary
var bgAlternateColor       = darkTheme ? "#092e3a" : "#adbabe"
var textColor              = foreground
var textDarkColor          = darkTheme ? "#647174" : "black"
var textLightColor         = darkTheme ? "white"   : "white"
var highlightColor         = darkTheme ? "#89e3ff" : "#89e3ff"
var borderColor            = darkTheme ? "#95c5d0" : "#244f58"
var menuHighlightColor     = darkTheme ? "#005671" : "#005671"
var shadowColor            = "black"
