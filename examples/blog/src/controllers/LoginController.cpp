#include <controllers/LoginController.h>

#include <controllers/HomeController.h>
#include <views/Login.h>
#include <datamappers/AuthorMapper.h>

LoginController::LoginController() : BlogController() {
}

void LoginController::index() {
	render(Login(getSession()));
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
	
	render(Login(getSession(), email, true));
}

void LoginController::logout() {
	getSession()->author = nullptr;
	
	redirect(url(&HomeController::index));
}