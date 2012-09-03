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

TagModifier DomHelper::attribute(QString name, QString value) {
	return [name, value](QDomElement element) {
		element.setAttribute(name, value);
	};
}

TagModifier DomHelper::cssClass(QString name) {
	return attribute("class", name);
}

QDomElement NodeCreator::operator()(QDomDocument document) const {
	QDomElement element = document.createElement(name);
	for (TagModifier modifier: modifiers) modifier(element);
	return element;
}

void NodeCreator::operator()(QDomNode node) const {
	QDomElement element = (*this)(node.ownerDocument());
	node.appendChild(element);
}

NodeCreatorPlaceholder DomHelper::tag(QString name) {
	return NodeCreatorPlaceholder(name);
}

NodeCreator::NodeCreator(QString name) : name(name) {
}

NodeCreator::NodeCreator(NodeCreatorPlaceholder placeholder) {
	*this = placeholder();
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

void NodeCreator::addModifier(long i) {
	addModifier(QString::number(i));
}

void NodeCreator::addModifier(double d) {
	addModifier(QString::number(d));
}


