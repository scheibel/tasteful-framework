#include <views/BlogPostEdit>
#include <controllers/BlogPostController>

BlogPostEdit::BlogPostEdit(Session* session, BlogPost* blogPost, unsigned id) : BlogView(session), blogPost(blogPost), id(id) {
	setFilename("blogpostedit.html");
	
	addTransform("blogeditform", &BlogPostEdit::blogEditForm);
	addTransform("blogpostid", &BlogPostEdit::blogPostId);
	addTransform("blogposttitle", &BlogPostEdit::blogPostTitle);
	addTransform("blogposttext", &BlogPostEdit::blogPostText);
	addTransform("savebuttontext", &BlogPostEdit::saveButtonText);
}

void BlogPostEdit::blogEditForm(DomNode& node) const {
	node("action") = url(&BlogPostController::save);
}

void BlogPostEdit::blogPostId(DomNode& node) const {
	node("value") = id;
}

void BlogPostEdit::blogPostTitle(DomNode& node) const {
	node("value") = blogPost->getTitle();
}

void BlogPostEdit::blogPostText(DomNode& node) const {
	node.inner() = blogPost->getText();
}

void BlogPostEdit::saveButtonText(DomNode& node) const {
	node("value") = (id == 0) ? "Create" : "Save";
}