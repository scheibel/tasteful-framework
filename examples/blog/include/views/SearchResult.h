#pragma once

#include <views/BlogView>
#include <models/BlogPost>

class SearchResult : public BlogView {
	public:
		SearchResult(Session* session, QList<BlogPost*> searchResult, const QString& searchString);
		
		void blogPostList(DomNode& node) const;
	private:
		QList<BlogPost*> searchResult;
		QString searchString;
};
