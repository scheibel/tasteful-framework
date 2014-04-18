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

#include <tastefulframework/Database.h>

#include <QThread>
#include <QSqlError>

namespace tastefulframework {

QHash<QString, Database *> Database::s_databases;
QReadWriteLock Database::s_lock;
Database::Database(const QSqlDatabase & database)
    : m_database(database)
{
}

Database &Database::get()
{
    return getByIdAndThreadId(QString(), QString::number((long)QThread::currentThreadId()));
}

Database &Database::get(const QString & id)
{
    return getByIdAndThreadId(id, QString::number((long)QThread::currentThreadId()));
}

Database &Database::getByIdAndThreadId(const QString & id, const QString & threadId)
{
    QString databaseId = id.isNull() ? threadId : id + "-" + threadId;

    s_lock.lockForRead();

    if (!s_databases.contains(databaseId))
    {
        s_lock.unlock();
        s_lock.lockForWrite();

        QSqlDatabase prototypeDb = id.isNull() ? QSqlDatabase::database() : QSqlDatabase::database(id);

        if (!prototypeDb.isValid())
        {
            throw QString("No connection with id " + id + " found");
        }

        QSqlDatabase threadDb = QSqlDatabase::cloneDatabase(prototypeDb, databaseId);

        if (!threadDb.open())
        {
            throw QString("Can't establish database connection " + id + ": " + threadDb.lastError().text());
        }

        s_databases.insert(databaseId, new Database(threadDb));
    }

    s_lock.unlock();

    return *s_databases[databaseId];
}

void Database::add(const DatabaseConfig & config)
{
    if (config.type.isEmpty())
    {
        throw QString("Can't establish database connection " + config.id + ": No type is set");
    }

    QString type = config.type;
    if (type=="mysql")
    {
        type = "QMYSQL";
    }
    else if (type=="sqlite")
    {
        type = "QSQLITE";
    }

    QSqlDatabase database;

    if (config.id.isNull())
    {
        database = QSqlDatabase::addDatabase(type);
    }
    else
    {
        database = QSqlDatabase::addDatabase(type, config.id);
    }

    if (!config.host.isNull())
    {
        database.setHostName(config.host);
    }
    if (!config.name.isNull())
    {
        database.setDatabaseName(config.name);
    }
    if (!config.user.isNull())
    {
        database.setUserName(config.user);
    }
    if (!config.password.isNull())
    {
        database.setPassword(config.password);
    }
}

QSqlQuery Database::build(const QString & sql) const
{
    QSqlQuery query(m_database);

    query.prepare(sql);

    return query;
}

QSqlQuery Database::build(const QString & sql, const QVariantMap & bindings) const
{
    QSqlQuery query = build(sql);

    for (const QString & key : bindings.keys())
    {
        query.bindValue(":" + key, bindings[key]);
    }

    return query;
}

QSqlQuery Database::build(const SqlBuilder & sqlBuilder) const
{
    QString sql = sqlBuilder.getQuery();
    QSqlQuery query = build(sql);

    return query;
}

QSqlQuery Database::build(const SqlBuilder & sqlBuilder, const QVariantMap & bindings) const
{
    QString sql = sqlBuilder.getQuery();
    QSqlQuery query = build(sql, bindings);

    return query;
}

} // namespace tastefulframework
