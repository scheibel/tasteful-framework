#pragma once

#include <session/Session.h>
#include <views/Layout.h>

#include <LayoutedTemplateView>

class BlogView : public LayoutedTemplateView {
public:
	BlogView(Session* session);
protected:
	Session* session;
	Layout layout;
	
	const TemplatedLayout& getLayout() const;
};
