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

#include <tastefulframework/DataMapper.h>

namespace tastefulframework {

template <class Subclass, class T, typename I>
DataMapper<Subclass, T, I>::DataMapper()
{
}

template <class Subclass, class T, typename I>
DataMapper<Subclass, T, I>::~DataMapper()
{
}

template <class Subclass, class T, typename I>
Subclass * DataMapper<Subclass, T, I>::s_instance = new Subclass();

template <class Subclass, class T, typename I>
Subclass & DataMapper<Subclass, T, I>::instance()
{
    return *s_instance;
}

template <class Subclass, class T, typename I>
T * DataMapper<Subclass, T, I>::newModel() const
{
    return new T();
}

template <class Subclass, class T, typename I>
I DataMapper<Subclass, T, I>::idOf(T * model) const
{
    return m_identities.idOf(model);
}

template <class Subclass, class T, typename I>
bool DataMapper<Subclass, T, I>::isValidId(const Identity & id) const
{
    return (bool)id;
}

template <class Subclass, class T, typename I>
T * DataMapper<Subclass, T, I>::obtainFromIdentityMap(const QVariantMap & map)
{
    T * model = nullptr;
    QVariant variantId = map[identityFieldName()]; // hack because of compile errors if those two lines are just one
    Identity id = variantId.value<Identity>();

    if (m_identities.hasModel(id))
    {
        model = m_identities.getModel(id);
    }
    else
    {
        model = newModel();

        buildFromRecord(model, map);

        m_identities.registerModel(id, model);
    }

    return model;
}

template <class Subclass, class T, typename I>
T * DataMapper<Subclass, T, I>::get(const Identity & id)
{
    if (m_identities.hasModel(id))
    {
        return m_identities.getModel(id);
    }

    return getBy(identityFieldName() + " = " + QVariant(id).toString());
}

template <class Subclass, class T, typename I>
T * DataMapper<Subclass, T, I>::getBy(const QString & whereClause)
{
    QSqlQuery query = getDatabase().build(SELECT("*").FROM(table()).WHERE(whereClause).LIMIT(1));

    if (query.exec())
    {
        QSqlRecord record = query.record();
        QMap<QString, int> indices;

        for (unsigned i = 0;i < record.count();++i)
        {
            indices[record.fieldName(i)] = i;
        }

        if (query.next())
        {
            QVariantMap map;

            for (QString fieldName : indices.keys())
            {
                map[fieldName] = query.value(indices[fieldName]);
            }

            return obtainFromIdentityMap(map);
        }
    }

    return nullptr;
}

template <class Subclass, class T, typename I>
QList<T *> DataMapper<Subclass, T, I>::find(const QString & whereClause)
{
    return basicFind(SELECT("*").FROM(table()).WHERE(whereClause));
}

template <class Subclass, class T, typename I>
QList<T *> DataMapper<Subclass, T, I>::basicFind(const SqlBuilder & sqlBuilder)
{
    QList<T *> results;

    QSqlQuery query = getDatabase().build(sqlBuilder);

    if (query.exec())
    {
        QSqlRecord record = query.record();
        QMap<QString, int> indices;

        for (unsigned i = 0;i < record.count();++i)
        {
            indices[record.fieldName(i)] = i;
        }

        while (query.next())
        {
            QVariantMap map;

            for (QString fieldName : indices.keys())
            {
                map[fieldName] = query.value(indices[fieldName]);
            }

            results << obtainFromIdentityMap(map);
        }
    }

    return results;
}

template <class Subclass, class T, typename I>
QList<T *> DataMapper<Subclass, T, I>::basicFind(const QString & sql)
{
    QList<T *> results;

    QSqlQuery query = getDatabase().build(sql);

    if (query.exec())
    {
        QSqlRecord record = query.record();
        QMap<QString, int> indices;

        for (unsigned i = 0;i < record.count();++i)
        {
            indices[record.fieldName(i)] = i;
        }

        while (query.next())
        {
            QVariantMap map;

            for (QString fieldName : indices.keys())
            {
                map[fieldName] = query.value(indices[fieldName]);
            }

            results << obtainFromIdentityMap(map);
        }
    }

    return results;
}

template <class Subclass, class T, typename I>
QList<T *> DataMapper<Subclass, T, I>::all()
{
    return find("1");
}

template <class Subclass, class T, typename I>
I DataMapper<Subclass, T, I>::saveReturningId(T * model)
{
    save(model);

    return idOf(model);
}

template <class Subclass, class T, typename I>
bool DataMapper<Subclass, T, I>::save(T * model)
{
    if (!model)
    {
        return false;
    }

    Identity id = idOf(model);
    QVariantMap record;
    buildRecordFrom(model, record);

    QList<QString> variables = record.keys();

    if (isValidId(id))
    {
        record[identityFieldName()] = id;

        QSqlQuery query = getDatabase().build(UPDATE(table()).SET(variables).WHERE(identityFieldName() + " = :" + identityFieldName()), record);

        query.exec();
    }
    else
    {
        QSqlQuery query = getDatabase().build(INSERT().INTO(table()).SET(variables, true), record);

        if (query.exec())
        {
            Identity id = query.lastInsertId().value<Identity>();

            if (isValidId(id))
            {
                m_identities.registerModel(id, model);
            }
        }
    }

    saveRelationsOf(model);

    return true;
}

template <class Subclass, class T, typename I>
bool DataMapper<Subclass, T, I>::remove(T * model)
{
    QSqlQuery query = getDatabase().build(DELETE().FROM(table()).WHERE(identityFieldName() + " = " + QString::number(idOf(model))));

    return query.exec();
}

template <class Subclass, class T, typename I>
QString DataMapper<Subclass, T, I>::databaseId() const
{
    return QString();
}

template <class Subclass, class T, typename I>
void DataMapper<Subclass, T, I>::saveRelationsOf(T * /*model*/)
{

}

template <class Subclass, class T, typename I>
Database & DataMapper<Subclass, T, I>::getDatabase() const
{
    return Database::get(databaseId());
}

} // namespace tastefulframework
