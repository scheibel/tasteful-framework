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

#include <views/BlogPostShow.h>

#include <views/TagPartial.h>

BlogPostShow::BlogPostShow(Session * session, BlogPost * blogPost, unsigned id)
    : BlogView(session)
    , _blogPost(blogPost)
    , _id(id)
{
    setFilename("blogpostshow.html");

    addTransform("blogposttitle", [this](tastefulframework::DomNode & node) {
            node.inner() = _blogPost->title();
        });

    addTransform("blogpostcontent", [this](tastefulframework::DomNode & node) {
            node.inner() = _blogPost->text();
        });

    addTransform("tags", &BlogPostShow::blogPostTags);
}

void BlogPostShow::blogPostTags(tastefulframework::DomNode & node) const
{
    TagPartial tagPartial(node.children()[0].remove());

    // ~ if (_blogPost->getTags().size()) {
    // ~ for (Tag* tag : _blogPost->getTags()) {
    // ~ tagPartial.setData(tag);
    // ~ node << tagPartial;
    // ~ node << " ";
    // ~ }
    // ~ } else {
    node.inner() = " ";
    // ~ }
}
