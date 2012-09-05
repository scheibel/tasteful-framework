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

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QVariantMap>
#include <internal/SqlBuilder>
#include <WebAppConfig>
#include <QReadWriteLock>

namespace internal {
	class Database {
		public:
			static Database& get();
			static Database& get(const QString& id);
			
			static void add(const DatabaseConfig& config);
			
			QSqlQuery build(const QString& sql) const;
			QSqlQuery build(const QString& sql, const QVariantMap& bindings) const;
			QSqlQuery build(const SqlBuilder& sqlBuilder) const;
			QSqlQuery build(const SqlBuilder& sqlBuilder, const QVariantMap& bindings) const;
		private:
			Database(const QSqlDatabase& database);
			
			static Database& getByIdAndThreadId(const QString& id, const QString& threadId);
			
			QSqlDatabase database;
			
			static QHash<QString, Database*> databases;
			static QReadWriteLock lock;
	};
}