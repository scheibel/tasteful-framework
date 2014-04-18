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

#include <QList>
#include <QString>
#include <QVariantMap>
#include <QSqlRecord>

#include <tastefulframework/IdentityMap.h>
#include <tastefulframework/Database.h>
#include <tastefulframework/SqlHelper.h>
#include <tastefulframework/IdentityMap.h>

namespace tastefulframework {

template <class Subclass, class T, typename I = unsigned>
class DataMapper : protected SqlHelper
{
protected:
    DataMapper();
    DataMapper(const DataMapper &);
    virtual ~DataMapper();
    DataMapper &operator=(const DataMapper &);

private:
    static Subclass * s_instance;

public:
    typedef T Model;
    typedef I Identity;

    static Subclass & instance();
    virtual T* newModel() const;
    virtual void buildFromRecord(T * model, const QVariantMap & record) const = 0;
    virtual void buildRecordFrom(T * model, QVariantMap & record) const = 0;
    virtual QString table() const = 0;
    virtual QList<QString> selectVariables() const = 0;
    virtual QString identityFieldName() const = 0;
    virtual QString databaseId() const;
    virtual void saveRelationsOf(T * model);
    Database & getDatabase() const;
    Identity idOf(T * model) const;
    bool isValidId(const Identity & id) const;
    T* obtainFromIdentityMap(const QVariantMap & map);
    T* get(const Identity & id);
    T* getBy(const QString & whereClause);
    QList<T *> find(const QString & whereClause);
    QList<T *> basicFind(const SqlBuilder & sqlBuilder);
    QList<T *> basicFind(const QString & sql);
    QList<T *> all();

    Identity saveReturningId(T * model);
    bool save(T * model);
    bool remove(T * model);

    /*
       QVariant averageOf(QString field, QString whereClause);
       QVariant minOf(QString field, QString whereClause);
       QVariant maxOf(QString field, QString whereClause);
       QVariant countOf(QString field, QString whereClause);
       QVariant aggregateOf(QString field, QString aggregationType, QString whereClause);
     */

protected:

private:
    IdentityMap<T, I> m_identities;
};

} // namespace tastefulframework

#include <tastefulframework/DataMapper.hpp>
