#include <controllers/BlogController>

BlogController::BlogController() : RestrictedController() {
	
}

bool BlogController::isAuthorized() const {
	return true;
}

Session* BlogController::getSession() const {
	return Controller::getSession<Session>();
}