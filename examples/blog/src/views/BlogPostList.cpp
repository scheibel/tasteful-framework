#include <views/BlogPostList.h>

#include <controllers/BlogPostController.h>
#include <views/BlogPostPartial.h>

BlogPostList::BlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
	addTransform("newlink", &BlogPostList::newLink);
}

void BlogPostList::blogPostTable(DomNode& node) const {
	BlogPostPartial blogPostPartial(node["tr"][1].remove(), session);
	
	for (unsigned id : blogPosts.keys()) {
		blogPostPartial.setData(blogPosts.value(id), id);
		node << blogPostPartial;
	}
}

void BlogPostList::newLink(DomNode& node) const {
	node("href") = url(&BlogPostController::create);
}
