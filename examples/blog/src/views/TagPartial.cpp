#include <views/TagPartial>

#include <controllers/SearchController>

TagPartial::TagPartial(DomNode node) : Partial(node), tag(nullptr) {
	addTransform("searchtagurl", &TagPartial::searchTagUrl);
	addTransform("tagname", &TagPartial::tagName);
}

void TagPartial::setData(Tag* tag) {
	this->tag = tag;
}

void TagPartial::searchTagUrl(DomNode& node) const {
	node("href") = url(&SearchController::find, { { "string", tag->getName() } });
}

void TagPartial::tagName(DomNode& node) const {
	node.inner() = tag->getName();
}
