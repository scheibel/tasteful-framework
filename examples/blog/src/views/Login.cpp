#include <views/Login>
#include <controllers/LoginController>

Login::Login(QString email, bool loginAttempt) : BlogView(), email(email), loginAttempt(loginAttempt) {
	setFilename("login.html");
	
	addTransform("loginform", &Login::loginForm);
	addTransform("errormessage", &Login::errorMessage);
	addTransform("emailvalue", &Login::emailValue);
}

void Login::loginForm(DomNode& node) {
	node.attribute("method") = "POST";
	node.attribute("url") = url(&LoginController::login);
}

void Login::errorMessage(DomNode& node) {
	if (loginAttempt) {
		node.appendChild("Failed to log in.");
	}
}

void Login::emailValue(DomNode& node) {
	node.attribute("value") = email;
}
