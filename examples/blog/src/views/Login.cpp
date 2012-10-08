#include <views/Login>
#include <controllers/LoginController>

Login::Login(Session* session, QString email, bool loginAttempt) : BlogView(session), email(email), loginAttempt(loginAttempt) {
	setFilename("login.html");
	
	addTransform("loginform", &Login::loginForm);
	addTransform("errormessage", &Login::errorMessage);
	addTransform("emailvalue", &Login::emailValue);
}

void Login::loginForm(DomNode& node) const {
	node("method") = "POST";
	node("url") = url(&LoginController::login);
}

void Login::errorMessage(DomNode& node) const {
	if (loginAttempt) {
		node << "Failed to log in.";
	}
}

void Login::emailValue(DomNode& node) const {
	node("value") = email;
}
