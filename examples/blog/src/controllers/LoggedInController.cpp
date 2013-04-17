#include <controllers/LoggedInController.h>

#include <RedirectException>
#include <controllers/HomeController.h>

LoggedInController::LoggedInController() : BlogController() {
}

bool LoggedInController::isAuthorized() const {
	return (bool)getSession()->author;
}

void LoggedInController::unauthorized()
{
	throw RedirectException(url(&HomeController::index));
}
