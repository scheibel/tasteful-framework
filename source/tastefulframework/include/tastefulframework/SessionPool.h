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

#include <tastefulframework/AbstractSession.h>
#include <tastefulframework/ObjectConstructor.h>
#include <tastefulframework/Request.h>
#include <tastefulframework/Response.h>
#include <QTimer>
#include <QReadWriteLock>

#include <tastefulframework/tastefulframework_api.h>

class TASTEFULFRAMEWORK_API SessionPool : public QObject {
    Q_OBJECT

    public:
        SessionPool();
        ~SessionPool();

        template<class SessionClass> void setSessionClass();

        AbstractSession* getSessionFor(Request& request);
        void addSessionTo(Request& request);
    protected slots:
        void expireSession(const QString& sessionKey);
    protected:
        bool hasSession(const QString& sessionKey);
        void addSession(const QString& sessionKey, AbstractSession* session);
        AbstractSession* getSession(const QString& sessionKey);
        void removeSession(const QString& sessionKey);

        AbstractSession* getNewSession();
        AbstractSession* obtainSession(const QString& sessionKey);
        AbstractSession* createSession();

        void initializeSession(AbstractSession* session, const QString& sessionKey);
        QString getUniqueId(AbstractSession* session);
        QString getHash(AbstractSession* session, unsigned attempt);

        QReadWriteLock lock;
        QHash<QString, AbstractSession*> sessions;
        AbstractObjectConstructor<AbstractSession>* sessionConstructor;
        static unsigned defaultLifetime;
};

template<class SessionClass>
void SessionPool::setSessionClass() {
    sessionConstructor = new ObjectConstructor<AbstractSession, SessionClass>();
}
