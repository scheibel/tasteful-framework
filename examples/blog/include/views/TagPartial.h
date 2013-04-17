#pragma once

#include <models/Tag.h>

#include <Partial>

class TagPartial : public Partial {
public:
	TagPartial(DomNode node);

	void setData(Tag* tag);
	
	void searchTagUrl(DomNode& node) const;
	void tagName(DomNode& node) const;
private:
	Tag* tag;
};
