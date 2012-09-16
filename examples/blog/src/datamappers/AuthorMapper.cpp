#include <datamappers/AuthorMapper>

AuthorMapper::AuthorMapper() {
	
}

AuthorMapper::~AuthorMapper() {
	
}

Author* AuthorMapper::newModel() const {
	return new Author();
}

void AuthorMapper::buildFromRecord(Author* model, const QVariantMap& record) const {
	model->setEmail(record["email"].toString());
	model->setPassword(record["password"].toString());
	model->setSalt(record["salt"].toString());
}

void AuthorMapper::buildRecordFrom(Author* model, QVariantMap& record) const {
	record.insert("email", model->getEmail());
	record.insert("password", model->getPassword());
	record.insert("salt", model->getSalt());
}

QList<QString> AuthorMapper::selectVariables() const {
	return { "email", "password", "salt" };
}

QString AuthorMapper::identityFieldName() const {
	return "id";
}

QString AuthorMapper::table() const {
	return "authors";
}

QString AuthorMapper::databaseId() const {
	return "blog";
}
