#include <datamappers/BlogPostMapper>
#include <datamappers/AuthorMapper>
#include <datamappers/TagMapper>
#include <datamappers/CommentMapper>

BlogPostMapper::BlogPostMapper() {
	
}

BlogPostMapper::~BlogPostMapper() {
	
}

BlogPost* BlogPostMapper::newModel() const {
	return new BlogPost();
}

void BlogPostMapper::buildFromRecord(BlogPost* model, const QVariantMap& record) const {
	model->setAuthor(AuthorMapper::instance().get(record["author"].toUInt()));
	model->setTitle(record["title"].toString());
	model->setText(record["text"].toString());
	model->setComments(CommentMapper::instance().find("blogPost = " + QString::number(record["id"].toUInt())));
	model->setTags(TagMapper::instance().basicFind("SELECT `tags`.id AS id, `tags`.name AS name FROM `tags` LEFT OUTER JOIN `relatedTags` ON `relatedTags`.tag = `tags`.id WHERE `relatedTags`.blogentry = " + QString::number(record["id"].toUInt())));
}

void BlogPostMapper::buildRecordFrom(BlogPost* model, QVariantMap& record) const {
	record.insert("author", AuthorMapper::instance().saveReturningId(model->getAuthor()));
	record.insert("title", model->getTitle());
	record.insert("text", model->getText());
}

QList<QString> BlogPostMapper::selectVariables() const {
	return { "author", "title", "text" };
}

QString BlogPostMapper::identityFieldName() const {
	return "id";
}

QString BlogPostMapper::table() const {
	return "blogentries";
}

void BlogPostMapper::saveRelationsOf(BlogPost* model) {
	// todo: save relation of tags and comments
}

QString BlogPostMapper::databaseId() const {
	return "blog";
}
