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

QDomNode BlogPostEdit::blogEditForm(QDomNode node) {
	node.toElement().setAttribute("action", url(&BlogPostController::save));
	
	return node;
}

QDomNode BlogPostEdit::blogPostId(QDomNode node) {
	node.toElement().setAttribute("value", id);
	
	return node;
}

QDomNode BlogPostEdit::blogPostTitle(QDomNode node) {
	node.toElement().setAttribute("value", blogPost->getTitle());
	
	return node;
}

QDomNode BlogPostEdit::blogPostText(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getText()));
	
	return node;
}

QDomNode BlogPostEdit::saveButtonText(QDomNode node) {
	node.toElement().setAttribute("value", id == 0 ? "Create" : "Save");
	
	return node;
}