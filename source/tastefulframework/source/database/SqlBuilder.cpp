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

#include <tastefulframework/SqlBuilder.h>

#include <QStringList>

namespace tastefulframework {

SqlBuilder::SqlBuilder(Sql::QueryType type)
    : stream(&m_sql)
{
    switch (type)
    {
        case Sql::SELECT:
            stream << "SELECT";
            break;
        case Sql::INSERT:
            stream << "INSERT";
            break;
        case Sql::UPDATE:
            stream << "UPDATE";
            break;
        case Sql::REPLACE:
            stream << "REPLACE";
            break;
        case Sql::DELETE:
            stream << "DELETE";
            break;
    }
}

SqlBuilder::SqlBuilder(const SqlBuilder & builder)
    : m_sql(builder.m_sql)
    , stream(&m_sql)
{
}

QString SqlBuilder::getQuery() const
{
    return m_sql;
}

SqlBuilder &SqlBuilder::setSelectVariables(const QString & selectVariables)
{
    stream << " " << selectVariables;

    return *this;
}

SqlBuilder &SqlBuilder::setTable(const QString & tablename)
{
    stream << " " << tablename;

    return *this;
}

SqlBuilder &SqlBuilder::FROM(const QString & tablename)
{
    stream << " FROM " << tablename;

    return *this;
}

SqlBuilder &SqlBuilder::INTO(const QString & tablename)
{
    stream << " INTO " << tablename;

    return *this;
}

SqlBuilder &SqlBuilder::SET(const QString & variables)
{
    stream << " SET " << variables;

    return *this;
}

SqlBuilder &SqlBuilder::SET(const QList<QString> & variables, bool useVALUES)
{
    if (useVALUES)
    {
        QStringList partBeforeValues;
        QStringList partAfterValues;

        for (const QString & key : variables)
        {
            partBeforeValues << key;
            partAfterValues << (":" + key);
        }

        stream << " (" << partBeforeValues.join(", ") << ") VALUES (" << partAfterValues.join(", ") << ")";
    }
    else
    {
        QStringList part;

        for (const QString & key : variables)
        {
            part << (key + " = :" + key);
        }

        stream << " SET " << part.join(", ");
    }

    return *this;
}

SqlBuilder &SqlBuilder::WHERE(const QString & whereClause)
{
    stream << " WHERE " << whereClause;

    return *this;
}

SqlBuilder &SqlBuilder::LIMIT(unsigned lowerLimit, unsigned count)
{
    if (count)
    {
        stream << " LIMIT " << QString::number(lowerLimit) << ", " << QString::number(count);
    }
    else
    {
        stream << " LIMIT " << QString::number(lowerLimit);
    }

    return *this;
}

SqlBuilder &SqlBuilder::GROUPBY(const QString & fieldname)
{
    stream << " GROUP BY " << fieldname;

    return *this;
}

} // namespace tastefulframework
