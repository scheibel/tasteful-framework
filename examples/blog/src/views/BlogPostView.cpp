#include <views/BlogPostView>

#include <controllers/BlogPostController>

BlogPostView::BlogPostView(DomNode node) : node(node), blogPost(nullptr), blogPostId(0) {
	addTransform("id", &BlogPostView::id);
	addTransform("title", &BlogPostView::title);
	addTransform("text", &BlogPostView::text);
	addTransform("shorttext", &BlogPostView::shortText);
	addTransform("showlink", &BlogPostView::showLink);
	addTransform("editlink", &BlogPostView::editLink);
	addTransform("deletelink", &BlogPostView::deleteLink);
}

DomNode BlogPostView::toNode() const {
	DomNode n = node.clone();
	transform(n);
	return n;
}

void BlogPostView::reset(BlogPost* blogPost, unsigned blogPostId) {
	this->blogPost = blogPost;
	this->blogPostId = blogPostId;
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