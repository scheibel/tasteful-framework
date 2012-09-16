#include <controllers/LoggedInController>

LoggedInController::LoggedInController() : BlogController() {
	
}

bool LoggedInController::isAuthorized() {
	return (bool)getSession()->author;
}