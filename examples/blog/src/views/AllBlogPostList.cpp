#include <views/AllBlogPostList>

#include <views/BlogPostView>

AllBlogPostList::AllBlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
	setFilename("blogpostlist.html");
	
	addTransform("blogpostlist", &AllBlogPostList::blogPostList);
}

void AllBlogPostList::blogPostList(DomNode& node) const {
	if (blogPosts.empty()) {
		node.remove();
		return;
	}
	
	DomNode blogPostNode = node.firstChild().remove();
	
	for (unsigned index : blogPosts.keys()) {
		//node.transferChildrenFrom(DomNode(BlogPostView(blogPostNode.clone(), blogPosts.value(index), index).contentNode()));
	}
}