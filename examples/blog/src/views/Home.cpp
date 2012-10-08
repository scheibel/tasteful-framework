#include <views/Home>

#include <views/BlogPostView>
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
	
	BlogPostView blogPostView(node.firstChild().remove());
	
	for (BlogPost* blogPost : blogPosts) {
		blogPostView.reset(blogPost, BlogPostMapper::instance().idOf(blogPost));
		node << blogPostView.toNode();
	}
}
