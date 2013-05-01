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

#include <datamappers/BlogPostMapper.h>

#include <datamappers/AuthorMapper.h>
#include <datamappers/TagMapper.h>

#include <internal/Database>

#include <QSet>

void BlogPostMapper::buildFromRecord(BlogPost* model, const QVariantMap& record) const {
	model->setAuthor(AuthorMapper::instance().get(record["author"].toUInt()));
	model->setTitle(record["title"].toString());
	model->setText(record["text"].toString());
	model->setTags(findTagsFor(record["id"].toUInt()));
}

void BlogPostMapper::buildRecordFrom(BlogPost* model, QVariantMap& record) const {
	record.insert("author", AuthorMapper::instance().saveReturningId(model->getAuthor()));
	record.insert("title", model->getTitle());
	record.insert("text", model->getText());
}

QList<QString> BlogPostMapper::selectVariables() const {
	return { "author", "title", "text" };
}

QString BlogPostMapper::identityFieldName() const {
	return "id";
}

QString BlogPostMapper::table() const {
	return "blogentries";
}

void BlogPostMapper::saveRelationsOf(BlogPost* model) {
	unsigned blogPostId = idOf(model);
	QSet<Tag*> oldTags = findTagsFor(blogPostId).toSet();
	QSet<Tag*> newTags = model->getTags().toSet();
	
	for (Tag* tag : oldTags - newTags) {
		getDatabase().build(DELETE().FROM("relatedTags").WHERE("tag = "+QString::number(TagMapper::instance().idOf(tag)))).exec();
	}
	
	for (Tag* tag : newTags - oldTags) {
		getDatabase().build(INSERT().INTO("relatedTags").SET("blogentry = "+QString::number(blogPostId)+", tag = "+QString::number(TagMapper::instance().idOf(tag)))).exec();
	}
}

QString BlogPostMapper::databaseId() const {
	return "blog";
}

QList<Tag*> BlogPostMapper::findTagsFor(unsigned blogPostId) {
	return TagMapper::instance().basicFind("SELECT `tags`.id AS id, `tags`.name AS name FROM `tags` LEFT OUTER JOIN `relatedTags` ON `relatedTags`.tag = `tags`.id WHERE `relatedTags`.blogentry = " + QString::number(blogPostId));
}
