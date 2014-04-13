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

#include <QTimer>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API AbstractSession : public QObject
{
    Q_OBJECT

public:
    AbstractSession();
    virtual ~AbstractSession();

    bool isValid() const;
    bool isInvalid() const;
    void setInvalid(bool newState);

    const QString&getIdentifier() const;
    void setIdentifier(const QString & newIdentifier);

    void touch();
    void setTimeout(unsigned seconds);

protected slots:
    void timeout();

signals:
    void expired(const QString & sessionKey);

private:
    QString identifier;
    bool invalidState;
    unsigned milliseconds;
    QTimer timer;
};

} // namespace tastefulframework
