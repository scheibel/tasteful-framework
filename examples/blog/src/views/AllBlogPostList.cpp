#include <views/AllBlogPostList.h>

#include <datamappers/BlogPostMapper.h>
#include <views/BlogPostPartial.h>

AllBlogPostList::AllBlogPostList(Session* session, const QList<BlogPost*>& blogPosts)
: BlogView(session)
, blogPosts(blogPosts) {
	setFilename("blogpostlist.html");
	
	addTransform("blogpostlist", &AllBlogPostList::blogPostList);
}

void AllBlogPostList::blogPostList(DomNode& node) const {
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