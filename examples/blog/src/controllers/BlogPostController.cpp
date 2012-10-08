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

const View& BlogPostController::listViewFor(QHash<unsigned, BlogPost*> blogPosts) {
	return BlogPostList(blogPosts);
}

const View& BlogPostController::showViewFor(BlogPost* blogPost, unsigned id) {
	return BlogPostShow(blogPost, id);
}

const View& BlogPostController::editViewFor(BlogPost* blogPost, unsigned id) {
	return BlogPostEdit(blogPost, id);
}
