#include <views/BlogPostSummary>

#include <controllers/BlogPostController>

BlogPostSummary::BlogPostSummary(BlogPost* blogPost) : BlogView(), blogPost(blogPost) {
	setFilename("blogpostsummary.html");
	
	addTransform("url", &BlogPostSummary::url);
	addTransform("title", &BlogPostSummary::title);
	addTransform("shorttext", &BlogPostSummary::shorttext);
}

void BlogPostSummary::url(DomNode& node) {
	node("href") = UrlHelper::url(&BlogPostController::show, { { "id", BlogPostMapper::instance().idOf(blogPost) } });
}

void BlogPostSummary::title(DomNode& node) {
	node.inner() = blogPost->getTitle();
}

void BlogPostSummary::shorttext(DomNode& node) {
	node.inner() = blogPost->getText();
}