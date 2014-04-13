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

#include <QString>
#include <QList>

#include <tastefulframework/DataMapper.h>

template <class T, typename Identity = unsigned>
class ActiveRecordDataMapper : public DataMapper<ActiveRecordDataMapper<T, Identity>, T, Identity>
{
public:
    ActiveRecordDataMapper()
    {
        _databaseName = T::databaseName();
        _fieldNames = T::fieldNames();
        _tableName = T::tableName();
        _primaryKeyName = T::primaryKeyName();
    }

    virtual void buildFromRecord(T * model, const QVariantMap & record) const
    {
        model->initializeFromRecord(record);
        model->setSaved();
    }

    virtual void buildRecordFrom(T * model, QVariantMap & record) const
    {
        model->serializeToRecord(record);
    }

    virtual QString table() const
    {
        return _tableName;
    }

    virtual QList<QString> selectVariables() const
    {
        return _fieldNames;
    }

    virtual QString identityFieldName() const
    {
        return _primaryKeyName;
    }

    virtual QString databaseId() const
    {
        return _databaseName;
    }

    virtual void saveRelationsOf(T * model)
    {
        model->saveRelations();
    }

protected:
    QString _databaseName;
    QList<QString> _fieldNames;
    QString _tableName;
    QString _primaryKeyName;
};
