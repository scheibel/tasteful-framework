#include <session/Session>

Session::Session() : AbstractSession(), author(nullptr) {
	
}

bool Session::isLoggedIn() {
	return (bool)author;
}