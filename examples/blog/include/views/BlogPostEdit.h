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
#include <views/BlogView.h>

class BlogPostEdit : public BlogView {
public:
	BlogPostEdit(Session* session, BlogPost* blogPost, unsigned id);
	
	void blogEditForm(DomNode& node) const;
	void blogPostId(DomNode& node) const;
	void blogPostTitle(DomNode& node) const;
	void blogPostText(DomNode& node) const;
	void saveButtonText(DomNode& node) const;
	void backUrl(DomNode& node) const;
	void tagList(DomNode& node) const;
private:
	BlogPost* blogPost;
	unsigned id;
};
