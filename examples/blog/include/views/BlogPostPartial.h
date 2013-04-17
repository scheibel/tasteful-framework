#pragma once

#include <models/BlogPost.h>
#include <session/Session.h>

#include <Partial>

class BlogPostPartial : public Partial {
	public:
		BlogPostPartial(DomNode node, Session* session);
	
		void setData(BlogPost* blogPost, unsigned blogPostId);
		
		void id(DomNode& node) const;
		void title(DomNode& node) const;
		void text(DomNode& node) const;
		void shortText(DomNode& node) const;
		void showLink(DomNode& node) const;
		void editLink(DomNode& node) const;
		void deleteLink(DomNode& node) const;
		void tags(DomNode& node) const;
	private:
		Session* session;
		BlogPost* blogPost;
		unsigned blogPostId;
};
