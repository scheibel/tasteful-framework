#include <views/BlogPostList>

#include <views/BlogPostPartial>

BlogPostList::BlogPostList(Session* session, QHash<unsigned, BlogPost*> blogPosts) : BlogView(session), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
}

void BlogPostList::blogPostTable(DomNode& node) const {
	BlogPostPartial blogPostPartial(node["tr"][1].remove());
	
	for (unsigned id : blogPosts.keys()) {
		blogPostPartial.setData(blogPosts.value(id), id);
		node << blogPostPartial;
	}
}
