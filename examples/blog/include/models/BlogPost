#pragma once

#include <QString>
#include <QList>
#include <models/Author>
#include <models/Comment>
#include <models/Tag>

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
		QList<Comment*> getComments();
		void setComments(QList<Comment*> newComments);
		QList<Tag*> getTags();
		void setTags(QList<Tag*> newTags);
	private:
		Author* author;
		QString title;
		QString text;
		QList<Comment*> comments;
		QList<Tag*> tags;
};
