#include <views/Home.h>

#include <datamappers/BlogPostMapper.h>
#include <views/BlogPostPartial.h>

Home::Home(Session* session, const QList<BlogPost*>& blogPosts)
: BlogView(session)
, blogPosts(blogPosts) {
	setFilename("home.html");
	
	addTransform("recentposts", &Home::recentPosts);
}

void Home::recentPosts(DomNode& node) const {
	if (blogPosts.empty()) {
		node.remove();
		return;
	}
	
	BlogPostPartial blogPostPartial(node.firstChild().remove(), session);
	
	for (BlogPost* blogPost : blogPosts) {
		blogPostPartial.setData(blogPost, BlogPostMapper::instance().idOf(blogPost));
		node << blogPostPartial;
	}
}
