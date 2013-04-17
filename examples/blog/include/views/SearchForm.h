#pragma once

#include <views/BlogView.h>

class SearchForm : public BlogView {
public:
	SearchForm(Session* session);
	
	void searchUrl(DomNode& node) const;
};
