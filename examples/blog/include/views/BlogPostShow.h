#pragma once

#include <views/BlogView>
#include <models/BlogPost>

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
