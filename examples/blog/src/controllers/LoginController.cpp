#include <controllers/LoginController>

#include <controllers/HomeController>
#include <views/Login>
#include <datamappers/AuthorMapper>

LoginController::LoginController() : BlogController() {
	
}

void LoginController::index() {
	render(new Login());
}

void LoginController::login() {
	QString email = parameters["email"].value<QString>();
	QString password = parameters["password"].value<QString>();
	
	Author* author = AuthorMapper::instance().getBy("email = '" + email + "'");
	
	if (author) {
		if (author->validatePassword(password)) {
			getSession()->author = author;
			
			redirect(url(&HomeController::index));
		}
	}
	
	render(new Login(email, true));
}

void LoginController::logout() {
	getSession()->author = nullptr;
	
	redirect(url(&HomeController::index));
}