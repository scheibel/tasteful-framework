#include <controllers/LoggedInController>

#include <RedirectException>
#include <controllers/HomeController>

LoggedInController::LoggedInController() : BlogController() {
	
}

bool LoggedInController::isAuthorized() const {
	return (bool)getSession()->author;
}

void LoggedInController::unauthorized()
{
	throw RedirectException(url(&HomeController::index));
}
