#include <models/Comment>

Comment::Comment() {
	
}

Comment::~Comment() {
	
}

QString Comment::getEmail() {
	return email;
}

void Comment::setEmail(QString newEmail) {
	email = newEmail;
}

QString Comment::getText() {
	return text;
}

void Comment::setText(QString newText) {
	text = newText;
}

