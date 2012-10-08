#include <controllers/AllBlogPostController>

#include <views/AllBlogPostList>
#include <datamappers/BlogPostMapper>

AllBlogPostController::AllBlogPostController() : BlogController() {
	
}

void AllBlogPostController::index() {
	QList<BlogPost*> blogPosts = BlogPostMapper::instance().find("1");
	QHash<BlogPostMapper::Identity, BlogPost*> blogPostHash;
	
	for (BlogPost* blogPost : blogPosts) {
		blogPostHash.insert(BlogPostMapper::instance().idOf(blogPost), blogPost);
	}
	
	render(AllBlogPostList(blogPostHash));
}

void AllBlogPostController::show() {
	
}