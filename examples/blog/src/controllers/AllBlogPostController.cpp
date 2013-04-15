#include <controllers/AllBlogPostController>

#include <views/AllBlogPostList>
#include <views/BlogPostShow>
#include <datamappers/BlogPostMapper>

AllBlogPostController::AllBlogPostController() : BlogController() {
	
}

void AllBlogPostController::index() {
	render(AllBlogPostList(getSession(), BlogPostMapper::instance().find("1 ORDER BY id DESC")));
}

void AllBlogPostController::show() {
	BlogPostMapper::Identity id = parameters["id"].value<BlogPostMapper::Identity>();
	
	render(BlogPostShow(getSession(), BlogPostMapper::instance().get(id), id));
}
