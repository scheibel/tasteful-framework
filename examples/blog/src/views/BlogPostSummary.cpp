#include <views/BlogPostSummary>

BlogPostSummary::BlogPostSummary(BlogPost* blogPost) : BlogView(), blogPost(blogPost) {
	setFilename("blogpostsummary.html");
	
	addTransform("url", &BlogPostSummary::url);
	addTransform("title", &BlogPostSummary::title);
	addTransform("shorttext", &BlogPostSummary::shorttext);
}

QDomNode BlogPostSummary::url(QDomNode node) {
	node.toElement().setAttribute("href", "#testurl");
	
	return node;
}

QDomNode BlogPostSummary::title(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getTitle()));
	
	return node;
}

QDomNode BlogPostSummary::shorttext(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getText()));
	
	return node;
}