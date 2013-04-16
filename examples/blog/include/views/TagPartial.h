#pragma once

#include <Partial>
#include <models/Tag>

class TagPartial : public Partial {
	public:
		TagPartial(DomNode node);
	
		void setData(Tag* tag);
		
		void searchTagUrl(DomNode& node) const;
		void tagName(DomNode& node) const;
	private:
		Tag* tag;
};
