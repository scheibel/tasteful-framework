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

#include <views/BlogPostPartial.h>

#include <controllers/BlogPostController.h>
#include <controllers/AllBlogPostController.h>
#include <views/TagPartial.h>

BlogPostPartial::BlogPostPartial(DomNode node, Session* session)
: Partial(node)
, _session(session)
, _blogPost(nullptr)
, _id(0) {
	addTransform("id", [this](DomNode& node) {
		node.inner() = QString::number(_id);
	});
	
	addTransform("title", [this](DomNode& node) {
		node.inner() = _blogPost->title();
	});
	
	addTransform("text", [this](DomNode& node) {
		node.inner() = _blogPost->text();
	});
	
	addTransform("shorttext", [this](DomNode& node) {
		node.inner() = _blogPost->text();
	});
	
	addTransform("showlink", [this](DomNode& node) {
		if (_session->isLoggedIn() && _blogPost->author() == _session->author()) {
			node("href") = url(&BlogPostController::show, { { "id", _id } });
		} else {
			node("href") = url(&AllBlogPostController::show, { { "id", _id } });
		}
	});
	
	addTransform("editlink", [this](DomNode& node) {
		node("href") = url(&BlogPostController::edit, { { "id", _id } });
	});
	
	addTransform("deletelink", [this](DomNode& node) {
		node("href") = url(&BlogPostController::remove, { { "id", _id } });
	});
	
	addTransform("tags", &BlogPostPartial::tags);
}

void BlogPostPartial::setData(BlogPost* blogPost, unsigned id) {
	_blogPost = blogPost;
	_id = id;
}

void BlogPostPartial::tags(DomNode& node) const {
	TagPartial tagPartial(node.children()[0].remove());
	
	//~ if (_blogPost->getTags().size()) {
		//~ for (Tag* tag : _blogPost->getTags()) {
			//~ tagPartial.setData(tag);
			//~ node << tagPartial;
			//~ node << " ";
		//~ }
	//~ } else {
		node.inner() = " ";
	//~ }
}