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

#include <tastefulframework/SessionPool.h>

#include <QCryptographicHash>

unsigned SessionPool::defaultLifetime = 900;

SessionPool::SessionPool() : sessionConstructor(new ObjectConstructor<AbstractSession, AbstractSession>()) {
}

SessionPool::~SessionPool() {
	delete sessionConstructor;
}

void SessionPool::addSessionTo(Request& request) {
	request.setSession(getSessionFor(request));
}

AbstractSession* SessionPool::getSessionFor(Request& request) {
	QString sessionKey = request.getCookies().get("sessionId").getValue();
	
	AbstractSession* session = nullptr;
	
	if (sessionKey.isNull() || sessionKey.isEmpty()) {
		session = getNewSession();
	} else {
		session = obtainSession(sessionKey);
	}
	
	session->touch();
	
	return session;
}

AbstractSession* SessionPool::getNewSession() {
	AbstractSession* session = createSession();
	
	initializeSession(session, getUniqueId(session));
	
	return session;
}

AbstractSession* SessionPool::obtainSession(const QString& sessionKey) {
	AbstractSession* session = nullptr;
	
	if (hasSession(sessionKey)) {
		session = getSession(sessionKey);
	} else {
		session = createSession();
		
		initializeSession(session, sessionKey);
	}
	
	return session;
}

void SessionPool::initializeSession(AbstractSession* session, const QString& sessionKey) {
	session->setIdentifier(sessionKey);
	session->setTimeout(defaultLifetime);
	
	addSession(sessionKey, session);
	
	connect(session, SIGNAL(expired(const QString&)), this, SLOT(expireSession(const QString&)));
}

AbstractSession* SessionPool::createSession() {
	return (*sessionConstructor)();
}

void SessionPool::expireSession(const QString& sessionKey) {
	removeSession(sessionKey);
}

QString SessionPool::getUniqueId(AbstractSession* session) {
	QString sessionKey;
	unsigned attempt = 0;
	do {
		sessionKey = getHash(session, attempt++);
	} while (hasSession(sessionKey));
	
	return sessionKey;
}

QString SessionPool::getHash(AbstractSession* session, unsigned attempt) {
	unsigned sessionAddress = *((unsigned*)&session);
	
	return QCryptographicHash::hash(
		(QString::number(sessionAddress, 16) + "x" + QString::number(attempt)).toUtf8(),
		QCryptographicHash::Sha1
	).toHex();
}

// critical methods

bool SessionPool::hasSession(const QString& sessionKey) {
	lock.lockForRead();
	bool has = sessions.contains(sessionKey);
	lock.unlock();
	return has;
}

AbstractSession* SessionPool::getSession(const QString& sessionKey) {
	lock.lockForRead();
	AbstractSession* session = sessions[sessionKey];
	lock.unlock();
	return session;
}

void SessionPool::addSession(const QString& sessionKey, AbstractSession* session) {
	lock.lockForWrite();
	sessions.insert(sessionKey, session);
	lock.unlock();
}

void SessionPool::removeSession(const QString& sessionKey) {
	lock.lockForWrite();
	sessions.remove(sessionKey);
	lock.unlock();
}
