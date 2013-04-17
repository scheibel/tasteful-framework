#include <controllers/RegisterController.h>

#include <controllers/HomeController.h>
#include <views/Registration.h>
#include <datamappers/AuthorMapper.h>

RegisterController::RegisterController() : BlogController() {
	
}

void RegisterController::index() {
	render(Registration(getSession()));
}

void RegisterController::signup() {
	QString email = parameters["email"].value<QString>();
	QString password = parameters["password"].value<QString>();
	QString password2 = parameters["password2"].value<QString>();
	
	if (AuthorMapper::instance().getBy("email = '" + email + "'")) {
		render(Registration(getSession(), email, "An account with this email already exists"));
	} else {
		if (password != password2) {
			render(Registration(getSession(), email, "The password confirmation doesn't match with the password"));
		} else {
			Author* author = new Author();
			
			author->setEmail(email);
			author->setNewSalt(email);
			author->setNewPassword(password);
			
			AuthorMapper::instance().save(author);
			
			getSession()->author = author;
			
			redirect(url(&HomeController::index));
		}
	}
}
