#pragma once

#include <models/BlogPost.h>
#include <views/BlogView.h>

class BlogPostEdit : public BlogView {
	public:
		BlogPostEdit(Session* session, BlogPost* blogPost, unsigned id);
		
		void blogEditForm(DomNode& node) const;
		void blogPostId(DomNode& node) const;
		void blogPostTitle(DomNode& node) const;
		void blogPostText(DomNode& node) const;
		void saveButtonText(DomNode& node) const;
		void backUrl(DomNode& node) const;
		void tagList(DomNode& node) const;
	private:
		BlogPost* blogPost;
		unsigned id;
};
