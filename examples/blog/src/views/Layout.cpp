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

QDomNode Layout::stylesheets(QDomNode node) {
	node.appendChild($(link(type("text/css"), href("/stylesheets/blog.css"), rel("stylesheet"))));
	
	return node;
}

QDomNode Layout::menu(QDomNode node) {
	if (session->isValid() && session->isLoggedIn()) {
		node.appendChild($(a(href(url(&BlogPostController::index)), "My blogposts")));
		node.appendChild($(" | "));
	}
	
	node.appendChild($(a(href(url(&AllBlogPostController::index)), "List blogposts")));
	
	return node;
}

QDomNode Layout::login(QDomNode node) {
	if (session->isValid()) {
		if (session->isLoggedIn()) {
			return $(span(id("session"),
				a(href(url(&LoginController::logout)), "Log out"),
				" | Logged in as " + session->author->getEmail()
			));
		} else {
			return $(span(id("session"),
				a(href(url(&LoginController::index)), "Log in"),
				" | ",
				a(href(url(&RegisterController::index)), "Sign up")
			));
		}
	} else {
		return $(span(id("session"),
			"Cannot log in because Cookies are not allowed"
		));
	}
}