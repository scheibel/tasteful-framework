#include <models/BlogPost.h>

BlogPost::BlogPost() {
	
}

BlogPost::~BlogPost() {
	
}

Author* BlogPost::getAuthor() {
	return author;
}

void BlogPost::setAuthor(Author* newAuthor) {
	author = newAuthor;
}

QString BlogPost::getTitle() {
	return title;
}

void BlogPost::setTitle(QString newTitle) {
	title = newTitle;
}

QString BlogPost::getText() {
	return text;
}

void BlogPost::setText(QString newText) {
	text = newText;
}

QList<Tag*> BlogPost::getTags() {
	return tags;
}

void BlogPost::setTags(QList<Tag*> newTags) {
	tags = newTags;
}

