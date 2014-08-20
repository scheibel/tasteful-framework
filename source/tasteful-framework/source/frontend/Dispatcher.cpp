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

#include <tasteful-framework/Dispatcher.h>

#include <tasteful-framework/RedirectException.h>
#include <tasteful-framework/Logger.h>

namespace tastefulframework {

Dispatcher::Dispatcher()
{
    initializeRoutes();
    connect(&RouteRegistry::instance(), SIGNAL(routeAdded(Route *)), this, SLOT(addRoute(Route *)));
}

void Dispatcher::addRoute(Route * route)
{
    if (route->isStatic())
    {
        m_staticRoutes.insert(RouteRegistry::keyFor(route), route);
    }
    else if (route->isDynamic())
    {
        m_dynamicRoutes << route;
    }
    else if (route->isWildcard())
    {
        m_wildcardRoutes << route;
    }
}

void Dispatcher::initializeRoutes()
{
    for (Route * route : RouteRegistry::routes())
    {
        addRoute(route);
    }
}

Response Dispatcher::dispatch(Request & request) const
{
    Route * route = findMatch(RequestedAction(request.getMethod(), request.getPath()));

    if (!route)
    {
        return defaultDispatch(request);
    }

    return performActionFor(route, request);
}

Response Dispatcher::defaultDispatch(Request & request) const
{
    if (request.getMethod()==tastefulserver::HttpMethod::HEAD)
    {
        Route * route = findMatch(RequestedAction(tastefulserver::HttpMethod::GET, request.getPath()));
        if (route)
        {
            Response response = performActionFor(route, request);
            response.clearContent();

            return response;
        }
    }

    return Response::notFound();
}

Route * Dispatcher::findMatch(const RequestedAction & requestedAction) const
{
    Route * route = findStaticMatch(requestedAction);

    if (!route)
    {
        route = findDynamicMatch(requestedAction);
    }
    if (!route)
    {
        route = findWildcardMatch(requestedAction);
    }

    logger() << requestedAction.getMethod().toString() << " " << requestedAction.getPath() << " -> " << (route ? route->getUrlPattern() : "no match");

    return route;
}

Route * Dispatcher::findStaticMatch(const RequestedAction & requestedAction) const
{
    return m_staticRoutes.value(RouteRegistry::keyFor(requestedAction), nullptr);
}

Route * Dispatcher::findDynamicMatch(const RequestedAction & requestedAction) const
{
    for (Route * route : m_dynamicRoutes)
    {
        if (route->match(requestedAction))
        {
            return route;
        }
    }

    return nullptr;
}

Route * Dispatcher::findWildcardMatch(const RequestedAction & requestedAction) const
{
    for (Route * route : m_wildcardRoutes)
    {
        if (route->match(requestedAction))
        {
            return route;
        }
    }

    return nullptr;
}

Response Dispatcher::performActionFor(Route * route, Request & request) const
{
    if (!route)
    {
        return Response::notFound();
    }
    Action * action = route->getAction();
    if (!action)
    {
        return Response::notFound();
    }

    if (route->isDynamic())
    {
        request.setUrlParameters(((DynamicRoute *)route)->getMatchedParts(request.getPath()));
    }

    try
    {
        return (*action)(request);
    }
    catch (RedirectException e)
    {
        return e.toResponse();
    }
}

} // namespace tastefulframework
