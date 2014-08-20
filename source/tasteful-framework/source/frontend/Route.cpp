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

#include <tasteful-framework/Route.h>

#include <QTextStream>

namespace tastefulframework {

RequestedAction::RequestedAction()
{
}

RequestedAction::RequestedAction(const tastefulserver::HttpMethod & method, const QString & path)
    : m_method(method)
    , m_path(path)
{
}

tastefulserver::HttpMethod RequestedAction::getMethod() const
{
    return m_method;
}

QString RequestedAction::getPath() const
{
    return m_path;
}

Route::Route(const tastefulserver::HttpMethod & method, const QString & urlPattern)
    : m_method(method)
    , m_urlPattern(urlPattern)
    , m_action(nullptr)
{
}

tastefulserver::HttpMethod Route::getMethod() const
{
    return m_method;
}

QString Route::getUrlPattern() const
{
    return m_urlPattern;
}

Action * Route::getAction() const
{
    return m_action.data();
}

void Route::setAction(QSharedPointer<Action> action)
{
    this->m_action = action;
}

bool Route::isStatic() const
{
    return false;
}

bool Route::isDynamic() const
{
    return false;
}

bool Route::isWildcard() const
{
    return false;
}

QString Route::urlParameters(const QVariantMap & parameters) const
{
    QString urlParams;
    QTextStream stream(&urlParams);

    for (QString & key : parameters.keys())
    {
        stream << (stream.pos()==0 ? "?" : "&");
        stream << key << "=" << parameters[key].toString();
    }

    return urlParams;
}

Route * Route::create(const tastefulserver::HttpMethod & method, const QString & urlPattern)
{
    QString correctUrlPattern = urlPattern;

    if (!correctUrlPattern.startsWith("/"))
    {
        correctUrlPattern = "/" + urlPattern;
    }
    if (correctUrlPattern.contains("/:"))
    {
        return new DynamicRoute(method, correctUrlPattern);
    }
    else if (urlPattern.contains("*") || urlPattern.contains("?"))
    {
        return new WildcardRoute(method, correctUrlPattern);
    }

    return new StaticRoute(method, correctUrlPattern);
}

StaticRoute::StaticRoute(const tastefulserver::HttpMethod & method, const QString & urlPattern)
    : Route(method, urlPattern)
{
}

bool StaticRoute::match(const RequestedAction & requestedAction) const
{
    return m_method==requestedAction.getMethod() && m_urlPattern==requestedAction.getPath();
}

bool StaticRoute::isStatic() const
{
    return true;
}

QString StaticRoute::urlFor(const QVariantMap & parameters) const
{
    return m_urlPattern + urlParameters(parameters);
}

DynamicRoute::DynamicRoute(const tastefulserver::HttpMethod & method, const QString & urlPattern)
    : Route(method, urlPattern)
{
    QStringList parts = urlPattern.split("/");

    for (QString & part : parts)
    {
        m_urlParts << UrlPart(part);
    }
}

DynamicRoute::UrlPart::UrlPart(const QString & part)
{
    if (part.startsWith(":"))
    {
        m_variable = true;
        this->m_part = part.mid(1);
    }
    else
    {
        m_variable = false;
        this->m_part = part;
    }
}

bool DynamicRoute::UrlPart::isVariable() const
{
    return m_variable;
}

QString DynamicRoute::UrlPart::getName() const
{
    return m_part;
}

bool DynamicRoute::UrlPart::match(const QString & otherPart) const
{
    return m_variable ? true : m_part == otherPart;
}

QHash<QString, QString> DynamicRoute::getMatchedParts(const QString & path) const
{
    QHash<QString, QString> matchedUrlParts;

    QStringList parts = path.split("/");
    if (m_urlParts.size()!=parts.size())
    {
        return QHash<QString, QString>();
    }

    for (int i = 0;i<parts.size();++i)
    {
        if (!m_urlParts[i].match(parts[i]))
        {
            return QHash<QString, QString>();
        }
        if (m_urlParts[i].isVariable())
        {
            matchedUrlParts.insert(m_urlParts[i].getName(), parts[i]);
        }
    }

    return matchedUrlParts;
}

bool DynamicRoute::match(const RequestedAction & requestedAction) const
{
    if (m_method!=requestedAction.getMethod())
    {
        return false;
    }

    QStringList parts = requestedAction.getPath().split("/");
    if (m_urlParts.size()!=parts.size())
    {
        return false;
    }

    for (int i = 0;i<parts.size();++i)
    {
        if (!m_urlParts[i].match(parts[i]))
        {
            return false;
        }
    }

    return true;
}

bool DynamicRoute::isDynamic() const
{
    return true;
}

QString DynamicRoute::urlFor(const QVariantMap & parameters) const
{
    QStringList list;
    QVariantMap params = parameters;

    for (const UrlPart & urlPart : m_urlParts)
    {
        if (urlPart.isVariable())
        {
            if (!params.contains(urlPart.getName()))
            {
                return "";
            }

            list << params.take(urlPart.getName()).toString();
        }
        else
        {
            list << urlPart.getName();
        }
    }

    return list.join("/") + urlParameters(params);
}

WildcardRoute::WildcardRoute(const tastefulserver::HttpMethod & method, const QString & urlPattern)
    : Route(method, urlPattern)
{
    m_regexp.setPatternSyntax(QRegExp::Wildcard);
    m_regexp.setPattern(urlPattern);
}

bool WildcardRoute::isWildcard() const
{
    return true;
}

bool WildcardRoute::match(const RequestedAction & requestedAction) const
{
    return requestedAction.getMethod()==m_method && m_regexp.exactMatch(requestedAction.getPath());
}

QString WildcardRoute::urlFor(const QVariantMap & /*parameters*/) const
{
    return "";
}

} // namespace tastefulframework
