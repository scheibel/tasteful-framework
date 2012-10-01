#include <views/Home>

#include <views/BlogPostSummary>

Home::Home(QList<BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("home.html");
	
	addTransform("recentposts", &Home::recentPosts);
	addTransform("numberofrecentposts", &Home::numberOfRecentPosts);
}

void Home::recentPosts(DomNode& node) {
	node.removeChildren();
	
	for (BlogPost* blogPost : blogPosts) {
		node.importChildrenFrom(BlogPostSummary(blogPost).contentNode());
	}
}

void Home::numberOfRecentPosts(DomNode& node) {
	node.replaceChildren(QString::number(blogPosts.size()));
}
