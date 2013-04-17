#include <views/SearchForm>

#include <controllers/SearchController>

SearchForm::SearchForm(Session* session) : BlogView(session) {
	setFilename("searchform.html");
	
	addTransform("searchurl", &SearchForm::searchUrl);
}

void SearchForm::searchUrl(DomNode& node) const {
	node("action") = url(&SearchController::findPost);
}
