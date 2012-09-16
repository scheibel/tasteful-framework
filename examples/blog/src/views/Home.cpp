#include <views/Home>

#include <views/BlogPostSummary>

Home::Home(QList<BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("home.html");
	
	addTransform("recentposts", &Home::recentPosts);
	addTransform("numberofrecentposts", &Home::numberOfRecentPosts);
}

QDomNode Home::recentPosts(QDomNode node) {
	removeChildren(node);
	
	for (BlogPost* blogPost : blogPosts) {
		appendChildren(node, BlogPostSummary(blogPost).contentNode());
	}
	
	return node;
}

QDomNode Home::numberOfRecentPosts(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(QString::number(blogPosts.size())));
	
	return node;
}
