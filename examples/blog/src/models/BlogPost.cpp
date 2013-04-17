#include <models/BlogPost.h>

BlogPost::BlogPost() {
}

Author* BlogPost::getAuthor() const {
	return author;
}

void BlogPost::setAuthor(Author* newAuthor) {
	author = newAuthor;
}

const QString& BlogPost::getTitle() const {
	return title;
}

void BlogPost::setTitle(const QString& newTitle) {
	title = newTitle;
}

const QString& BlogPost::getText() const {
	return text;
}

void BlogPost::setText(const QString& newText) {
	text = newText;
}

const QList<Tag*>& BlogPost::getTags() const {
	return tags;
}

void BlogPost::setTags(const QList<Tag*>& newTags) {
	tags = newTags;
}
