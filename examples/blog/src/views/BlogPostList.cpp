#include <views/BlogPostList>
#include <views/BlogPostSummary>
#include <datamappers/BlogPostMapper>
#include <controllers/BlogPostController>

BlogPostList::BlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
}

void BlogPostList::blogPostTable(DomNode& node) {
	DomNode trNode = node["tr"][1].remove();
	
	for (unsigned id : blogPosts.keys()) {
		node.appendChild(BlogPostLine(trNode.clone(), blogPosts.value(id), id).contentNode());
	}
}

BlogPostLine::BlogPostLine(DomNode node, BlogPost* blogPost, unsigned blogPostId) : BlogView(), blogPost(blogPost), blogPostId(blogPostId) {
	setNode(node);
	
	addTransform("id", &BlogPostLine::id);
	addTransform("title", &BlogPostLine::title);
	addTransform("showlink", &BlogPostLine::showLink);
	addTransform("editlink", &BlogPostLine::editLink);
	addTransform("deletelink", &BlogPostLine::deleteLink);
}

void BlogPostLine::id(DomNode& node) {
	node.replaceChildren(QString::number(blogPostId));
}

void BlogPostLine::title(DomNode& node) {
	node.replaceChildren(blogPost->getTitle());
}

void BlogPostLine::showLink(DomNode& node) {
	node.attribute("href") = url(&BlogPostController::show, { { "id", blogPostId } });
}

void BlogPostLine::editLink(DomNode& node) {
	node.attribute("href") = url(&BlogPostController::edit, { { "id", blogPostId } });
}

void BlogPostLine::deleteLink(DomNode& node) {
	node.attribute("href") = url(&BlogPostController::remove, { { "id", blogPostId } });
}