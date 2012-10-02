#include <views/Layout>

#include <controllers/LoginController>
#include <controllers/RegisterController>
#include <controllers/BlogPostController>
#include <controllers/AllBlogPostController>

Layout::Layout() : TemplateLayout(), session(nullptr) {
	setFilename("layout.html");
	addTransform("stylesheets", &Layout::stylesheets);
	addTransform("login", &Layout::login);
	addTransform("menu", &Layout::menu);
}

void Layout::setSession(Session* newSession) {
	session = newSession;
}

void Layout::stylesheets(DomNode& node) {
	node << link(type("text/css"), href("/stylesheets/blog.css"), rel("stylesheet"));
}

void Layout::menu(DomNode& node) {
	if (session->isValid() && session->isLoggedIn()) {
		node << a(href(url(&BlogPostController::index)), "My blogposts") << " | ";
	}
	
	node << a(href(url(&AllBlogPostController::index)), "List blogposts");
}

void Layout::login(DomNode& node) {
	if (session->isValid()) {
		if (session->isLoggedIn()) {
			node << a(href(url(&LoginController::logout)), "Log out") << " | Logged in as " + session->author->getEmail();
		} else {
			node << a(href(url(&LoginController::index)), "Log in") << " | " << a(href(url(&RegisterController::index)), "Sign up");
		}
	} else {
		node << "Cannot log in because Cookies are not allowed";
	}
}