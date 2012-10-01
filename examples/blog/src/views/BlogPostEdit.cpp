#include <views/BlogPostEdit>
#include <controllers/BlogPostController>

BlogPostEdit::BlogPostEdit(BlogPost* blogPost, unsigned id) : BlogView(), blogPost(blogPost), id(id) {
	setFilename("blogpostedit.html");
	
	addTransform("blogeditform", &BlogPostEdit::blogEditForm);
	addTransform("blogpostid", &BlogPostEdit::blogPostId);
	addTransform("blogposttitle", &BlogPostEdit::blogPostTitle);
	addTransform("blogposttext", &BlogPostEdit::blogPostText);
	addTransform("savebuttontext", &BlogPostEdit::saveButtonText);
}

void BlogPostEdit::blogEditForm(DomNode& node) {
	node.attribute("action") = url(&BlogPostController::save);
}

void BlogPostEdit::blogPostId(DomNode& node) {
	node.attribute("value") = id;
}

void BlogPostEdit::blogPostTitle(DomNode& node) {
	node.attribute("value") = blogPost->getTitle();
}

void BlogPostEdit::blogPostText(DomNode& node) {
	node.replaceChildren(blogPost->getText());
}

void BlogPostEdit::saveButtonText(DomNode& node) {
	node.attribute("value") = id == 0 ? "Create" : "Save";
}