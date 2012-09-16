#include <models/Author>

#include <QCryptographicHash>

Author::Author() {
	
}

Author::~Author() {
	
}

QString Author::getEmail() {
	return email;
}

void Author::setEmail(QString newEmail) {
	email = newEmail;
}

QString Author::getPassword() {
	return password;
}

void Author::setPassword(QString newPassword) {
	password = newPassword;
}

QString Author::getSalt() {
	return salt;
}

void Author::setSalt(QString newSalt) {
	salt = newSalt;
}

bool Author::validatePassword(QString pass) {
	return password == calculateHash(pass, salt);
}

void Author::setNewSalt(QString newSalt) {
	setSalt(calculateHash(newSalt, "Blog"));
}

void Author::setNewPassword(QString newPassword) {
	setPassword(calculateHash(newPassword, salt));
}

QString Author::calculateHash(QString value, QString salt) {
	return QCryptographicHash::hash((salt + value).toUtf8(), QCryptographicHash::Sha1).toHex();
}