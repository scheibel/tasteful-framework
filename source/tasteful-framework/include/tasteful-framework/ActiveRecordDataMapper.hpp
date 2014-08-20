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

#include <tasteful-framework/ActiveRecordDataMapper.h>

namespace tastefulframework {

template <class T, typename Identity>
ActiveRecordDataMapper<T, Identity>::ActiveRecordDataMapper()
{
    m_databaseName = T::databaseName();
    m_fieldNames = T::fieldNames();
    m_tableName = T::tableName();
    m_primaryKeyName = T::primaryKeyName();
}

template <class T, typename Identity>
void ActiveRecordDataMapper<T, Identity>::buildFromRecord(T * model, const QVariantMap & record) const
{
    model->initializeFromRecord(record);
    model->setSaved();
}

template <class T, typename Identity>
void ActiveRecordDataMapper<T, Identity>::buildRecordFrom(T * model, QVariantMap & record) const
{
    model->serializeToRecord(record);
}

template <class T, typename Identity>
QString ActiveRecordDataMapper<T, Identity>::table() const
{
    return m_tableName;
}

template <class T, typename Identity>
QList<QString> ActiveRecordDataMapper<T, Identity>::selectVariables() const
{
    return m_fieldNames;
}

template <class T, typename Identity>
QString ActiveRecordDataMapper<T, Identity>::identityFieldName() const
{
    return m_primaryKeyName;
}

template <class T, typename Identity>
QString ActiveRecordDataMapper<T, Identity>::databaseId() const
{
    return m_databaseName;
}

template <class T, typename Identity>
void ActiveRecordDataMapper<T, Identity>::saveRelationsOf(T * model)
{
    model->saveRelations();
}

} // namespace tastefulframework
