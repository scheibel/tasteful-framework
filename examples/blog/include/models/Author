#pragma once

#include <QString>

class Author {
	public:
		Author();
		~Author();
		
		QString getEmail();
		void setEmail(QString newEmail);
		QString getPassword();
		void setPassword(QString newPassword);
		QString getSalt();
		void setSalt(QString newSalt);
		
		bool validatePassword(QString pass);
		void setNewSalt(QString newSalt);
		void setNewPassword(QString newPassword);
	protected:
		QString calculateHash(QString value, QString salt);
	private:
		QString email;
		QString password;
		QString salt;
};
