#include <models/Author.h>

#include <QCryptographicHash>

Author::Author() {
}

const QString& Author::getEmail() const {
	return email;
}

void Author::setEmail(const QString& newEmail) {
	email = newEmail;
}

const QString& Author::getPassword() const {
	return password;
}

void Author::setPassword(const QString& newPassword) {
	password = newPassword;
}

const QString& Author::getSalt() const {
	return salt;
}

void Author::setSalt(const QString& newSalt) {
	salt = newSalt;
}

bool Author::validatePassword(const QString& pass) {
	return password == calculateHash(pass, salt);
}

void Author::setNewSalt(const QString& newSalt) {
	setSalt(calculateHash(newSalt, "Blog"));
}

void Author::setNewPassword(const QString& newPassword) {
	setPassword(calculateHash(newPassword, salt));
}

QString Author::calculateHash(const QString& value, const QString& salt) {
	return QCryptographicHash::hash((salt + value).toUtf8(), QCryptographicHash::Sha1).toHex();
}
