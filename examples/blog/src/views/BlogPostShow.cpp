#include <views/BlogPostShow>

BlogPostShow::BlogPostShow(Session* session, BlogPost* blogPost, unsigned id) : BlogView(session), blogPost(blogPost), id(id) {
	setFilename("blogpostshow.html");
	
	addTransform("blogposttitle", &BlogPostShow::blogPostTitle);
	addTransform("blogpostcontent", &BlogPostShow::blogPostContent);
}

void BlogPostShow::blogPostTitle(DomNode& node) const {
	node.inner() = blogPost->getTitle();
}

void BlogPostShow::blogPostContent(DomNode& node) const {
	node.inner() = blogPost->getText();
}