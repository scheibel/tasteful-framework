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

#include <tastefulframework/SessionPool.h>

#include <QCryptographicHash>

namespace tastefulframework {

unsigned SessionPool::s_defaultLifetime = 900;
SessionPool::SessionPool()
    : m_sessionConstructor(new ObjectConstructor<AbstractSession, AbstractSession>())
{
}

SessionPool::~SessionPool()
{
    delete m_sessionConstructor;
}

void SessionPool::addSessionTo(Request & request)
{
    request.setSession(getSessionFor(request));
}

AbstractSession * SessionPool::getSessionFor(Request & request)
{
    QString sessionKey = request.getCookies().get("sessionId").getValue();
    AbstractSession * session = nullptr;

    if (sessionKey.isNull() || sessionKey.isEmpty())
    {
        session = getNewSession();
    }
    else
    {
        session = obtainSession(sessionKey);
    }

    session->touch();

    return session;
}

AbstractSession * SessionPool::getNewSession()
{
    AbstractSession * session = createSession();

    initializeSession(session, getUniqueId(session));

    return session;
}

AbstractSession * SessionPool::obtainSession(const QString & sessionKey)
{
    AbstractSession * session = nullptr;

    if (hasSession(sessionKey))
    {
        session = getSession(sessionKey);
    }
    else
    {
        session = createSession();

        initializeSession(session, sessionKey);
    }

    return session;
}

void SessionPool::initializeSession(AbstractSession * session, const QString & sessionKey)
{
    session->setIdentifier(sessionKey);
    session->setTimeout(s_defaultLifetime);

    addSession(sessionKey, session);

    connect(session, SIGNAL(expired(const QString &)), this, SLOT(expireSession(const QString &)));
}

AbstractSession * SessionPool::createSession()
{
    return (*m_sessionConstructor)();
}

void SessionPool::expireSession(const QString & sessionKey)
{
    removeSession(sessionKey);
}

QString SessionPool::getUniqueId(AbstractSession * session)
{
    QString sessionKey;
    unsigned attempt = 0;

    do
    {
        sessionKey = getHash(session, attempt++);
    }
    while (hasSession(sessionKey));

    return sessionKey;
}

QString SessionPool::getHash(AbstractSession * session, unsigned attempt)
{
    unsigned sessionAddress = *((unsigned *)&session);

    return QCryptographicHash::hash((QString::number(sessionAddress, 16) + "x" + QString::number(attempt)).toUtf8(), QCryptographicHash::Sha1).toHex();
}

// critical methods

bool SessionPool::hasSession(const QString & sessionKey)
{
    m_lock.lockForRead();
    bool has = m_sessions.contains(sessionKey);
    m_lock.unlock();

    return has;
}

AbstractSession * SessionPool::getSession(const QString & sessionKey)
{
    m_lock.lockForRead();
    AbstractSession * session = m_sessions[sessionKey];
    m_lock.unlock();

    return session;
}

void SessionPool::addSession(const QString & sessionKey, AbstractSession * session)
{
    m_lock.lockForWrite();
    m_sessions.insert(sessionKey, session);
    m_lock.unlock();
}

void SessionPool::removeSession(const QString & sessionKey)
{
    m_lock.lockForWrite();
    m_sessions.remove(sessionKey);
    m_lock.unlock();
}

} // namespace tastefulframework
