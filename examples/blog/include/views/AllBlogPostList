#pragma once

#include <views/BlogView>
#include <models/BlogPost>
#include <QHash>

class AllBlogPostList : public BlogView {
	public:
		AllBlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts);
		
		void blogPostList(DomNode& node) const;
	private:
		QHash<unsigned, BlogPost*> blogPosts;
};
