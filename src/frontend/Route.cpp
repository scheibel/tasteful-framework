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

#include <internal/Route>
#include <QTextStream>

using namespace internal;

RequestedAction::RequestedAction() {
}

RequestedAction::RequestedAction(HttpMethod method, QString path) : method(method), path(path) {
}

HttpMethod RequestedAction::getMethod() const {
	return method;
}

QString RequestedAction::getPath() const {
	return path;
}


Route::Route(HttpMethod method, QString urlPattern) : method(method), urlPattern(urlPattern), action(nullptr)
{
}

HttpMethod Route::getMethod() const
{
	return method;
}

QString Route::getUrlPattern() const
{
	return urlPattern;
}

Action* Route::getAction() const
{
	return action.data();
}

void Route::setAction(QSharedPointer<Action> action)
{
	this->action = action;
}

bool Route::isStatic()
{
	return false;
}

bool Route::isDynamic()
{
	return false;
}

bool Route::isWildcard()
{
	return false;
}

QString Route::urlParameters(QVariantMap parameters) {
	QString urlParams;
	QTextStream stream(&urlParams);
	for (QString& key: parameters.keys()) {
		stream << (stream.pos()==0?"?":"&");
		stream << key << "=" << parameters[key].toString();
	}
	return urlParams;
}

Route* Route::create(HttpMethod method, QString urlPattern) {
	if (!urlPattern.startsWith("/")) urlPattern="/"+urlPattern;
	if (urlPattern.contains("/:")) {
		return new DynamicRoute(method, urlPattern);
	} else if (urlPattern.contains("*") || urlPattern.contains("?")) {
		return new WildcardRoute(method, urlPattern);
	}
	return new StaticRoute(method, urlPattern);
}

StaticRoute::StaticRoute(HttpMethod method, QString urlPattern) : Route(method, urlPattern) {
}

bool StaticRoute::match(const RequestedAction& requestedAction)
{
	return method==requestedAction.getMethod() && urlPattern==requestedAction.getPath();
}

bool StaticRoute::isStatic()
{
	return true;
}

QString StaticRoute::urlFor(QVariantMap parameters)
{
	return urlPattern+urlParameters(parameters);
}

DynamicRoute::DynamicRoute(HttpMethod method, QString urlPattern) : Route(method, urlPattern)
{
	QStringList parts = urlPattern.split("/");
	for (QString& part: parts) {
		urlParts << UrlPart(part);
	}
}

DynamicRoute::UrlPart::UrlPart(QString part) {
	if (part.startsWith(":")) {
		variable = true;
		this->part = part.mid(1);
	} else {
		this->part = part;
	}
}

bool DynamicRoute::UrlPart::isVariable() {
	return variable;
}

QString DynamicRoute::UrlPart::getName() {
	return part;
}

bool DynamicRoute::UrlPart::match(QString otherPart) {
	return variable ? true : part == otherPart;
}

QHash<QString, QString> DynamicRoute::getMatchedParts(QString path) {
	QHash<QString, QString> matchedUrlParts;

	QStringList parts = path.split("/");
	if (urlParts.size()!=parts.size()) return QHash<QString, QString>();
	
	for (int i=0; i<parts.size(); ++i) {
		if (!urlParts[i].match(parts[i])) return QHash<QString, QString>();
		if (urlParts[i].isVariable()) matchedUrlParts.insert(urlParts[i].getName(), parts[i]);
	}
	return matchedUrlParts;
}

bool DynamicRoute::match(const RequestedAction& requestedAction)
{
	if (method!=requestedAction.getMethod()) return false;
	
	QStringList parts = requestedAction.getPath().split("/");
	if (urlParts.size()!=parts.size()) return false;
	
	for (int i=0; i<parts.size(); ++i) {
		if (!urlParts[i].match(parts[i])) return false;
	}
	return true;
}

bool DynamicRoute::isDynamic()
{
	return true;
}

QString DynamicRoute::urlFor(QVariantMap parameters)
{
	QStringList list;
	for (UrlPart urlPart: urlParts) {
		if (urlPart.isVariable()) {
			if (!parameters.contains(urlPart.getName())) return "";
			list << parameters.take(urlPart.getName()).toString();
		} else {
			list << urlPart.getName();
		}
	}
	return list.join("/")+urlParameters(parameters);
}

WildcardRoute::WildcardRoute(HttpMethod method, QString urlPattern) : Route(method, urlPattern) {
	regexp.setPatternSyntax(QRegExp::Wildcard);
	regexp.setPattern(urlPattern);
}

bool WildcardRoute::isWildcard()
{
	return true;
}

bool WildcardRoute::match(const RequestedAction& requestedAction) {
	return requestedAction.getMethod()==method && regexp.exactMatch(requestedAction.getPath());
}

QString WildcardRoute::urlFor(QVariantMap parameters) {
	return "";
}
