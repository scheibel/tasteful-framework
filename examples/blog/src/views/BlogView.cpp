#include <views/BlogView>

#include <views/Layout>
#include <session/Session>

BlogView::BlogView() : TemplateView() {
}
 
void BlogView::initialize() {
	Layout* layout = new Layout();
	layout->setSession(getSession<Session>());
	setLayout(layout);
}
