#include <session/Session.h>

Session::Session()
: AbstractSession()
, author(nullptr) {
}

bool Session::isLoggedIn() {
	return (bool)author;
}
