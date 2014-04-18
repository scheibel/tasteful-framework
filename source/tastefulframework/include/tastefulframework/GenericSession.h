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

#include <QString>
#include <QHash>
#include <QVariant>

#include <tastefulframework/tastefulframework_api.h>

#include <tastefulframework/AbstractSession.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API GenericSession : public AbstractSession
{
public:
    GenericSession();
    ~GenericSession();

    bool has(const QString & key) const;
    template <typename T>
    T get(const QString & key) const;
    template <typename T>
    void set(const QString & key, T value);

protected:
    QHash<QString, QVariant> m_values;
};

} // namespace tastefulframework

#include <tastefulframework/GenericSession.hpp>
