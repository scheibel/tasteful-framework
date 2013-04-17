#pragma once

#include <models/BlogPost.h>
#include <views/BlogView.h>

#include <QHash>

class AllBlogPostList : public BlogView {
	public:
		AllBlogPostList(Session* session, QList<BlogPost*> blogPosts);
		
		void blogPostList(DomNode& node) const;
	private:
		QList<BlogPost*> blogPosts;
};
