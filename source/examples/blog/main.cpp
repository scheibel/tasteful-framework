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

#include <tastefulframework/startup.h>

#include <controllers/HomeController.h>
#include <controllers/LoginController.h>
#include <controllers/RegisterController.h>
#include <controllers/BlogPostController.h>
#include <controllers/AllBlogPostController.h>
#include <controllers/SearchController.h>
#include <session/Session.h>

int main(int argc, char * argv[])
{
    WebApplication blog(argc, argv);
    QStringList args = blog.arguments();

    blog.setUpFromConfig(args.size()>=2 ? args[1] : "");
    blog.setSessionClass<Session>();

    ROOT = &HomeController::index;

    GET("login") = &LoginController::index;
    POST("login") = &LoginController::login;
    GET("logout") = &LoginController::logout;

    GET("register") = &RegisterController::index;
    POST("register") = &RegisterController::signup;

    registerCrudActions<BlogPostController>("myblogposts");

    GET("blogposts") = &AllBlogPostController::index;
    GET("blogposts/:id") = &AllBlogPostController::show;

    GET("search") = &SearchController::index;
    GET("find/:string") = &SearchController::find;
    POST("find") = &SearchController::findPost;

    return blog.run();
}
