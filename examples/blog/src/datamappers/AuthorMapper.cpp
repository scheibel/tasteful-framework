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

#include <datamappers/AuthorMapper.h>

AuthorMapper::AuthorMapper() {
}

void AuthorMapper::buildFromRecord(Author* model, const QVariantMap& record) const {
	model->setEmail(record["email"].toString());
	model->setPassword(record["password"].toString());
	model->setSalt(record["salt"].toString());
}

void AuthorMapper::buildRecordFrom(Author* model, QVariantMap& record) const {
	record.insert("email", model->getEmail());
	record.insert("password", model->getPassword());
	record.insert("salt", model->getSalt());
}

QList<QString> AuthorMapper::selectVariables() const {
	return { "email", "password", "salt" };
}

QString AuthorMapper::identityFieldName() const {
	return "id";
}

QString AuthorMapper::table() const {
	return "authors";
}

QString AuthorMapper::databaseId() const {
	return "blog";
}
