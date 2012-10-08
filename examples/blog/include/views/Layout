#pragma once

#include <TemplatedLayout>
#include <session/Session>

class Layout : public TemplatedLayout {
	public:
		Layout();
		
		void setSession(Session* newSession);
	protected:
		void stylesheets(DomNode& node) const;
		void login(DomNode& node) const;
		void menu(DomNode& node) const;
	private:
		Session* session;
};
