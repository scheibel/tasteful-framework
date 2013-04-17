#include <controllers/SearchController.h>

#include <datamappers/BlogPostMapper.h>
#include <views/SearchForm.h>
#include <views/SearchResult.h>

SearchController::SearchController() : BlogController() {
}

void SearchController::index() {
	render(SearchForm(getSession()));
}

void SearchController::find() {
	QString searchString = parameters["string"].value<QString>();
	
	if (searchString.isNull() || searchString.isEmpty()) {
		render(SearchForm(getSession()));
		
		return;
	}
	
	QList<BlogPost*> searchResult;
	for (BlogPost* blogPost : BlogPostMapper::instance().find("1 ORDER BY id DESC")) {
		if (blogPost->getTitle().contains(searchString, Qt::CaseInsensitive)) {
			searchResult << blogPost;
		} else if (blogPost->getText().contains(searchString, Qt::CaseInsensitive)) {
			searchResult << blogPost;
		} else {
			for (Tag* tag : blogPost->getTags()) {
				if (tag->getName().contains(searchString, Qt::CaseInsensitive)) {
					searchResult << blogPost;
					
					break;
				}
			}
		}
	}
	
	render(SearchResult(getSession(), searchResult, searchString));
}

void SearchController::findPost() {
	find();
}
