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
#ifndef NAYK_HTTP_H
#define NAYK_HTTP_H

#include <QString>

namespace nayk {
//======================================================================================================
const QString ContentTypeImageGIF             = "image/gif";
const QString ContentTypeImageJPEG            = "image/jpeg";
const QString ContentTypeImageJPG             = "image/jpg";
const QString ContentTypeImagePNG             = "image/png";
const QString ContentTypeImageSVG             = "image/svg+xml";
const QString ContentTypeImageTIFF            = "image/tiff";
const QString ContentTypeFont                 = "application/font";
const QString ContentTypeFontEOT              = "application/vnd.ms-fontobject";
const QString ContentTypeFontOTF              = "font/opentype";
const QString ContentTypeFontTTF              = "font/ttf";
const QString ContentTypeFontWOFF             = "font/woff";
const QString ContentTypeScriptECMAS          = "text/ecmascript";
const QString ContentTypeScriptVB             = "text/vbscript";
const QString ContentTypeCSS                  = "text/css";
const QString ContentTypeHTML                 = "text/html";
const QString ContentTypeJS                   = "text/javascript";
const QString ContentTypeJSON                 = "application/json";
const QString ContentTypeText                 = "text/plain";
const QString ContentTypeXML                  = "text/xml";
const QString ContentTypeWWWForm              = "application/x-www-form-urlencoded";
const QString ContentTypeMultipartForm        = "multipart/form-data";
const QString ContentTypeBinary               = "application/octet-stream";
// Server headers:
const QString ServerHeaderComSpec             = "COMSPEC";
const QString ServerHeaderDocumentRoot        = "DOCUMENT_ROOT";
const QString ServerHeaderGatewayInterface    = "GATEWAY_INTERFACE";
const QString ServerHeaderHttpAccept          = "HTTP_ACCEPT";
const QString ServerHeaderHttpAcceptEncoding  = "HTTP_ACCEPT_ENCODING";
const QString ServerHeaderHttpAcceptLanguage  = "HTTP_ACCEPT_LANGUAGE";
const QString ServerHeaderHttpConnection      = "HTTP_CONNECTION";
const QString ServerHeaderHttpCookie          = "HTTP_COOKIE";
const QString ServerHeaderHttpHost            = "HTTP_HOST";
const QString ServerHeaderHttpUserAgent       = "HTTP_USER_AGENT";
const QString ServerHeaderHttps               = "HTTPS";
const QString ServerHeaderPath                = "PATH";
const QString ServerHeaderQueryString         = "QUERY_STRING";
const QString ServerHeaderRemoteAddress       = "REMOTE_ADDR";
const QString ServerHeaderRemotePort          = "REMOTE_PORT";
const QString ServerHeaderRequestMethod       = "REQUEST_METHOD";
const QString ServerHeaderRequestScheme       = "REQUEST_SCHEME";
const QString ServerHeaderRequestUri          = "REQUEST_URI";
const QString ServerHeaderScriptFilename      = "SCRIPT_FILENAME";
const QString ServerHeaderScriptName          = "SCRIPT_NAME";
const QString ServerHeaderServerAddress       = "SERVER_ADDR";
const QString ServerHeaderServerAdministrator = "SERVER_ADMIN";
const QString ServerHeaderServerName          = "SERVER_NAME";
const QString ServerHeaderServerPort          = "SERVER_PORT";
const QString ServerHeaderServerProtocol      = "SERVER_PROTOCOL";
const QString ServerHeaderServerSignature     = "SERVER_SIGNATURE";
const QString ServerHeaderServerSoftware      = "SERVER_SOFTWARE";
const QString ServerHeaderContentType         = "CONTENT_TYPE";
const QString ServerHeaderContentLength       = "CONTENT_LENGTH";
const QString ServerHeaderContextPrefix       = "CONTEXT_PREFIX";
//
const QString MethodDelete                    = "DELETE";
const QString MethodGet                       = "GET";
const QString MethodHead                      = "HEAD";
const QString MethodPost                      = "POST";
const QString MethodPut                       = "PUT";
// Response headers:
const QString HeaderContentLength             = "Content-Length";
const QString HeaderContentType               = "Content-Type";
const QString HeaderCookie                    = "Set-Cookie";

//======================================================================================================
} // namespace nayk
#endif // NAYK_HTTP_H
