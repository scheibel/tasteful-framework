#include <views/BlogPostShow.h>

#include <views/TagPartial.h>

BlogPostShow::BlogPostShow(Session* session, BlogPost* blogPost, unsigned id)
: BlogView(session)
, blogPost(blogPost)
, id(id) {
	setFilename("blogpostshow.html");
	
	addTransform("blogposttitle", &BlogPostShow::blogPostTitle);
	addTransform("blogpostcontent", &BlogPostShow::blogPostContent);
	addTransform("tags", &BlogPostShow::blogPostTags);
}

void BlogPostShow::blogPostTitle(DomNode& node) const {
	node.inner() = blogPost->getTitle();
}

void BlogPostShow::blogPostContent(DomNode& node) const {
	node.inner() = blogPost->getText();
}

void BlogPostShow::blogPostTags(DomNode& node) const {
	TagPartial tagPartial(node.children()[0].remove());
	
	if (blogPost->getTags().size()) {
		for (Tag* tag : blogPost->getTags()) {
			tagPartial.setData(tag);
			node << tagPartial;
			node << " ";
		}
	} else {
		node.inner() = " ";
	}
}
