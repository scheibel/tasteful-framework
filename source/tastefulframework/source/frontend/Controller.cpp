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

#include <tastefulframework/Controller.h>
#include <tastefulframework/RedirectException.h>
#include <tastefulframework/LayoutedTemplateView.h>
#include <tastefulframework/TemplatedLayout.h>

namespace tastefulframework {

Controller::Controller()
{

}

Controller::~Controller()
{

}

void Controller::initialize(Request & request)
{
    setSession(request.getSession());
    parameters = request.getParameters();
    cookies = request.getCookies();
}

bool Controller::beforeAction()
{
    return true;
}

void Controller::afterAction()
{
}

const Response &Controller::getResponse() const
{
    return response;
}

void Controller::render(const View & view)
{
    view.renderOn(response);
}

void Controller::renderWithLayout(const QString & /*templateFile*/, const QString & /*layoutFile*/)
{
    // render(LayoutedTemplateView(templateFile, TemplatedLayout(layoutFile));
}

void Controller::redirect(const QString & url)
{
    throw RedirectException(url);
}

const tastefulserver::RequestParameters &Controller::getParameters() const
{
    return parameters;
}

tastefulserver::RequestParameters &Controller::getParameters()
{
    return parameters;
}

const tastefulserver::Cookies &Controller::getCookies() const
{
    return cookies;
}

tastefulserver::Cookies &Controller::getCookies()
{
    return cookies;
}

} // namespace tastefulframework
