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

#include <DomHelper>
#include <DomNode>


QDomDocument DomHelper::currentDocument() {
	static bool initialized = false;
	if (!initialized) {
		__emptyDocument.setContent(QString("<empty>"));
		initialized = true;
	}
	return __emptyDocument;
}

/*DomNode DomHelper::$(const QString& xmlOrSelector) {
	return $(xmlOrSelector, currentDocument().documentElement());
}

DomNode DomHelper::$(const QString& xmlOrSelector, DomNode node) {
	if (xmlOrSelector.trimmed().startsWith("<")) {
		return node.createXml(xmlOrSelector);
	}
	return node.select(xmlOrSelector);
}*/

TagModifier DomHelper::attribute(QString name, QString value) {
	return [name, value](QDomElement element) {
		element.setAttribute(name, value);
	};
}

TagModifier DomHelper::cssClass(QString name) {
	return attribute("class", name);
}

NodeCreatorPlaceholder DomHelper::tag(QString name) {
	return NodeCreatorPlaceholder(name);
}

NodeCreator::NodeCreator() : null(true) {
}

NodeCreator::NodeCreator(QString name) : name(name), null(false) {
}

NodeCreator::NodeCreator(NodeCreatorPlaceholder placeholder) {
	*this = placeholder();
}

QDomElement NodeCreator::operator()(QDomDocument document) const {
	if (null) return QDomElement();
	
	QDomElement element = document.createElement(name);
	for (TagModifier modify: modifiers) modify(element);
	return element;
}

void NodeCreator::operator()(QDomNode node) const {
	if (null) return;
	
	QDomElement element = (*this)(node.ownerDocument());
	node.appendChild(element);
}

void NodeCreator::addModifier(TagModifier modifier) {
	modifiers << modifier;
}

void NodeCreator::addModifier(NodeCreator creator) {
	addModifier([creator](QDomElement element) {
		element.appendChild(creator(element.ownerDocument()));
	});
}

void NodeCreator::addModifier(NodeCreatorPlaceholder creatorPlaceholder) {
	addModifier(creatorPlaceholder());
}

void NodeCreator::addModifier(QDomNode node) {
	addModifier([node](QDomElement element) {
		element.appendChild(node);
	});
}

void NodeCreator::addModifier(DomNode node) {
	addModifier(node.asQDomNode());
}

void NodeCreator::addModifier(QString text) {
	addModifier([text](QDomElement element) {
		element.appendChild(element.ownerDocument().createTextNode(text));
	});
}

void NodeCreator::addModifier(const char* text) {
	addModifier(QString(text));
}

void NodeCreator::addModifier(int i) {
	addModifier(QString::number(i));
}

void NodeCreator::addModifier(unsigned u) {
	addModifier(QString::number(u));
}

void NodeCreator::addModifier(long i) {
	addModifier(QString::number(i));
}

void NodeCreator::addModifier(double d) {
	addModifier(QString::number(d));
}


