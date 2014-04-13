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

#include <views/Layout.h>

#include <controllers/LoginController.h>
#include <controllers/RegisterController.h>
#include <controllers/BlogPostController.h>
#include <controllers/AllBlogPostController.h>
#include <controllers/SearchController.h>

Layout::Layout()
    : _session(nullptr)
{
    setFilename("layout.html");

    addTransform("stylesheets", [this](tastefulframework::DomNode & node) {
            node << link(type("text/css"), href("/stylesheets/blog.css"), rel("stylesheet"));
        });

    addTransform("login", &Layout::login);
    addTransform("menu", &Layout::menu);
}

void Layout::setSession(Session * newSession)
{
    _session = newSession;
}

void Layout::menu(tastefulframework::DomNode & node) const
{
    if (_session && _session->isValid() && _session->isLoggedIn())
    {
        node << a(href(url(&BlogPostController::index)), "My blogposts") << " | ";
    }

    node << a(href(url(&AllBlogPostController::index)), "List blogposts") << " | ";
    node << a(href(url(&SearchController::index)), "Search blogposts");
}

void Layout::login(tastefulframework::DomNode & node) const
{
    if (_session && _session->isValid())
    {
        if (_session->isLoggedIn())
        {
            node << a(href(url(&LoginController::logout)), "Log out") << (" | Logged in as " + _session->author()->email());
        }
        else
        {
            node << a(href(url(&LoginController::index)), "Log in") << " | " << a(href(url(&RegisterController::index)), "Sign up");
        }
    }
    else
    {
        node << "Cannot log in because Cookies are not allowed";
    }
}
