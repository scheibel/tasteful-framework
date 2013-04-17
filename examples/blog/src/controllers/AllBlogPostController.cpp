#include <controllers/AllBlogPostController.h>

#include <views/AllBlogPostList.h>
#include <views/BlogPostShow.h>
#include <datamappers/BlogPostMapper.h>

AllBlogPostController::AllBlogPostController() : BlogController() {
	
}

void AllBlogPostController::index() {
	render(AllBlogPostList(getSession(), BlogPostMapper::instance().find("1 ORDER BY id DESC")));
}

void AllBlogPostController::show() {
	BlogPostMapper::Identity id = parameters["id"].value<BlogPostMapper::Identity>();
	
	render(BlogPostShow(getSession(), BlogPostMapper::instance().get(id), id));
}
