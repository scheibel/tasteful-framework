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

#include <tasteful-framework/Controller.h>

#include <tasteful-framework/RedirectException.h>
#include <tasteful-framework/LayoutedTemplateView.h>
#include <tasteful-framework/TemplatedLayout.h>

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
    m_parameters = request.getParameters();
    m_cookies = request.getCookies();
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
    return m_response;
}

void Controller::render(const View & view)
{
    view.renderOn(m_response);
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
    return m_parameters;
}

tastefulserver::RequestParameters &Controller::getParameters()
{
    return m_parameters;
}

const tastefulserver::Cookies &Controller::getCookies() const
{
    return m_cookies;
}

tastefulserver::Cookies &Controller::getCookies()
{
    return m_cookies;
}

} // namespace tastefulframework
