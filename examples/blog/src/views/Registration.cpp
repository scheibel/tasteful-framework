#include <views/Registration>
#include <controllers/RegisterController>

Registration::Registration(QString email, QString error) : BlogView(), email(email), error(error) {
	setFilename("registration.html");
	
	addTransform("registrationform", &Registration::registrationForm);
	addTransform("errormessage", &Registration::errorMessage);
	addTransform("emailvalue", &Registration::emailValue);
}

void Registration::registrationForm(DomNode& node) {
	node("method") = "POST";
	node("url") = url(&RegisterController::signup);
}

void Registration::errorMessage(DomNode& node) {
	if (!error.isNull()) {
		node << error;
	}
}

void Registration::emailValue(DomNode& node) {
	node("value") = email;
}
