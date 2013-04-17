#include <datamappers/TagMapper.h>

TagMapper::TagMapper() {
	
}

TagMapper::~TagMapper() {
	
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

Tag* TagMapper::obtainByName(const QString& name) {
	Tag* tag = getBy("name = '" + name + "'");
	
	if (!tag) {
		tag = newModel();
		tag->setName(name);
		save(tag);
	}
	
	return tag;
}
