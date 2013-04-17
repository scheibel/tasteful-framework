#pragma once

#include <models/BlogPost.h>
#include <views/BlogView.h>

#include <QList>

class AllBlogPostList : public BlogView {
public:
	AllBlogPostList(Session* session, const QList<BlogPost*>& blogPosts);
	
	void blogPostList(DomNode& node) const;
private:
	QList<BlogPost*> blogPosts;
};
