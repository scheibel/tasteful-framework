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

#include <internal/SqlBuilder>

using namespace internal;

SqlBuilder::SqlBuilder(Sql::QueryType type) {
	switch (type) {
		case Sql::SELECT:
			sql = "SELECT";
		break;
		case Sql::INSERT:
			sql = "INSERT";
		break;
		case Sql::UPDATE:
			sql = "UPDATE";
		break;
		case Sql::REPLACE:
			sql = "REPLACE";
		break;
		case Sql::DELETE:
			sql = "DELETE";
		break;
	}
}

QString SqlBuilder::getQuery() const {
	return sql;
}

SqlBuilder& SqlBuilder::setSelectVariables(QString selectVariables) {
	sql += " " + selectVariables;
	
	return *this;
}

SqlBuilder& SqlBuilder::setTable(QString tablename) {
	sql += " " + tablename;
	
	return *this;
}

SqlBuilder& SqlBuilder::FROM(QString tablename) {
	sql += " FROM " + tablename;
	
	return *this;
}

SqlBuilder& SqlBuilder::INTO(QString tablename) {
	//sql += " INTO " + tablename;
	sql += " " + tablename;
	
	return *this;
}

SqlBuilder& SqlBuilder::SET(QString variables) {
	sql += " SET " + variables;
	
	return *this;
}

SqlBuilder& SqlBuilder::WHERE(QString whereClause) {
	sql += " WHERE " + whereClause;
	
	return *this;
}

SqlBuilder& SqlBuilder::LIMIT(unsigned lowerLimit, unsigned count) {
	if (count) {
		sql += " LIMIT " + QString::number(lowerLimit) + ", " + QString::number(count);
	} else {
		sql += " LIMIT " + QString::number(lowerLimit);
	}
	
	return *this;
}

SqlBuilder& SqlBuilder::GROUPBY(QString fieldname) {
	sql += " GROUP BY " + fieldname;
	
	return *this;
}