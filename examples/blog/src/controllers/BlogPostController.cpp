#include <controllers/BlogPostController>

#include <views/BlogPostList>
#include <views/BlogPostShow>
#include <views/BlogPostEdit>
#include <datamappers/AuthorMapper>

BlogPostController::BlogPostController() {
	
}

QList<BlogPost*> BlogPostController::findAll() {
	return getDataMapper().find("author = " + QString::number(AuthorMapper::instance().idOf(getSession()->author)));
}

void BlogPostController::beforeSave(BlogPost* blogPost) {
	blogPost->setAuthor(getSession()->author);
}

void BlogPostController::renderListViewFor(QHash<unsigned, BlogPost*> blogPosts) {
	render(BlogPostList(getSession(), blogPosts));
}

void BlogPostController::renderShowViewFor(BlogPost* blogPost, unsigned id) {
	render(BlogPostShow(getSession(), blogPost, id));
}

void BlogPostController::renderEditViewFor(BlogPost* blogPost, unsigned id) {
	render(BlogPostEdit(getSession(), blogPost, id));
}
