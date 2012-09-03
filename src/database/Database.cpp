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

#include <internal/Database>

#include <QSqlError>
#include <QThread>

using namespace internal;

QHash<QString, Database*> Database::databases;
QReadWriteLock Database::lock;

Database::Database(QSqlDatabase database) : database(database) {
}

Database& Database::get() {
	return getByIdAndThreadId(QString(), QString::number(QThread::currentThreadId()));
}

Database& Database::get(const QString& id) {
	return getByIdAndThreadId(id, QString::number(QThread::currentThreadId()));
}

Database& Database::getByIdAndThreadId(QString id, QString threadId) {
	QString databaseId = id.isNull() ? threadId : id + "-" + threadId;
	
	lock.lockForRead();
	
	if (!databases.contains(databaseId)) {
		lock.unlock();
		lock.lockForWrite();
		
		QSqlDatabase prototypeDb = id.isNull() ? QSqlDatabase::database() : QSqlDatabase::database(id);
		
		if (!prototypeDb.isValid()) {
			//QString("CanNo connection with id  "+id+" found");
		}
		
		QSqlDatabase threadDb = QSqlDatabase::cloneDatabase(prototypeDb, databaseId);
		
		if (!threadDb.open()) {
			//QString("Can't establish database connection "+id+": "+threadDb.lastError().text());
		}
		
		databases.insert(databaseId, new Database(threadDb));
	}
	
	lock.unlock();
	
	return *databases[databaseId];
}

void Database::add(const DatabaseConfig& config) {
	if (config.type.isEmpty()) {
		throw QString("Can't establish database connection "+config.id+": No type is set");
	}
	
	QString type = config.type;
	if (type=="mysql") type = "QMYSQL";
	else if (type=="sqlite") type = "QSQLITE";
	
	QSqlDatabase database;
	
	if (config.id.isNull()) {
		database = QSqlDatabase::addDatabase(type);
	} else {
		database = QSqlDatabase::addDatabase(type, config.id);
	}
	
	if (!config.host.isNull()) database.setHostName(config.host);
	if (!config.name.isNull()) database.setDatabaseName(config.name);
	if (!config.user.isNull()) database.setUserName(config.user);
	if (!config.password.isNull()) database.setPassword(config.password);
}

QSqlQuery Database::build(QString sql) {
	QSqlQuery query(database);
	
	query.prepare(sql);
	
	return query;
}

QSqlQuery Database::build(QString sql, QVariantMap bindings) {
	QSqlQuery query = build(sql);
	
	for (QString key : bindings.keys()) {
		query.bindValue(":" + key, bindings[key]);
	}
	
	return query;
}

QSqlQuery Database::build(const SqlBuilder& sqlBuilder) {
	QString sql = sqlBuilder.getQuery();
	
	QSqlQuery query = build(sql);
	
	return query;
}

QSqlQuery Database::build(const SqlBuilder& sqlBuilder, QVariantMap bindings) {
	QString sql = sqlBuilder.getQuery();
	
	QSqlQuery query = build(sql, bindings);
	
	return query;
}
