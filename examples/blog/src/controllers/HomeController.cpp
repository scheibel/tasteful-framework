#include <controllers/HomeController>

#include <views/Home>
#include <datamappers/BlogPostMapper>

HomeController::HomeController() : BlogController() {
	
}

void HomeController::index() {
	render(new Home(BlogPostMapper::instance().all()));
}