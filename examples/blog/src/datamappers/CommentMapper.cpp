#include <datamappers/CommentMapper>

CommentMapper::CommentMapper() {
	
}

CommentMapper::~CommentMapper() {
	
}

void CommentMapper::buildFromRecord(Comment* model, const QVariantMap& record) const {
	model->setEmail(record["email"].toString());
	model->setText(record["text"].toString());
}

void CommentMapper::buildRecordFrom(Comment* model, QVariantMap& record) const {
	record.insert("email", model->getEmail());
	record.insert("text", model->getText());
}

QList<QString> CommentMapper::selectVariables() const {
	return { "email", "text" };
}

QString CommentMapper::identityFieldName() const {
	return "id";
}

QString CommentMapper::table() const {
	return "comments";
}

QString CommentMapper::databaseId() const {
	return "blog";
}
