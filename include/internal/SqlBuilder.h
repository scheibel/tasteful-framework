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

#include <QString>
#include <QTextStream>

namespace internal {
	namespace Sql {
		typedef enum {
			SELECT,
			INSERT,
			UPDATE,
			REPLACE,
			DELETE
		} QueryType;
	}
	
	class SqlBuilder {
		public:
			SqlBuilder(Sql::QueryType type);
			SqlBuilder(const SqlBuilder& builder);
			
			SqlBuilder& FROM(const QString& tablename);
			SqlBuilder& INTO(const QString& tablename);
			SqlBuilder& SET(const QString& variables);
			SqlBuilder& WHERE(const QString& whereClause);
			SqlBuilder& GROUPBY(const QString& fieldname);
			SqlBuilder& LIMIT(unsigned lowerLimit, unsigned count = 0);
			
			SqlBuilder& setSelectVariables(const QString& newSelectVariables);
			SqlBuilder& setTable(const QString& tablename);
			
			QString getQuery() const;
		private:
			QString sql;
			QTextStream stream;
	};
}