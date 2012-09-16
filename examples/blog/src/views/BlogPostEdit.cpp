#include <views/BlogPostEdit>

BlogPostEdit::BlogPostEdit(BlogPost* blogPost, unsigned id) : BlogView(), blogPost(blogPost), id(id) {
	setFilename("blogpostedit.html");
	
	addTransform("blogpostform", &BlogPostEdit::blogPostForm);
}

QDomNode BlogPostEdit::blogPostForm(QDomNode node) {
	return node;
}