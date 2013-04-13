#pragma once

#include <views/BlogView>
#include <models/BlogPost>
#include <QHash>

class BlogPostList : public BlogView {
	public:
		BlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts);
		
		void blogPostTable(DomNode& node) const;
		void newLink(DomNode& node) const;
	private:
		QHash<unsigned, BlogPost*> blogPosts;
};
