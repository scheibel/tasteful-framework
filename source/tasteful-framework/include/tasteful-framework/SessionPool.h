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

#pragma once

#include <QTimer>
#include <QReadWriteLock>

#include <tasteful-framework/tasteful-framework_api.h>

#include <tasteful-framework/AbstractSession.h>
#include <tasteful-framework/ObjectConstructor.h>
#include <tasteful-framework/Request.h>
#include <tasteful-framework/Response.h>

namespace tastefulframework {

class TASTEFUL_FRAMEWORK_API SessionPool : public QObject
{
    Q_OBJECT

public:
    SessionPool();
    ~SessionPool();

    template <class SessionClass>
    void setSessionClass();

    AbstractSession* getSessionFor(Request & request);
    void addSessionTo(Request & request);

protected slots:
    void expireSession(const QString & sessionKey);

protected:
    bool hasSession(const QString & sessionKey);
    void addSession(const QString & sessionKey, AbstractSession * session);
    AbstractSession* getSession(const QString & sessionKey);
    void removeSession(const QString & sessionKey);

    AbstractSession* getNewSession();
    AbstractSession* obtainSession(const QString & sessionKey);
    AbstractSession* createSession();

    void initializeSession(AbstractSession * session, const QString & sessionKey);
    QString getUniqueId(AbstractSession * session);
    QString getHash(AbstractSession * session, unsigned attempt);

    QReadWriteLock m_lock;
    QHash<QString, AbstractSession *> m_sessions;
    AbstractObjectConstructor<AbstractSession> * m_sessionConstructor;
    static unsigned s_defaultLifetime;
};

} // namespace tastefulframework

#include <tasteful-framework/SessionPool.hpp>
