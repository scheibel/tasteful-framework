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

#define DECLARE_NxM_RELATION(singleName, name, className)
#define INITIALIZE_NxM_RELATION(name, className, foreignKey)
#define SAVE_NxM_RELATION(name, className, foreignKey)

#include <models/Author.h>
#include <models/Tag.h>

#include <QString>
#include <QList>
#include <tastefulframework/ActiveRecord.h>

class BlogPost : public tastefulframework::ActiveRecord<BlogPost, unsigned>
{
    DATABASE_NAME(blog);
    DATABASE_TABLENAME(blogentries);
    DATABASE_PRIMARY_KEY(id, unsigned);
    DATABASE_FIELDNAMES("author", "title", "text");
    DECLARE_RELATION(author, Author);
    DECLARE_PROPERTY(title, QString);
    DECLARE_PROPERTY(text, QString);
    DECLARE_NxM_RELATION(tag, tags, Tag);
    ENTITY_INITIALIZER(INITIALIZE(author);
        INITIALIZE(title);
        INITIALIZE(text);
        INITIALIZE_NxM_RELATION(tags, Tag, blogEntry);
        );
    ENTITY_SAVER(SAVE_RELATION(author);
        SAVE(title);
        SAVE(text);
        SAVE_NxM_RELATION(tags, Tag, blogEntry);
        );

public:
    BlogPost();
};
