/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012-2014 Lux, Scheibel
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

#include <QString>
#include <QHash>

#include <tasteful-server/Cookie.h>

#include <tasteful-framework/tasteful-framework_api.h>

#include <tasteful-framework/View.h>
#include <tasteful-framework/Request.h>
#include <tasteful-framework/Response.h>
#include <tasteful-framework/SessionContainer.h>
#include <tasteful-framework/UrlHelper.h>

namespace tastefulframework {

class TASTEFUL_FRAMEWORK_API Controller : public SessionContainer, public UrlHelper
{
public:
    Controller();
    virtual ~Controller();

    virtual void initialize(Request & request);
    virtual bool beforeAction();
    virtual void afterAction();
    virtual const Response & getResponse() const;
    const tastefulserver::RequestParameters & getParameters() const;
    tastefulserver::RequestParameters & getParameters();
    const tastefulserver::Cookies & getCookies() const;
    tastefulserver::Cookies & getCookies();

protected:
    void render(const View & view);
    void renderWithLayout(const QString & templateFile, const QString & layoutFile);
    void redirect(const QString & url);

    Response m_response;
    tastefulserver::RequestParameters m_parameters;
    tastefulserver::Cookies m_cookies;
};

} // namespace tastefulframework
