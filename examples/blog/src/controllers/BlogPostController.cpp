#include <controllers/BlogPostController>

#include <views/BlogPostList>
#include <views/BlogPostShow>
#include <views/BlogPostEdit>
#include <datamappers/AuthorMapper>
#include <datamappers/TagMapper>

BlogPostController::BlogPostController() {

}

QList<BlogPost*> BlogPostController::findAll() {
	return getDataMapper().find("author = " + QString::number(AuthorMapper::instance().idOf(getSession()->author)));
}

void BlogPostController::beforeSave(BlogPost* blogPost) {
	QString tags = parameters["tags"].value<QString>();
	
	QList<Tag*> newTags;
	if (!tags.isNull() && !tags.isEmpty()) {
		for (const QString& tagName : tags.split(" ")) {
			newTags << TagMapper::instance().obtainByName(tagName);
		}
	}
	blogPost->setTags(newTags);
	
	blogPost->setAuthor(getSession()->author);
}

void BlogPostController::renderListViewFor(const QHash<unsigned, BlogPost*>& blogPosts) {
	render(BlogPostList(getSession(), blogPosts));
}

void BlogPostController::renderShowViewFor(BlogPost* blogPost, unsigned id) {
	render(BlogPostShow(getSession(), blogPost, id));
}

void BlogPostController::renderEditViewFor(BlogPost* blogPost, unsigned id) {
	render(BlogPostEdit(getSession(), blogPost, id));
}
