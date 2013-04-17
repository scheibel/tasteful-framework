#include <views/Registration.h>

#include <controllers/RegisterController.h>

Registration::Registration(Session* session, const QString& email, const QString& error)
: BlogView(session)
, email(email)
, error(error) {
	setFilename("registration.html");
	
	addTransform("registrationform", &Registration::registrationForm);
	addTransform("errormessage", &Registration::errorMessage);
	addTransform("emailvalue", &Registration::emailValue);
}

void Registration::registrationForm(DomNode& node) const {
	node("method") = "POST";
	node("url") = url(&RegisterController::signup);
}

void Registration::errorMessage(DomNode& node) const {
	if (!error.isNull()) {
		node << error;
	}
}

void Registration::emailValue(DomNode& node) const {
	node("value") = email;
}
