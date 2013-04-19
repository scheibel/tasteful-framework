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

#include <models/BlogPost.h>

#include <DataMapper>

class BlogPostMapper : public DataMapper<BlogPostMapper, BlogPost, unsigned> {
public:
	BlogPostMapper();
	
	void buildFromRecord(BlogPost* model, const QVariantMap& record) const;
	void buildRecordFrom(BlogPost* model, QVariantMap& record) const;
	QList<QString> selectVariables() const;
	QString identityFieldName() const;
	QString table() const;
	void saveRelationsOf(BlogPost* model);
	QString databaseId() const;
protected:
	static QList<Tag*> findTagsFor(unsigned blogPostId);
};
