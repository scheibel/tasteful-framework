#include <controllers/HomeController.h>

#include <views/Home.h>
#include <datamappers/BlogPostMapper.h>

HomeController::HomeController() : BlogController() {
}

void HomeController::index() {
	render(Home(getSession(), BlogPostMapper::instance().find("1 ORDER BY id DESC LIMIT 5")));
}
