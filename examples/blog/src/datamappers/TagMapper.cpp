#include <datamappers/TagMapper>

TagMapper::TagMapper() {
	
}

TagMapper::~TagMapper() {
	
}

Tag* TagMapper::newModel() const {
	return new Tag();
}

void TagMapper::buildFromRecord(Tag* model, const QVariantMap& record) const {
	model->setName(record["name"].toString());
}

void TagMapper::buildRecordFrom(Tag* model, QVariantMap& record) const {
	record.insert("name", model->getName());
}

QList<QString> TagMapper::selectVariables() const {
	return { "name" };
}

QString TagMapper::identityFieldName() const {
	return "id";
}

QString TagMapper::table() const {
	return "tags";
}

QString TagMapper::databaseId() const {
	return "blog";
}
