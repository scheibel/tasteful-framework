#include <views/Home>

#include <views/BlogPostSummary>

Home::Home(QList<BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("home.html");
	
	addTransform("recentposts", &Home::recentPosts);
	addTransform("numberofrecentposts", &Home::numberOfRecentPosts);
}

void Home::recentPosts(DomNode& node) {
	if (blogPosts.empty()) {
		node.remove();
		return;
	}
	
	node.removeChildren();
	
	for (BlogPost* blogPost : blogPosts) {
		node.transferChildrenFrom(DomNode(BlogPostSummary(blogPost).contentNode()));
	}
}

void Home::numberOfRecentPosts(DomNode& node) {
	node.inner() = QString::number(blogPosts.size());
}
