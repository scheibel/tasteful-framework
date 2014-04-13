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

#include <tastefulframework/XmlTransform.h>
#include <QStringList>
#include <QDomDocument>
#include <QtAlgorithms>

XmlTransform::~XmlTransform() {
	qDeleteAll(transformations);
}

void XmlTransform::transform(DomNode& node) const {
	transformRecursion(node);
}

DomNode XmlTransform::transformFile(const QString& filename) const {
	QDomDocument document = loadDocument(filename);
	
	if (document.isNull()) {
		return DomNode();
	}
	
	DomNode node = document.documentElement();
	
	transform(node);
	
	return node;
}

void XmlTransform::transformRecursion(DomNode& node) const {
	if (node.isElement() && node.hasAttribute("data-transform")) {
		transformElement(node);
	}
	
	for (DomNode& child : node.children()) {
		transformRecursion(child);
	}
}

void XmlTransform::transformElement(DomNode& element) const {
	QStringList selectors = element.getAttribute("data-transform").split(QRegExp("\\s+"));
	element.removeAttribute("data-transform");
	
	for (const QString& selector: selectors) {
		if (transformations.contains(selector)) {
			(*transformations[selector])(element);
		}
	}
}

DomNode XmlTransform::findContentNode(const DomNode& node) const {
	DomNode contentNode = findFirstNodeWithAttribute(node, "data-content");
	if (!contentNode.isNull()) {
		return contentNode;
	}
	
	DomNode bodyNode = node.root().first("body");
	if (!bodyNode.isNull()) {
		return bodyNode;
	}
	
	return node;
}

DomNode XmlTransform::findFirstNodeWithAttribute(const DomNode& node, const QString& attribute) const {
	for (DomNode& child : node.children()) {
		if (!child.isNull()) {
			if (child.hasAttribute(attribute)) {
				return child;
			}
		}
		
		DomNode n = findFirstNodeWithAttribute(child, attribute);
		if (!n.isNull()) {
			return n;
		}
	}
	
	return DomNode();
}

void XmlTransform::addTransform(const QString& selector, LambdaNodeTransformation::Lambda transform) {
	transformations.insert(selector, new LambdaNodeTransformation(transform));
}
