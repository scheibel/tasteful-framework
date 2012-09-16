#include <views/Registration>
#include <controllers/RegisterController>

Registration::Registration(QString email, QString error) : BlogView(), email(email), error(error) {
	setFilename("registration.html");
	
	addTransform("registrationform", &Registration::registrationForm);
	addTransform("errormessage", &Registration::errorMessage);
	addTransform("emailvalue", &Registration::emailValue);
	//addTransform("passwordvalue", &Registration::passwordValue);
	//addTransform("password2value", &Registration::password2Value);
}

QDomNode Registration::registrationForm(QDomNode node) {
	node.toElement().setAttribute("method", "POST");
	node.toElement().setAttribute("url", url(&RegisterController::signup));
	
	return node;
}

QDomNode Registration::errorMessage(QDomNode node) {
	if (!error.isNull()) {
		node.appendChild($(error));
	}
	
	return node;
}

QDomNode Registration::emailValue(QDomNode node) {
	node.toElement().setAttribute("value", email);
	
	return node;
}

/*
QDomNode Registration::passwordValue(QDomNode node) {
	return node;
}

QDomNode Registration::password2Value(QDomNode node) {
	return node;
}
*/