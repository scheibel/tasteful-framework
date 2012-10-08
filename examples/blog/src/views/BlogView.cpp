#include <views/BlogView>

BlogView::BlogView(Session* session) {
	layout.setSession(session);
}

const TemplatedLayout& BlogView::getLayout() const {
	return layout;
}
