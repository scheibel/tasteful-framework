#include <views/BlogView.h>

BlogView::BlogView(Session* session) : session(session) {
	layout.setSession(session);
}

const TemplatedLayout& BlogView::getLayout() const {
	return layout;
}
