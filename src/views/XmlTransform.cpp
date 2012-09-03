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

#include <XmlTransform>
#include <iostream>
#include <QStringList>

XmlTransform::XmlTransform() {
}

XmlTransform::~XmlTransform() {
	for (XmlTransform* partial: partials) delete partial;
}

void XmlTransform::transform() {
	document = getDocument(filename);
	transformNode(document.documentElement());
}

void XmlTransform::setFilename(QString filename) {
	this->filename = filename;
}

QDomDocument XmlTransform::getDocument(QString filename)
{
	QFile file("resources:"+filename);
	if (!file.open(QIODevice::ReadOnly)) {
		std::cerr << "Could not open file " << filename.toStdString() << std::endl;
		return QDomDocument();
	}
	QDomDocument doc;
	if (!doc.setContent(&file)) {
		std::cerr << "File " << filename.toStdString() << "not valid xml" << std::endl;
	}
	file.close();
	return doc;
}

QDomNode XmlTransform::findContentNode(QDomNode node) {
	QDomNode contentNode = findFirstNodeWithAttribute(node, "data-content");
	if (contentNode.isNull()) contentNode = node.ownerDocument().elementsByTagName("body").at(0);
	if (contentNode.isNull()) {
		contentNode = node.ownerDocument().createElement("body");
		QDomNodeList children =  node.childNodes();
		for (int i=0; i<children.size();++i) {
			QDomNode child = children.at(i);
			contentNode.appendChild(node.removeChild(child));
		}
	}
	return contentNode;
}

QDomNode XmlTransform::findFirstNodeWithAttribute(QDomNode node, QString attribute) {
	QDomNodeList children =  node.childNodes();
	for (int i=0; i<children.size();++i) {
		QDomElement element = children.at(i).toElement();
		if (!element.isNull()) {
			if (element.hasAttribute(attribute)) return element;
		}
		QDomNode n = findFirstNodeWithAttribute(element, attribute);
		if (!n.isNull()) return n;
	}
	return QDomNode();
}

void XmlTransform::addPartial(QString selector, XmlTransform* partial) {
	partials.insert(selector, partial);
}

void XmlTransform::replaceChildren(QDomNode node, QDomNode contentNode)
{
	QDomNodeList oldChildren = node.childNodes();
	for (int i = 0;i<oldChildren.size();++i) {
		node.removeChild(oldChildren.at(i));
	}
		
	QDomNodeList children = contentNode.childNodes();
	for (int i = 0;i<children.size();++i) {
		QDomNode child = node.ownerDocument().importNode(children.at(i), true);
		node.appendChild(child);
	}
}

QDomNode XmlTransform::transformElement(QDomElement element) {
	QStringList selectors = element.attribute("data-transform").split(QRegExp("\\s+"));
	element.removeAttribute("data-transform");
	QDomNode transformedNode = element;
	for (QString& selector: selectors) {
		if (transforms.contains(selector)) {
			transformedNode = doTransform(selector, transformedNode);
		}
	}
	return transformedNode;
}

void XmlTransform::transformNode(QDomNode node) {
	QDomNodeList children =  node.childNodes();
	for (int i=0; i<children.size();++i) {
		QDomElement element = children.at(i).toElement();
		if (!element.isNull()) {
			if (element.hasAttribute("data-transform")) {
				QDomNode transformedNode = transformElement(element);
				if (!transformedNode.isNull()) node.replaceChild(transformedNode, element);
			} else if (element.hasAttribute("data-import")) {
				QString importSelector = element.attribute("data-import");
				element.removeAttribute("data-import");
				if (partials.contains(importSelector)) {
					XmlTransform* t = partials[importSelector];
					t->transform();
					replaceChildren(element, findContentNode(t->document));
				}
			} else {
				transformNode(element);
			}
		}
	}	
}

QDomNode XmlTransform::doTransform(QString selector, QDomNode node) {
	return (this->*transforms[selector])(node);
}

QDomNode XmlTransform::$(NodeCreator creator) {
	return creator(document);
}

QDomNode XmlTransform::$(QString text) {
	return document.createTextNode(text);
}
