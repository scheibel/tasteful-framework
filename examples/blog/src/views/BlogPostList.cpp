#include <views/BlogPostList>
#include <views/BlogPostSummary>

BlogPostList::BlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
}

QDomNode BlogPostList::blogPostTable(QDomNode node) {
	QDomNode trNode = node.childNodes().item(1);
	
	node.removeChild(trNode);
	
	for (BlogPost* blogPost : blogPosts) {
		node.appendChild(BlogPostLine(trNode.cloneNode(), blogPost).contentNode());
	}
	
	return node;
}

BlogPostLine::BlogPostLine(QDomNode node, BlogPost* blogPost) : BlogView(), blogPost(blogPost) {
	setNode(node);
	
	addTransform("id", &BlogPostLine::id);
	addTransform("title", &BlogPostLine::title);
	addTransform("showlink", &BlogPostLine::showLink);
	addTransform("editlink", &BlogPostLine::editLink);
	addTransform("deletelink", &BlogPostLine::deleteLink);
}

QDomNode BlogPostLine::id(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(QString::number(0)));
	
	return node;
}

QDomNode BlogPostLine::title(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getTitle()));
	
	return node;
}

QDomNode BlogPostLine::showLink(QDomNode node) {
	node.toElement().setAttribute("href", "#");
	
	return node;
}

QDomNode BlogPostLine::editLink(QDomNode node) {
	node.toElement().setAttribute("href", "#");
	
	return node;
}

QDomNode BlogPostLine::deleteLink(QDomNode node) {
	node.toElement().setAttribute("href", "#");
	
	return node;
}