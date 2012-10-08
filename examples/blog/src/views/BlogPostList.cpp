#include <views/BlogPostList>

#include <views/BlogPostView>

BlogPostList::BlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
}

void BlogPostList::blogPostTable(DomNode& node) const {
	BlogPostView blogPostView(node["tr"][1].remove());
	
	for (unsigned id : blogPosts.keys()) {
		blogPostView.reset(blogPosts.value(id), id);
		node << blogPostView.toNode();
	}
}
