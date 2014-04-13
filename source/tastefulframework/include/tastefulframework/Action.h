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

#include <tastefulframework/Response.h>
#include <tastefulframework/Request.h>
#include <tastefulframework/Download.h>
#include <functional>
#include <QString>
#include <QFile>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class Controller;

class TASTEFULFRAMEWORK_API Action
{
public:
    virtual ~Action();
    virtual Response operator()(Request & request) const = 0;
};

template <typename T>
class ControllerAction : public Action
{
public:
    typedef void (T::* MethodPointer)();

    ControllerAction(MethodPointer methodPointer)
        : methodPointer(methodPointer)
    {
    }

    Response operator()(Request & request) const
    {
        T controller;

        controller.initialize(request);
        if (controller.beforeAction())
        {
            (controller.*methodPointer)();
            controller.afterAction();
        }

        return controller.getResponse();
    }

private:
    MethodPointer methodPointer;
};

class TASTEFULFRAMEWORK_API StringAction : public Action
{
public:
    StringAction(const QString & content);

    Response operator()(Request & request) const;

private:
    QString content;
};

class TASTEFULFRAMEWORK_API FileAction : public Action
{
public:
    FileAction(const QFile & file);

    Response operator()(Request & request) const;

private:
    QFile file;
};

class TASTEFULFRAMEWORK_API DownloadAction : public Action
{
public:
    DownloadAction(const Download & download);

    Response operator()(Request & request) const;

private:
    Download download;
};

class TASTEFULFRAMEWORK_API ResponseAction : public Action
{
public:
    ResponseAction(const Response & response);

    Response operator()(Request & request) const;

private:
    Response response;
};

class TASTEFULFRAMEWORK_API LambdaAction : public Action
{
public:
    typedef std::function<Response(Request &)> Lambda;
    LambdaAction(Lambda lambda);

    Response operator()(Request & request) const;

private:
    Lambda lambda;
};

} // namespace tastefulframework
