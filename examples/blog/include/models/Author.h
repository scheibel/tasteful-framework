#pragma once

#include <QString>

class Author {
public:
	Author();
	
	const QString& getEmail() const;
	void setEmail(const QString& newEmail);
	
	const QString& getPassword() const;
	void setPassword(const QString& newPassword);
	
	const QString& getSalt() const;
	void setSalt(const QString& newSalt);
	
	bool validatePassword(const QString& pass);
	void setNewSalt(const QString& newSalt);
	void setNewPassword(const QString& newPassword);
protected:
	QString calculateHash(const QString& value, const QString& salt);
private:
	QString email;
	QString password;
	QString salt;
};
