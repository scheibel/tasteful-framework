#include <views/AllBlogPostList>
#include <views/BlogPostSummary>
#include <QTextStream>

AllBlogPostList::AllBlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogpostlist.html");
}
