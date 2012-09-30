#include <views/BlogPostList>
#include <views/BlogPostSummary>
#include <datamappers/BlogPostMapper>
#include <controllers/BlogPostController>

BlogPostList::BlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
}

QDomNode BlogPostList::blogPostTable(QDomNode node) {
	QDomNode trNode = node.childNodes().item(1);
	
	node.removeChild(trNode);
	
	for (unsigned id : blogPosts.keys()) {
		node.appendChild(BlogPostLine(trNode.cloneNode(), blogPosts.value(id), id).contentNode());
	}
	
	return node;
}

BlogPostLine::BlogPostLine(QDomNode node, BlogPost* blogPost, unsigned blogPostId) : BlogView(), blogPost(blogPost), blogPostId(blogPostId) {
	setNode(node);
	
	addTransform("id", &BlogPostLine::id);
	addTransform("title", &BlogPostLine::title);
	addTransform("showlink", &BlogPostLine::showLink);
	addTransform("editlink", &BlogPostLine::editLink);
	addTransform("deletelink", &BlogPostLine::deleteLink);
}

QDomNode BlogPostLine::id(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(QString::number(blogPostId)));
	
	return node;
}

QDomNode BlogPostLine::title(QDomNode node) {
	removeChildren(node);
	
	node.appendChild($(blogPost->getTitle()));
	
	return node;
}

QDomNode BlogPostLine::showLink(QDomNode node) {
	node.toElement().setAttribute("href", url(&BlogPostController::show, { { "id", blogPostId } }));
	
	return node;
}

QDomNode BlogPostLine::editLink(QDomNode node) {
	node.toElement().setAttribute("href", url(&BlogPostController::edit, { { "id", blogPostId } }));
	
	return node;
}

QDomNode BlogPostLine::deleteLink(QDomNode node) {
	node.toElement().setAttribute("href", url(&BlogPostController::remove, { { "id", blogPostId } }));
	
	return node;
}