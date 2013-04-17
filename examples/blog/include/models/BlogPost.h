#pragma once

#include <models/Author.h>
#include <models/Tag.h>

#include <QString>
#include <QList>

class BlogPost {
public:
	BlogPost();
	
	Author* getAuthor() const;
	void setAuthor(Author* newAuthor);
	
	const QString& getTitle() const;
	void setTitle(const QString& newTitle);
	
	const QString& getText() const;
	void setText(const QString& newText);
	
	const QList<Tag*>& getTags() const;
	void setTags(const QList<Tag*>& newTags);
private:
	Author* author;
	QString title;
	QString text;
	QList<Tag*> tags;
};
