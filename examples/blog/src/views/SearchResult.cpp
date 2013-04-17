#include <views/SearchResult>

#include <views/BlogPostPartial>
#include <datamappers/BlogPostMapper>

SearchResult::SearchResult(Session* session, QList<BlogPost*> searchResult, const QString& searchString) : BlogView(session), searchResult(searchResult), searchString(searchString) {
	setFilename("searchresult.html");
	
	addTransform("blogpostlist", &SearchResult::blogPostList);
}

void SearchResult::blogPostList(DomNode& node) const {
	if (searchResult.empty()) {
		node.inner() = "No results were found for \"" + searchString + "\"";
		
		return;
	}
	
	BlogPostPartial blogPostPartial(node.firstChild().remove(), session);
	
	for (BlogPost* blogPost : searchResult) {
		blogPostPartial.setData(blogPost, BlogPostMapper::instance().idOf(blogPost));
		node << blogPostPartial;
	}
}
