/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012 Lux, Scheibel
 * Authors:
 *     Roland Lux <rollux2000@googlemail.com>
 *     Willy Scheibel <willyscheibel@gmx.de>
 *
 * This file is part of Tasteful Framework.
 *
 * Tasteful Framework is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tasteful Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Tasteful Framework.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <tastefulframework/Response.h>
#include <QFileInfo>
#include <tastefulframework/MimeDatabase.h>

Response::Response(unsigned statusCode)
{
    setStatusCode(statusCode);
    setHeader(tastefulserver::http::Server, "tasteful server");
}

tastefulserver::HttpResponse &Response::asHttpResponse() const
{
    return *(HttpResponse *)this;
}

void Response::setMimeType(const QString & mimeType)
{
    contentType.setTypeAndSubtype(mimeType);
}

void Response::setMimeTypeForFileName(const QString & filename)
{
    setMimeType(MimeDatabase::mimeTypeForFilename(filename));
}

void Response::setSession(AbstractSession * session)
{
    setCookie("sessionId", session->getIdentifier()).setPath("/");
}

void Response::setContentFromFile(const QString & filename)
{
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly))
    {
        setContent(file.readAll());
        file.close();
    }
}

Response &Response::asDownload(const QString & name)
{
    setMimeTypeForFileName(name);
    setHeader(tastefulserver::http::ContentDisposition, "attachment;filename=\"" + name + "\"");

    return *this;
}

Response Response::notFound()
{
    return Response(tastefulserver::http::NotFound);
}

Response Response::redirect(const QString & url)
{
    Response response(tastefulserver::http::Found);

    response.setHeader(tastefulserver::http::Location, url);

    return response;
}

Response Response::redirectPermanently(const QString & url)
{
    Response response(tastefulserver::http::MovedPermanently);

    response.setHeader(tastefulserver::http::Location, url);

    return response;
}

Response Response::forContent(const QString & content, unsigned statusCode)
{
    Response response(statusCode);

    response.setContent(content.toUtf8());

    return response;
}

Response Response::forContent(const QByteArray & content, unsigned statusCode)
{
    Response response(statusCode);

    response.setContent(content);

    return response;
}

Response Response::forFile(const QFile & constFile)
{
    QFile file(constFile.fileName());

    if (!file.open(QIODevice::ReadOnly))
    {
        return Response::notFound();
    }
    QByteArray content = file.readAll().data();
    file.close();

    Response response = Response::forContent(content);
    response.setMimeTypeForFileName(file.fileName());

    return response;
}

Response Response::download(const QFile & file, const QString & name)
{
    return Response::forFile(file).asDownload(name.isNull() ? QFileInfo(file).fileName() : name);
}

Response Response::download(const QByteArray & content, const QString & name)
{
    return Response::forContent(content).asDownload(name);
}

Response Response::accessDenied()
{
    return Response(tastefulserver::http::Forbidden);
}
