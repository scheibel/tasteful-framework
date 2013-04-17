#include <controllers/BlogPostController.h>

#include <views/BlogPostList.h>
#include <views/BlogPostShow.h>
#include <views/BlogPostEdit.h>
#include <datamappers/AuthorMapper.h>
#include <datamappers/TagMapper.h>

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
