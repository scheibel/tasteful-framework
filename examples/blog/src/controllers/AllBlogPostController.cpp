#include <controllers/AllBlogPostController>

#include <views/AllBlogPostList>
#include <datamappers/BlogPostMapper>

AllBlogPostController::AllBlogPostController() : BlogController() {
	
}

void AllBlogPostController::index() {
	render(AllBlogPostList(getSession(), BlogPostMapper::instance().find("1 ORDER BY id DESC")));
}

void AllBlogPostController::show() {
	
}
