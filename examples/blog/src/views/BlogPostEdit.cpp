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

#include <views/BlogPostEdit.h>

#include <controllers/BlogPostController.h>

BlogPostEdit::BlogPostEdit(Session* session, BlogPost* blogPost, unsigned id)
: BlogView(session)
, blogPost(blogPost)
, id(id) {
	setFilename("blogpostedit.html");
	
	addTransform("blogeditform", &BlogPostEdit::blogEditForm);
	addTransform("blogpostid", &BlogPostEdit::blogPostId);
	addTransform("blogposttitle", &BlogPostEdit::blogPostTitle);
	addTransform("blogposttext", &BlogPostEdit::blogPostText);
	addTransform("savebuttontext", &BlogPostEdit::saveButtonText);
	addTransform("backurl", &BlogPostEdit::backUrl);
	addTransform("blogposttags", &BlogPostEdit::tagList);
}

void BlogPostEdit::backUrl(DomNode& node) const {
	node("href") = url(&BlogPostController::index);
}

void BlogPostEdit::blogEditForm(DomNode& node) const {
	node("action") = url(&BlogPostController::save);
}

void BlogPostEdit::blogPostId(DomNode& node) const {
	node("value") = id;
}

void BlogPostEdit::blogPostTitle(DomNode& node) const {
	if (blogPost) {
		node("value") = blogPost->getTitle();
	} else {
		node("placeholder") = "Insert title here";
	}
}

void BlogPostEdit::blogPostText(DomNode& node) const {
	if (blogPost) {
		node.inner() = blogPost->getText();
	} else {
		node.inner() = " ";
	}
}

void BlogPostEdit::saveButtonText(DomNode& node) const {
	node("value") = (id == 0) ? "Create" : "Save";
}

void BlogPostEdit::tagList(DomNode& node) const
{
	if (blogPost) {
		QList<Tag*> tags = blogPost->getTags();
		QStringList tagNames;
		
		for (Tag* tag : tags) {
			tagNames << tag->getName();
		}
		
		node("value") = tagNames.join(" ");
	} else {
		node.inner() = "";
	}
}