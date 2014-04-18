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

#include <tastefulframework/ActiveRecord.h>

namespace tastefulframework {

template <class T, typename Identity>
ActiveRecord<T, Identity>::ActiveRecord()
: m_saved(false)
{
}

template <class T, typename Identity>
ActiveRecord<T, Identity>::~ActiveRecord()
{
}

template <class T, typename Identity>
T* ActiveRecord<T, Identity>::getBy(const QString & whereClause)
{
	return dataMapper().getBy(whereClause);
}

template <class T, typename Identity>
QList<T *> ActiveRecord<T, Identity>::find(const QString & whereClause)
{
	return dataMapper().find(whereClause);
}

template <class T, typename Identity>
T* ActiveRecord<T, Identity>::get(Identity id)
{
	return dataMapper().get(id);
}

template <class T, typename Identity>
QList<T *> ActiveRecord<T, Identity>::all()
{
	return dataMapper().all();
}

template <class T, typename Identity>
Identity ActiveRecord<T, Identity>::getPrimaryKey()
{
	return dataMapper().idOf(dynamic_cast<T *>(this));
}

template <class T, typename Identity>
void ActiveRecord<T, Identity>::setSaved(bool b)
{
	m_saved = b;
}

template <class T, typename Identity>
bool ActiveRecord<T, Identity>::isSaved()
{
	return m_saved;
}

template <class T, typename Identity>
bool ActiveRecord<T, Identity>::save()
{
	if (m_saved)
	{
	    return true;
	}

	return dataMapper().save(dynamic_cast<T *>(this));
}

template <class T, typename Identity>
Identity ActiveRecord<T, Identity>::saveReturningId()
{
	save();

	return getPrimaryKey();
}

template <class T, typename Identity>
void ActiveRecord<T, Identity>::saveRelations()
{
	
}

template <class T, typename Identity>
ActiveRecordDataMapper<T, Identity>& ActiveRecord<T, Identity>::dataMapper()
{
    return ActiveRecordDataMapper<T, Identity>::instance();
}

} // namespace tastefulframework
