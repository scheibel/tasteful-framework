#pragma once

#include <models/Author.h>
#include <models/Tag.h>

#include <QString>
#include <QList>

class BlogPost {
	public:
		BlogPost();
		~BlogPost();
		
		Author* getAuthor();
		void setAuthor(Author* newAuthor);
		QString getTitle();
		void setTitle(QString newTitle);
		QString getText();
		void setText(QString newText);
		QList<Tag*> getTags();
		void setTags(QList<Tag*> newTags);
	private:
		Author* author;
		QString title;
		QString text;
		QList<Tag*> tags;
};
