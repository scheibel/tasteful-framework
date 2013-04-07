#include <views/BlogPostList>

#include <views/BlogPostPartial>
#include <controllers/BlogPostController>

BlogPostList::BlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
	addTransform("newlink", &BlogPostList::newLink);
}

void BlogPostList::blogPostTable(DomNode& node) const {
	BlogPostPartial blogPostPartial(node["tr"][1].remove());
	
	for (unsigned id : blogPosts.keys()) {
		blogPostPartial.setData(blogPosts.value(id), id);
		node << blogPostPartial;
	}
}

void BlogPostList::newLink(DomNode& node) const {
	node("href") = url(&BlogPostController::create);
}
