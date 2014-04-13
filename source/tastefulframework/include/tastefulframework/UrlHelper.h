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
#include <QVariant>
#include <tastefulframework/RouteRegistry.h>
#include <initializer_list>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API UrlHelper
{
public:
    typedef std::initializer_list<std::pair<QString, QVariant >> InitializerList;

    template <typename T>
    QString url(void (T::* methodPointer)(), QVariantMap parameters) const
    {
        Route * route = RouteRegistry::routeFor(methodPointer);

        if (!route)
        {
            return "";
        }

        return route->urlFor(parameters);
    }

    template <typename T>
    QString url(void (T::* methodPointer)(), InitializerList parameters) const
    {
        return url(methodPointer, toQVariantMap(parameters));
    }

    template <typename T>
    QString url(void (T::* methodPointer)()) const
    {
        return url(methodPointer, QVariantMap());
    }

    QString url(const char * urlPattern, QVariantMap parameters) const
    {
        return url(QString(urlPattern), parameters);
    }

    QString url(QString urlPattern, QVariantMap parameters) const
    {
        DynamicRoute route(tastefulserver::HttpMethod::GET, urlPattern);

        return route.urlFor(parameters);
    }

    QString url(const char * urlPattern, InitializerList parameters) const
    {
        return url(QString(urlPattern), parameters);
    }

    QString url(QString urlPattern, InitializerList parameters) const
    {
        return url(urlPattern, toQVariantMap(parameters));
    }

private:
    QVariantMap toQVariantMap(InitializerList parameters) const
    {
        QVariantMap map;

        for (std::pair<QString, QVariant> pair : parameters)
        {
            map.insert(pair.first, pair.second);
        }

        return map;
    }

};

} // namespace tastefulframework
