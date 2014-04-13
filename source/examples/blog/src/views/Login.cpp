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

#include <views/Login.h>

#include <controllers/LoginController.h>

Login::Login(Session * session, const QString & email, bool loginAttempt)
    : BlogView(session)
    , _loginAttempt(loginAttempt)
    , _email(email)
{
    setFilename("login.html");

    addTransform("loginform", [this](DomNode & node) {
            node("method") = "POST";
            node("url") = url(&LoginController::login);
        });

    addTransform("errormessage", [this](DomNode & node) {
            if (_loginAttempt)
            {
                node << "Failed to log in.";
            }
        });

    addTransform("emailvalue", [this](DomNode & node) {
            node("value") = _email;
        });
}
