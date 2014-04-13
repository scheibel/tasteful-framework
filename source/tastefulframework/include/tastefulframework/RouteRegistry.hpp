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

#include <tastefulframework/RouteRegistry.h>

namespace tastefulframework {

template <typename T>
void RouteRegistry::assignMethodToRoute(void (T::* methodPointer)(), Route * route)
{
    instance().addMethodStringToRoutes(methodPointerToString(methodPointer), route);
}

template <typename T>
Route* RouteRegistry::routeFor(void (T::* methodPointer)())
{
    return instance().getRouteForMethodString(methodPointerToString(methodPointer));
}

template <typename T>
QSharedPointer<Action> RouteActionAssigner::operator=(void (T::* methodPointer)())
{
    RouteRegistry::assignMethodToRoute(methodPointer, route);

    return *this = new ControllerAction<T>(methodPointer);
}

} // namespace tastefulframework
