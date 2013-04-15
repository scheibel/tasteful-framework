#include <controllers/HomeController>

#include <views/Home>
#include <datamappers/BlogPostMapper>

HomeController::HomeController() : BlogController() {
	
}

void HomeController::index() {
	render(Home(getSession(), BlogPostMapper::instance().find("1 LIMIT 5")));
}
