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

#include <controllers/RegisterController.h>

#include <controllers/HomeController.h>
#include <views/Registration.h>
#include <models/Author.h>
#include <tastefulserver/QVariantTree.h>

void RegisterController::index()
{
    render(Registration(getSession()));
}

void RegisterController::signup()
{
    QString email = parameters["email"].value<QString>();
    QString password = parameters["password"].value<QString>();
    QString password2 = parameters["password2"].value<QString>();

    if (Author::getBy("email = '" + email + "'"))
    {
        render(Registration(getSession(), email, "An account with this email already exists"));
    }
    else
    {
        if (password != password2)
        {
            render(Registration(getSession(), email, "The password confirmation doesn't match with the password"));
        }
        else
        {
            Author * author = new Author();

            author->email(email);
            author->setNewSalt(email);
            author->setNewPassword(password);

            author->save();

            getSession()->setAuthor(author);

            redirect(url(&HomeController::index));
        }
    }
}
