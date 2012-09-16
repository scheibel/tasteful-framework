#include <views/AllBlogPostList>
#include <views/BlogPostSummary>
#include <QTextStream>

AllBlogPostList::AllBlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogpostlist.html");
	
	addTransform("blogpostlist", &AllBlogPostList::blogPostList);
}

QDomNode AllBlogPostList::blogPostList(QDomNode node) {
	removeChildren(node);
	
	for (BlogPost* blogPost : blogPosts) {
		appendChildren(node, BlogPostSummary(blogPost).contentNode());
	}
	
	return node;
}