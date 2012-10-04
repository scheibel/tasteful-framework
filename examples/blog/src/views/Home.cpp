#include <views/Home>

#include <views/BlogPostView>
#include <datamappers/BlogPostMapper>

Home::Home(QList<BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("home.html");
	
	addTransform("recentposts", &Home::recentPosts);
}

void Home::recentPosts(DomNode& node) {
	if (blogPosts.empty()) {
		node.remove();
		return;
	}
	
	DomNode blogPostNode = node.child(0).remove();
	
	for (BlogPost* blogPost : blogPosts) {
		node.transferChildrenFrom(DomNode(BlogPostView(blogPostNode, blogPost, BlogPostMapper::instance().idOf(blogPost)).contentNode()));
	}
}
