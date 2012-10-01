#include <views/BlogPostShow>

BlogPostShow::BlogPostShow(BlogPost* blogPost, unsigned id) : BlogView(), blogPost(blogPost), id(id) {
	setFilename("blogpostshow.html");
	
	addTransform("blogposttitle", &BlogPostShow::blogPostTitle);
	addTransform("blogpostcontent", &BlogPostShow::blogPostContent);
}

QDomNode BlogPostShow::blogPostTitle(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getTitle()));
	
	return node;
}

QDomNode BlogPostShow::blogPostContent(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getText()));
	
	return node;
}