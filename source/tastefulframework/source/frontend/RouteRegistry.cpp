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

#include <tastefulframework/RouteRegistry.h>

namespace tastefulframework {

RouteRegistry::RouteRegistry()
{
}

RouteRegistry RouteRegistry::s_instance = RouteRegistry();
void RouteRegistry::addMethodStringToRoutes(const QString & methodPointerString, Route * route)
{
    m_methodsToRoutes.insert(methodPointerString, route);
}

Route * RouteRegistry::getRouteForMethodString(const QString & methodPointerString) const
{
    return m_methodsToRoutes.value(methodPointerString, nullptr);
}

RouteRegistry &RouteRegistry::instance()
{
    return s_instance;
}

QList<Route *> RouteRegistry::routes()
{
    return instance().getRoutes();
}

QList<Route *> RouteRegistry::getRoutes() const
{
    return m_routes.values();
}

RouteRegistry::Key RouteRegistry::keyFor(Route * route)
{
    return Key(route->getMethod(), route->getUrlPattern());
}

RouteRegistry::Key RouteRegistry::keyFor(const Request & request)
{
    return Key(request.getMethod(), request.getPath());
}

RouteRegistry::Key RouteRegistry::keyFor(const RequestedAction & requestedAction)
{
    return Key(requestedAction.getMethod(), requestedAction.getPath());
}

RouteRegistry::Key RouteRegistry::keyFor(const tastefulserver::HttpMethod & method, const QString & urlPattern)
{
    QString correctedPattern = urlPattern.startsWith("/") ? urlPattern : "/" + urlPattern;

    return Key(method, correctedPattern);
}

Route * RouteRegistry::obtain(const tastefulserver::HttpMethod & method, const QString & urlPattern)
{
    Key key = keyFor(method, urlPattern);

    if (!m_routes.contains(key))
    {
        Route * route = Route::create(method, urlPattern);
        m_routes.insert(key, route);
        emit(routeAdded(route));
    }

    return m_routes[key];
}

Route * RouteRegistry::getOrCreate(const tastefulserver::HttpMethod & method, const QString & urlPattern)
{
    return instance().obtain(method, urlPattern);
}

} // namespace tastefulframework
