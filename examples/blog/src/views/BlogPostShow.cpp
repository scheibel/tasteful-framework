#include <views/BlogPostShow>

BlogPostShow::BlogPostShow(BlogPost* blogPost, unsigned id) : BlogView(), blogPost(blogPost), id(id) {
	setFilename("blogpostshow.html");
	
	addTransform("blogposttitle", &BlogPostShow::blogPostTitle);
	addTransform("blogpostcontent", &BlogPostShow::blogPostContent);
}

void BlogPostShow::blogPostTitle(DomNode& node) {
	node.replaceChildren(blogPost->getTitle());
}

void BlogPostShow::blogPostContent(DomNode& node) {
	node.replaceChildren(blogPost->getText());
}