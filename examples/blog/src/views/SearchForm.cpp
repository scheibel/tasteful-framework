#include <views/SearchForm.h>

#include <controllers/SearchController.h>

SearchForm::SearchForm(Session* session) : BlogView(session) {
	setFilename("searchform.html");
	
	addTransform("searchurl", &SearchForm::searchUrl);
}

void SearchForm::searchUrl(DomNode& node) const {
	node("action") = url(&SearchController::findPost);
}
