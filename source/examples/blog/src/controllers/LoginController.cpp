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

#include <controllers/LoginController.h>

#include <controllers/HomeController.h>
#include <views/Login.h>
#include <models/Author.h>

#include <tastefulserver/QVariantTree.h>

void LoginController::index()
{
    render(Login(getSession()));
}

void LoginController::login()
{
    QString email = parameters["email"].value<QString>();
    QString password = parameters["password"].value<QString>();
    Author * author = Author::getBy("email = '" + email + "'");

    if (author)
    {
        if (author->validatePassword(password))
        {
            getSession()->setAuthor(author);

            redirect(url(&HomeController::index));
        }
    }

    render(Login(getSession(), email, true));
}

void LoginController::logout()
{
    getSession()->setAuthor(nullptr);

    redirect(url(&HomeController::index));
}
