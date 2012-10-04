#include <views/AllBlogPostList>

#include <views/BlogPostView>

AllBlogPostList::AllBlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogpostlist.html");
	
	addTransform("blogpostlist", &AllBlogPostList::blogPostList);
}

void AllBlogPostList::blogPostList(DomNode& node) {
	if (blogPosts.empty()) {
		node.remove();
		return;
	}
	
	DomNode blogPostNode = node.child(0).remove();
	
	for (unsigned index : blogPosts.keys()) {
		node.transferChildrenFrom(DomNode(BlogPostView(blogPostNode, blogPosts.value(index), index).contentNode()));
	}
}