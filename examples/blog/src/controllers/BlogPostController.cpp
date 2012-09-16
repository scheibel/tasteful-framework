#include <controllers/BlogPostController>

#include <views/BlogPostList>
#include <views/BlogPostShow>
#include <views/BlogPostEdit>
#include <datamappers/AuthorMapper>

BlogPostController::BlogPostController() {
	
}

QList<BlogPost*> BlogPostController::findAll() const {
	return getDataMapper().find("author = " + QString::number(AuthorMapper::instance().idOf(getSession()->author)));
}

View* BlogPostController::listViewFor(QHash<unsigned, BlogPost*> blogPosts) {
	return new BlogPostList(blogPosts);
}

View* BlogPostController::showViewFor(BlogPost* blogPost, unsigned id) {
	return new BlogPostShow(blogPost, id);
}

View* BlogPostController::editViewFor(BlogPost* blogPost, unsigned id) {
	return new BlogPostEdit(blogPost, id);
}
