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

#include <internal/SqlHelper>

using namespace internal;

SqlBuilder SqlHelper::SELECT(QString variables) {
	SqlBuilder sqlBuilder(Sql::SELECT);
	
	sqlBuilder.setSelectVariables(variables);
	
	return sqlBuilder;
}

SqlBuilder SqlHelper::INSERT() {
	return SqlBuilder(Sql::INSERT);
}

SqlBuilder SqlHelper::UPDATE(QString tablename) {
	SqlBuilder sqlBuilder(Sql::UPDATE);
	
	sqlBuilder.setTable(tablename);
	
	return sqlBuilder;
}

SqlBuilder SqlHelper::REPLACE() {
	return SqlBuilder(Sql::REPLACE);
}

SqlBuilder SqlHelper::DELETE() {
	return SqlBuilder(Sql::DELETE);
}
