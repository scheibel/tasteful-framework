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

#include <models/Author.h>

#include <QCryptographicHash>

Author::Author() {
}

const QString& Author::getEmail() const {
	return _email;
}

void Author::setEmail(const QString& email) {
	_email = email;
}

const QString& Author::getPassword() const {
	return _password;
}

void Author::setPassword(const QString& password) {
	_password = password;
}

const QString& Author::getSalt() const {
	return _salt;
}

void Author::setSalt(const QString& salt) {
	_salt = salt;
}

bool Author::validatePassword(const QString& password) {
	return _password == calculateHash(password, _salt);
}

void Author::setNewSalt(const QString& salt) {
	_salt = calculateHash(salt, "Blog");
}

void Author::setNewPassword(const QString& password) {
	_password = calculateHash(password, _salt);
}

QString Author::calculateHash(const QString& value, const QString& salt) {
	return QCryptographicHash::hash((salt + value).toUtf8(), QCryptographicHash::Sha1).toHex();
}
