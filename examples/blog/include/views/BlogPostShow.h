#pragma once

#include <models/BlogPost.h>
#include <views/BlogView.h>

class BlogPostShow : public BlogView {
public:
	BlogPostShow(Session* session, BlogPost* blogPost, unsigned id);
	
	void blogPostTitle(DomNode& node) const;
	void blogPostContent(DomNode& node) const;
	void blogPostTags(DomNode& node) const;
private:
	BlogPost* blogPost;
	unsigned id;
};
