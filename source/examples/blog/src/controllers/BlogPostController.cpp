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

#include <controllers/BlogPostController.h>

#include <views/BlogPostList.h>
#include <views/BlogPostShow.h>
#include <views/BlogPostEdit.h>
#include <models/Author.h>
#include <models/Tag.h>

QList<BlogPost *> BlogPostController::findAll()
{
    return getDataMapper().find("author = " + QString::number(getSession()->author()->getPrimaryKey()));
}

void BlogPostController::beforeSave(BlogPost * blogPost)
{
    // ~ QString tags = parameters["tags"].value<QString>();

    // ~ QList<Tag*> newTags;
    // ~ if (!tags.isNull() && !tags.isEmpty()) {
    // ~ for (const QString& tagName : tags.split(" ")) {
    // ~ newTags << Tag::obtainByName(tagName);
    // ~ }
    // ~ }
    // ~ blogPost->tags(newTags);

    blogPost->author(getSession()->author());
}

void BlogPostController::renderListViewFor(const QHash<unsigned, BlogPost *> & blogPosts)
{
    render(BlogPostList(getSession(), blogPosts));
}

void BlogPostController::renderShowViewFor(BlogPost * blogPost, unsigned id)
{
    render(BlogPostShow(getSession(), blogPost, id));
}

void BlogPostController::renderEditViewFor(BlogPost * blogPost, unsigned id)
{
    render(BlogPostEdit(getSession(), blogPost, id));
}
