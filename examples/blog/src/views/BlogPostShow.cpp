#include <views/BlogPostShow>

BlogPostShow::BlogPostShow(BlogPost* blogPost, unsigned id) : BlogView(), blogPost(blogPost), id(id) {
	setFilename("blogpostshow.html");
	
	addTransform("blogpost", &BlogPostShow::getBlogPost);
}

QDomNode BlogPostShow::getBlogPost(QDomNode node) {
	return node;
}