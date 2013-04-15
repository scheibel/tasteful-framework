#include <views/AllBlogPostList>

#include <views/BlogPostPartial>
#include <datamappers/BlogPostMapper>

AllBlogPostList::AllBlogPostList(Session* session, QList<BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
	setFilename("blogpostlist.html");
	
	addTransform("blogpostlist", &AllBlogPostList::blogPostList);
}

void AllBlogPostList::blogPostList(DomNode& node) const {
	if (blogPosts.empty()) {
		node.remove();
		return;
	}
	
	BlogPostPartial blogPostPartial(node.firstChild().remove());
	
	for (BlogPost* blogPost : blogPosts) {
		blogPostPartial.setData(blogPost, BlogPostMapper::instance().idOf(blogPost));
		node << blogPostPartial;
	}
}