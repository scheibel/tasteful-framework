#pragma once

#include <views/BlogView>
#include <models/BlogPost>
#include <QHash>

class AllBlogPostList : public BlogView {
	public:
		AllBlogPostList(Session* session, QList<BlogPost*> blogPosts);
		
		void blogPostList(DomNode& node) const;
	private:
		QList<BlogPost*> blogPosts;
};
