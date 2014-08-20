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

#include <tasteful-framework/FrameworkEntryPoint.h>

#include <tasteful-server/HttpRequest.h>
#include <tasteful-server/HttpResponse.h>

#include <tasteful-framework/FrontController.h>

namespace tastefulframework {

FrameworkEntryPoint::FrameworkEntryPoint(FrontController * frontController)
    : m_frontController(frontController)
{
}

tastefulserver::HttpResponse FrameworkEntryPoint::operator()(const tastefulserver::HttpRequest & httpRequest)
{
    return m_frontController->handleRequest(httpRequest);
}

} // namespace tastefulframework
