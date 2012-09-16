#include <views/Login>
#include <controllers/LoginController>

Login::Login(QString email, bool loginAttempt) : BlogView(), email(email), loginAttempt(loginAttempt) {
	setFilename("login.html");
	
	addTransform("loginform", &Login::loginForm);
	addTransform("errormessage", &Login::errorMessage);
	addTransform("emailvalue", &Login::emailValue);
	//addTransform("passwordvalue", &Login::passwordValue);
}

QDomNode Login::loginForm(QDomNode node) {
	node.toElement().setAttribute("method", "POST");
	node.toElement().setAttribute("url", url(&LoginController::login));
	
	return node;
}

QDomNode Login::errorMessage(QDomNode node) {
	if (loginAttempt) {
		node.appendChild($("Failed to log in."));
	}
	
	return node;
}

QDomNode Login::emailValue(QDomNode node) {
	node.toElement().setAttribute("value", email);
	
	return node;
}

/*
QDomNode Registration::passwordValue(QDomNode node) {
	return node;
}
*/