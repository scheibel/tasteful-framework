#pragma once

#include <views/BlogView>
#include <QString>

class Registration : public BlogView {
	public:
		Registration(Session* session, QString email = "", QString error = "");
		
		void registrationForm(DomNode& node) const;
		void errorMessage(DomNode& node) const;
		void emailValue(DomNode& node) const;
	private:
		QString email;
		QString error;
};