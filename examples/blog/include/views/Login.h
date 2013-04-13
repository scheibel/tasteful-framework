#pragma once

#include <views/BlogView>
#include <QString>

class Login : public BlogView {
	public:
		Login(Session* session, QString email = "", bool loginAttempt = false);
		
		void loginForm(DomNode& node) const;
		void errorMessage(DomNode& node) const;
		void emailValue(DomNode& node) const;
	private:
		bool loginAttempt;
		QString email;
};
