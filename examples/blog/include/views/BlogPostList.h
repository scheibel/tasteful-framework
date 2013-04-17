#pragma once

#include <models/BlogPost.h>
#include <views/BlogView.h>

#include <QHash>

class BlogPostList : public BlogView {
	public:
		BlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts);
		
		void blogPostTable(DomNode& node) const;
		void newLink(DomNode& node) const;
	private:
		QHash<unsigned, BlogPost*> blogPosts;
};
