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
#include <QList>

#include <tastefulframework/DataMapper.h>

namespace tastefulframework {

template <class T, typename Identity = unsigned>
class ActiveRecordDataMapper : public DataMapper<ActiveRecordDataMapper<T, Identity>, T, Identity>
{
public:
    ActiveRecordDataMapper();

    virtual void buildFromRecord(T * model, const QVariantMap & record) const;
    virtual void buildRecordFrom(T * model, QVariantMap & record) const;
    virtual QString table() const;
    virtual QList<QString> selectVariables() const;
    virtual QString identityFieldName() const;
    virtual QString databaseId() const;
    virtual void saveRelationsOf(T * model);

protected:
    QString m_databaseName;
    QList<QString> m_fieldNames;
    QString m_tableName;
    QString m_primaryKeyName;
};

} // namespace tastefulframework

#include <tastefulframework/ActiveRecordDataMapper.hpp>
