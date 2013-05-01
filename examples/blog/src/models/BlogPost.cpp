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

#include <models/BlogPost.h>

BlogPost::BlogPost() {
}

Author* BlogPost::getAuthor() const {
	return _author;
}

void BlogPost::setAuthor(Author* author) {
	_author = author;
}

const QString& BlogPost::getTitle() const {
	return _title;
}

void BlogPost::setTitle(const QString& title) {
	_title = title;
}

const QString& BlogPost::getText() const {
	return _text;
}

void BlogPost::setText(const QString& text) {
	_text = text;
}

const QList<Tag*>& BlogPost::getTags() const {
	return _tags;
}

void BlogPost::setTags(const QList<Tag*>& tags) {
	_tags = tags;
}
