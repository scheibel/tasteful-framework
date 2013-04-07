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

#include <internal/IdentityMap>
#include <internal/Database>
#include <internal/SqlHelper>

#include <QList>
#include <QString>
#include <QVariantMap>
#include <QSqlRecord>

using namespace internal;

template <class Subclass, class T, typename I = unsigned>
class DataMapper : protected SqlHelper {
protected:
	DataMapper();
	DataMapper(const DataMapper&);
	virtual ~DataMapper();
	DataMapper& operator=(const DataMapper&);
private:
	static Subclass* _instance;
public:
	typedef T Model;
	typedef I Identity;

	static Subclass& instance();

	virtual T* newModel() const = 0;
	virtual void buildFromRecord(T* model, const QVariantMap& record) const = 0;
	virtual void buildRecordFrom(T* model, QVariantMap& record) const = 0;
	virtual QString table() const = 0;
	virtual QList<QString> selectVariables() const = 0;
	virtual QString identityFieldName() const = 0;
	virtual QString databaseId() const;
	virtual void saveRelationsOf(T* model);

	Database& getDatabase() const;
	Identity idOf(T* model) const;
	bool isValidId(const Identity& id) const;
	T* obtainFromIdentityMap(const QVariantMap& map);
	T* get(const Identity& id);
	T* getBy(const QString& whereClause);
	QList<T*> find(const QString& whereClause);
	QList<T*> all();

	Identity saveReturningId(T* model);
	bool save(T* model);
	bool remove(T* model);

	/*
	QVariant averageOf(QString field, QString whereClause);
	QVariant minOf(QString field, QString whereClause);
	QVariant maxOf(QString field, QString whereClause);
	QVariant countOf(QString field, QString whereClause);
	QVariant aggregateOf(QString field, QString aggregationType, QString whereClause);
	*/
private:
	IdentityMap<T, I> identities;
};

template <class Subclass, class T, typename I>
DataMapper<Subclass, T, I>::DataMapper() {
}

template <class Subclass, class T, typename I>
DataMapper<Subclass, T, I>::~DataMapper() {
}

template <class Subclass, class T, typename I>
Subclass* DataMapper<Subclass, T, I>::_instance = new Subclass();

template <class Subclass, class T, typename I>
Subclass& DataMapper<Subclass, T, I>::instance() {
	return *_instance;
}

template <class Subclass, class T, typename I>
I DataMapper<Subclass, T, I>::idOf(T* model) const {
	return identities.idOf(model);
}

template <class Subclass, class T, typename I>
bool DataMapper<Subclass, T, I>::isValidId(const Identity& id) const {
	return (bool)id;
}

template <class Subclass, class T, typename I>
T* DataMapper<Subclass, T, I>::obtainFromIdentityMap(const QVariantMap& map) {
	T* model = nullptr;

	QVariant variantId = map[identityFieldName()]; // hack because of compile errors if those two lines are just one
	Identity id = variantId.value<Identity>();

	if (identities.hasModel(id)) {
		model = identities.getModel(id);
	} else {
		model = newModel();

		buildFromRecord(model, map);

		identities.registerModel(id, model);
	}

	return model;
}

template <class Subclass, class T, typename I>
T* DataMapper<Subclass, T, I>::get(const Identity& id) {
	if (identities.hasModel(id)) {
		return identities.getModel(id);
	}

	return getBy(identityFieldName() + " = " + QVariant(id).toString());
}

template <class Subclass, class T, typename I>
T* DataMapper<Subclass, T, I>::getBy(const QString& whereClause) {
	QSqlQuery query = getDatabase().build(SELECT("*").FROM(table()).WHERE(whereClause).LIMIT(1));

	if (query.exec()) {
		QSqlRecord record = query.record();
		QMap<QString, int> indices;

		for (unsigned i = 0; i < record.count(); ++i) {
			indices[record.fieldName(i)] = i;
		}

		if (query.next()) {
			QVariantMap map;

			for (QString fieldName : indices.keys()) {
				map[fieldName] = query.value(indices[fieldName]);
			}

			return obtainFromIdentityMap(map);
		}
	}

	return nullptr;
}

template <class Subclass, class T, typename I>
QList<T*> DataMapper<Subclass, T, I>::find(const QString& whereClause) {
	QList<T*> results;

	QSqlQuery query = getDatabase().build(SELECT("*").FROM(table()).WHERE(whereClause));

	if (query.exec()) {
		QSqlRecord record = query.record();
		QMap<QString, int> indices;

		for (unsigned i = 0; i < record.count(); ++i) {
			indices[record.fieldName(i)] = i;
		}

		while (query.next()) {
			QVariantMap map;

			for (QString fieldName : indices.keys()) {
				map[fieldName] = query.value(indices[fieldName]);
			}

			results << obtainFromIdentityMap(map);
		}
	}

	return results;
}

template <class Subclass, class T, typename I>
QList<T*> DataMapper<Subclass, T, I>::all() {
	return find("1");
}

template <class Subclass, class T, typename I>
I DataMapper<Subclass, T, I>::saveReturningId(T* model) {
	save(model);

	return idOf(model);
}

template <class Subclass, class T, typename I>
bool DataMapper<Subclass, T, I>::save(T* model) {
	if (!model) {
		return false;
	}

	Identity id = idOf(model);
	QVariantMap record;
	buildRecordFrom(model, record);

	QString variables;
	bool first = true;
	for (QString key : record.keys()) {
		if (first) {
			first = false;
		} else {
			variables += ", ";
		}

		variables += key + " = :" + key;
	}

	record[identityFieldName()] = id;

	if (isValidId(id)) {
		QSqlQuery query = getDatabase().build(UPDATE(table()).SET(variables).WHERE(identityFieldName() + " = :" + identityFieldName()), record);

		query.exec();
	} else {
		QSqlQuery query = getDatabase().build(INSERT().INTO(table()).SET(variables), record);

		if (query.exec()) {
			Identity id = query.lastInsertId().value<Identity>();

			if (isValidId(id)) {
				identities.registerModel(id, model);
			}
		}
	}

	saveRelationsOf(model);

	return true;
}

template <class Subclass, class T, typename I>
bool DataMapper<Subclass, T, I>::remove(T* model) {
	QSqlQuery query = getDatabase().build(DELETE().FROM(table()).WHERE(identityFieldName() + " = " + QString::number(idOf(model))));

	return query.exec();
}

template <class Subclass, class T, typename I>
QString DataMapper<Subclass, T, I>::databaseId() const {
	return QString();
}

template <class Subclass, class T, typename I>
void DataMapper<Subclass, T, I>::saveRelationsOf(T* model) {

}

template <class Subclass, class T, typename I>
Database& DataMapper<Subclass, T, I>::getDatabase() const {
	return Database::get(databaseId());
}