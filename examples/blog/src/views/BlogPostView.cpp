#include <views/BlogPostView>

#include <controllers/BlogPostController>

BlogPostView::BlogPostView(DomNode node, BlogPost* blogPost, unsigned blogPostId) : BlogView(), blogPost(blogPost), blogPostId(blogPostId) {
	//setNode(node);
	
	addTransform("id", &BlogPostView::id);
	addTransform("title", &BlogPostView::title);
	addTransform("text", &BlogPostView::text);
	addTransform("shorttext", &BlogPostView::shortText);
	addTransform("showlink", &BlogPostView::showLink);
	addTransform("editlink", &BlogPostView::editLink);
	addTransform("deletelink", &BlogPostView::deleteLink);
}

void BlogPostView::id(DomNode& node) const {
	node.inner() = QString::number(blogPostId);
}

void BlogPostView::title(DomNode& node) const {
	node.inner() = blogPost->getTitle();
}

void BlogPostView::text(DomNode& node) const {
	node.inner() = blogPost->getText();
}

void BlogPostView::shortText(DomNode& node) const {
	node.inner() = blogPost->getText();
}

void BlogPostView::showLink(DomNode& node) const {
	node("href") = url(&BlogPostController::show, { { "id", blogPostId } });
}

void BlogPostView::editLink(DomNode& node) const {
	node("href") = url(&BlogPostController::edit, { { "id", blogPostId } });
}

void BlogPostView::deleteLink(DomNode& node) const {
	node("href") = url(&BlogPostController::remove, { { "id", blogPostId } });
}