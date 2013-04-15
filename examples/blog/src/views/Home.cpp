#include <views/Home>

#include <views/BlogPostPartial>
#include <datamappers/BlogPostMapper>

Home::Home(Session* session, QList<BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
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
