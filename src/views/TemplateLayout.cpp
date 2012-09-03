/**
  * (C) LGPL-3
  *
  * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
  *
  * Copyright: 2012 Lux, Scheibel
  * Authors:
  *     Roland Lux <rollux2000@googlemail.com>
  *     Willy Scheibel <willyscheibel@gmx.de>
  * 
  * This file is part of Tasteful Framework.
  *
  * Tasteful Framework is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  * 
  * Tasteful Framework is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Lesser General Public License for more details.
  * 
  * You should have received a copy of the GNU Lesser General Public License
  * along with Tasteful Framework.  If not, see <http://www.gnu.org/licenses/>.
  **/

#include <TemplateLayout>
#include <QTextStream>

TemplateLayout::TemplateLayout() {
}

TemplateLayout::TemplateLayout(QString filename) {
	setFilename(filename);
}

TemplateLayout::~TemplateLayout() {
}

QDomDocument TemplateLayout::layout(QDomDocument contentDocument) {
	transform();
	mergeHead(contentDocument.elementsByTagName("head").at(0));
	
	QDomNode contentNode = findContentNode(document.documentElement());
	contentNode.toElement().removeAttribute("data-content");
	
	replaceChildren(contentNode, findContentNode(contentDocument.documentElement()));
	
	return document;
}

void TemplateLayout::mergeHead(QDomNode contentHead) {
	if (contentHead.isNull()) return;
	QDomNode head = document.elementsByTagName("head").at(0);
	if (head.isNull()) return;
	
	QDomNodeList headChildren = head.childNodes();
	QDomNodeList contentHeadChildren = contentHead.childNodes();
	for (int i=0; i<contentHeadChildren.size(); ++i) {
		QDomElement contentHeadChild = contentHeadChildren.at(i).toElement();
		if (contentHeadChild.isNull()) continue;
		bool duplicate = false;
		for (int j=0; j<headChildren.size(); ++j) {
			QDomElement headChild = headChildren.at(i).toElement();
			if (headChild.isNull()) continue;
			if (sameHeadNodes(headChild, contentHeadChild)) {
				duplicate = true;
				break;
			}
		}
		if (!duplicate) {
			QDomNode importedNode = document.importNode(contentHeadChild, true);
			head.appendChild(importedNode);
		}
	}
}

bool TemplateLayout::sameHeadNodes(QDomNode node1, QDomNode node2) {
	if (node1.toElement().tagName()!=node2.toElement().tagName()) return false;
	return sameAttributes(node1, node2);
	//TODO: take text into account
}

bool TemplateLayout::sameAttributes(QDomNode node1, QDomNode node2) {
	QDomNamedNodeMap map1 = node1.attributes();
	QDomNamedNodeMap map2 = node2.attributes();
	if (map1.size()!=map2.size()) return false;
	
	for (int i=0; i<map1.size(); ++i) {
		QDomAttr attr1 = map1.item(i).toAttr();
		QDomAttr attr2 = map2.item(i).toAttr();
		if (attr1.name()!=attr2.name() || attr1.value()!=attr2.value()) {
			return false;
		}
	}
	
	return true;
}
