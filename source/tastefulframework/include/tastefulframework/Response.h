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

#pragma once

#include <QStringList>
#include <QHash>
#include <QString>
#include <QFile>
#include <tastefulserver/HttpResponse.h>
#include <tastefulframework/AbstractSession.h>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API Response : public tastefulserver::HttpResponse
{
public:
    Response(unsigned statusCode = tastefulserver::http::OK);

    HttpResponse &asHttpResponse() const;

    void setMimeType(const QString & mimeType);
    void setMimeTypeForFileName(const QString & filename);

    void setSession(AbstractSession * session);

    void setContentFromFile(const QString & filename);

    Response&asDownload(const QString & name);
    static Response notFound();
    static Response redirect(const QString & url);
    static Response redirectPermanently(const QString & url);
    static Response forContent(const QString & content, unsigned statusCode = tastefulserver::http::OK);
    static Response forContent(const QByteArray & content, unsigned statusCode = tastefulserver::http::OK);
    static Response forFile(const QFile & file);
    static Response download(const QFile & file, const QString & name = QString());
    static Response download(const QByteArray & content, const QString & name);
    static Response accessDenied();
};

} // namespace tastefulframework
