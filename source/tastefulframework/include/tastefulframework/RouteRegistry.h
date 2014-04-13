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

#include <tastefulframework/Route.h>
#include <QObject>
#include <QHash>
#include <tastefulframework/Request.h>
#include <tastefulframework/QHashExtension.h>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API RouteRegistry : public QObject
{
    Q_OBJECT

private:
    RouteRegistry();
    RouteRegistry(const RouteRegistry & registry);    // do not implement
    RouteRegistry &operator=(const RouteRegistry & registry);    // do not implement
    static RouteRegistry _instance;

    void addMethodStringToRoutes(const QString & methodPointerString, Route * route);
    Route* getRouteForMethodString(const QString & methodPointerString) const;

signals:
    void routeAdded(Route * route);

public:
    typedef QPair<tastefulserver::HttpMethod::Method, QString> Key;

    static RouteRegistry&instance();

    QList<Route *> getRoutes() const;
    static QList<Route *> routes();
    Route* obtain(const tastefulserver::HttpMethod & method, const QString & urlPattern);
    static Route* getOrCreate(const tastefulserver::HttpMethod & method, const QString & urlPattern);
    static Key keyFor(Route * route);
    static Key keyFor(const Request & request);
    static Key keyFor(const RequestedAction & requestedAction);
    static Key keyFor(const tastefulserver::HttpMethod & method, const QString & urlPattern);

    template <typename T>
    static void assignMethodToRoute(void (T::* methodPointer)(), Route * route)
    {
        instance().addMethodStringToRoutes(methodPointerToString(methodPointer), route);
    }

    template <typename T>
    static Route* routeFor(void (T::* methodPointer)())
    {
        return instance().getRouteForMethodString(methodPointerToString(methodPointer));
    }

private:
    QHash<QString, Route *> methodsToRoutes;
    QHash<Key, Route *> _routes;
};

class TASTEFULFRAMEWORK_API RouteActionAssigner
{
public:
    RouteActionAssigner(Route * route)
        : route(route)
    {
    }

    QSharedPointer<Action> operator=(QSharedPointer<Action> action)
    {
        route->setAction(action);

        return action;
    }

    QSharedPointer<Action> operator=(Action * action)
    {
        return *this = QSharedPointer<Action>(action);
    }

    template <typename T>
    QSharedPointer<Action> operator=(void (T::* methodPointer)())
    {
        RouteRegistry::assignMethodToRoute(methodPointer, route);

        return *this = new ControllerAction<T>(methodPointer);
    }

    QSharedPointer<Action> operator=(const QString & string)
    {
        return *this = new StringAction(string);
    }

    QSharedPointer<Action> operator=(const char * string)
    {
        return *this = QString(string);
    }

    QSharedPointer<Action> operator=(const QFile & file)
    {
        return *this = new FileAction(file);
    }

    QSharedPointer<Action> operator=(const Download & download)
    {
        return *this = new DownloadAction(download);
    }

    QSharedPointer<Action> operator=(const Response & response)
    {
        return *this = new ResponseAction(response);
    }

    QSharedPointer<Action> operator=(std::function<Response(Request)> lambda)
    {
        return *this = new LambdaAction(lambda);
    }

private:
    Route * route;
};

} // namespace tastefulframework