#pragma once

#include <views/BlogView.h>

#include <QString>

class Registration : public BlogView {
public:
	Registration(Session* session, const QString& email = "", const QString& error = "");
	
	void registrationForm(DomNode& node) const;
	void errorMessage(DomNode& node) const;
	void emailValue(DomNode& node) const;
private:
	QString email;
	QString error;
};
