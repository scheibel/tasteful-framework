#include <views/BlogPostList>

#include <views/BlogPostView>

BlogPostList::BlogPostList(QHash<unsigned, BlogPost*> blogPosts) : BlogView(), blogPosts(blogPosts) {
	setFilename("blogposttable.html");
	
	addTransform("blogposttable", &BlogPostList::blogPostTable);
}

void BlogPostList::blogPostTable(DomNode& node) const {
	DomNode trNode = node["tr"][1].remove();
	
	for (unsigned id : blogPosts.keys()) {
		//node << BlogPostView(trNode.clone(), blogPosts.value(id), id).contentNode();
	}
}
