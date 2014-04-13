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
#include <QVariant>
#include <QVariantMap>

#include <QDebug>

#include <tastefulframework/ActiveRecordDataMapper.h>

namespace tastefulframework {

template <class T, typename Identity = unsigned>
class ActiveRecord
{
public:
    ActiveRecord()
        : saved(false)
    {
    }

    virtual ~ActiveRecord()
    {
    }

    typedef ActiveRecordDataMapper<T, Identity> DataMapper;
    static T* getBy(const QString & whereClause)
    {
        return dataMapper().getBy(whereClause);
    }

    static QList<T *> find(const QString & whereClause)
    {
        return dataMapper().find(whereClause);
    }

    static T* get(Identity id)
    {
        return dataMapper().get(id);
    }

    static QList<T *> all()
    {
        return dataMapper().all();
    }

    Identity getPrimaryKey()
    {
        return dataMapper().idOf(dynamic_cast<T *>(this));
    }

    void setSaved(bool b = true)
    {
        saved = b;
    }

    bool isSaved()
    {
        return saved;
    }

    bool save()
    {
        if (saved)
        {
            return true;
        }

        return dataMapper().save(dynamic_cast<T *>(this));
    }

    Identity saveReturningId()
    {
        save();

        return getPrimaryKey();
    }

    void saveRelations()
    {

    }

protected:
    bool saved;
    static DataMapper&dataMapper()
    {
        return DataMapper::instance();
    }

};

#define INTERN_PROPERTY(name, type) \
private: \
    type _ ## name; \
public: \
    type name() const { return _ ## name;}; \
    void name(type name) { _ ## name = name;saved = false;}; \
private:

#define INTERN_CONST_PROPERTY(name, type) \
private: \
    type _ ## name; \
public: \
    const type & name() const { return _ ## name;}; \
    void name(const type &name) { _ ## name = name;saved = false;}; \
private:

#define DATABASE_NAME(name) \
public: \
    static QString databaseName() { return #name;}; \
private:

#define DATABASE_TABLENAME(name) \
public: \
    static QString tableName() { return #name;}; \
private:

#define DATABASE_PRIMARY_KEY(key, keyType) \
public: \
    static QString primaryKeyName() { return #key;}; \
private:

#define DATABASE_FIELDNAMES(...) \
public: \
    static QList<QString> fieldNames() { return { __VA_ARGS__ };}; \
private:

#define DECLARE_PROPERTY(name, type) \
    INTERN_CONST_PROPERTY(name, type) \
    void name(const QVariant &name) { _ ## name = name.value<type>();saved = false;};

#define DECLARE_RELATION(name, type) \
    INTERN_PROPERTY(name, type *) \
    void name(const QVariant &name) { _ ## name = type::get(name.value<unsigned>());saved = false;};


#define ENTITY_INITIALIZER(code) \
public: \
    void initializeFromRecord(const QVariantMap &record) { \
        code; \
    }; \
private:

#define INITIALIZE(variableName) variableName(record[#variableName]);

#define ENTITY_SAVER(code) \
public: \
    void serializeToRecord(QVariantMap & record) { \
        code; \
        \
        qDebug() << record; \
    }; \
private:

#define SAVE(variableName) record.insert(#variableName, variableName());

#define SAVE_RELATION(variableName) record.insert(#variableName, variableName()->saveReturningId());

} // namespace tastefulframework
