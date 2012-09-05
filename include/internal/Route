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

#pragma once

#include <internal/Action>
#include <internal/util.h>
#include <http>
#include <QString>
#include <QPair>
#include <QHash>
#include <QList>
#include <QRegExp>
#include <QVariantMap>
#include <string>
#include <QSharedPointer>

namespace internal {
	class RequestedAction {
		public:
			RequestedAction();
			RequestedAction(const HttpMethod& method, const QString& path);
		
			HttpMethod getMethod() const;
			QString getPath() const;
		private:
			HttpMethod method;
			QString path;
	};
	
	class Route {
		public:
			Route(const HttpMethod& method, const QString& urlPattern);
		
			static Route* create(const HttpMethod& method, const QString& urlPattern);
		
			HttpMethod getMethod() const;
			QString getUrlPattern() const;
			Action* getAction() const;
			void setAction(QSharedPointer<Action> action);
		
			virtual bool match(const RequestedAction& requestedAction) const = 0;
			virtual QString urlFor(const QVariantMap& parameters) const = 0;
		
			virtual bool isStatic() const;
			virtual bool isDynamic() const;
			virtual bool isWildcard() const;
		protected:
			QString urlParameters(const QVariantMap& parameters) const;
		
			HttpMethod method;
			QString urlPattern;
			QSharedPointer<Action> action;
	};

	class StaticRoute : public Route {
		public:
			StaticRoute(const HttpMethod& method, const QString& urlPattern);
		
			virtual bool isStatic() const;
			virtual bool match(const RequestedAction& requestedAction) const;
			virtual QString urlFor(const QVariantMap& parameters) const;
	};

	class DynamicRoute : public Route {
		public:
			DynamicRoute(const HttpMethod& method, const QString& urlPattern);
		
			virtual bool isDynamic() const;
			virtual bool match(const RequestedAction& requestedAction) const;
			virtual QString urlFor(const QVariantMap& parameters) const;

			QHash<QString, QString> getMatchedParts(const QString& path) const;
		private:
			class UrlPart {
				public:
					UrlPart(const QString& part);
				
					QString getName() const;
					bool isVariable() const;
					bool match(const QString& otherPart) const;
				private:
					QString part;
					bool variable;
			};
			QList<UrlPart> urlParts;
	};

	class WildcardRoute : public Route {
		public:
			WildcardRoute(const HttpMethod& method, const QString& urlPattern);
		
			virtual bool isWildcard() const;
			virtual bool match(const RequestedAction& requestedAction) const;
			virtual QString urlFor(const QVariantMap& parameters) const;
		private:
			QRegExp regexp;
	};
}