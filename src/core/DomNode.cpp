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

#include <DomNode>
#include <DomHelper>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>

using namespace dom;

Node::Node(QDomNode qNode, MissBehavior missBehavior, bool _isNew) : qNode(qNode), missBehavior(missBehavior), _isNew(_isNew) {
}

Node::Node(const QString& text, MissBehavior missBehavior) : _isNew(true), missBehavior(missBehavior) {
	emptyDocument.setContent(QString("<empty>"));
	qNode = emptyDocument.createTextNode(text);
}

Node::Node(NodeCreator nodeCreator, MissBehavior missBehavior) : _isNew(true), missBehavior(missBehavior) {
	emptyDocument.setContent(QString("<empty>"));
	qNode = nodeCreator(emptyDocument);
}

bool Node::isNull() {
	return false;
}

void Node::setMissBehavior(MissBehavior missBehavior) {
	this->missBehavior = missBehavior;
}

QDomNode Node::asQDomNode() {
	return qNode;
}

bool Node::isNew() {
	return _isNew;
}

QString Node::toString() {
	QString str;
	QTextStream stream(&str);
	stream << qNode;
	return str;
}


AbstractNode* Node::parent() {
	QDomNode parentNode = qNode.parentNode();
	if (parentNode.isNull()) return new NullNode();
	return new Node(qNode.parentNode(), missBehavior);
}

AbstractNode* Node::get(const QString& name) {
	QDomNodeList childNodes = qNode.toElement().childNodes();
	for (int i=0; i<childNodes.size(); ++i) {
		QDomElement child = childNodes.at(i).toElement();
		if (child.isNull()) continue;
		if (child.tagName()==name) {
			return new Node(child, missBehavior);
		}
	}
	
	return handleMiss(name);
}

QList<AbstractNode*> Node::all() {
	QList<AbstractNode*> list;
	
	QString name = qNode.toElement().tagName();
	QDomNodeList childNodes = qNode.parentNode().toElement().childNodes();
	for (int i=0; i<childNodes.size(); ++i) {
		QDomElement child = childNodes.at(i).toElement();
		if (child.isNull()) continue;
		if (child.tagName()==name) {
			list << new Node(child, missBehavior);
		}
	}
	
	return list;
}

QList<AbstractNode*> Node::children() {
	QList<AbstractNode*> list;
	
	QDomNodeList childNodes = qNode.toElement().childNodes();
	for (int i=0; i<childNodes.size(); ++i) {
		list << new Node(childNodes.at(i), missBehavior);
	}
	
	return list;
}

AbstractNode* Node::handleMiss(const QString& name) {
	switch (missBehavior) {
		case AUTO_CREATE: {
			QDomNode newNode = qNode.appendChild(qNode.ownerDocument().createElement(name));
			return new Node(newNode, missBehavior, true);
		}
		case RAISE_EXCEPTION:
			throw "Node not found";
		default:
			return new NullNode();
	}
}

AbstractNode* Node::prepend(AbstractNode* otherNode) {
	QDomNode newNode = qNode.ownerDocument().importNode(otherNode->asQDomNode(), true);
	qNode.parentNode().insertBefore(newNode, qNode);
	return new Node(newNode, missBehavior, otherNode->isNew());
}

AbstractNode* Node::append(AbstractNode* otherNode) {
	QDomNode newNode = qNode.ownerDocument().importNode(otherNode->asQDomNode(), true);
	qNode.parentNode().insertAfter(newNode, qNode);
	return new Node(newNode, missBehavior, otherNode->isNew());
}

AbstractNode* Node::prependChild(AbstractNode* childNode) {
	QDomNode newNode = qNode.ownerDocument().importNode(childNode->asQDomNode(), true);
	qNode.insertBefore(newNode, qNode.firstChild());
	return new Node(newNode, missBehavior, childNode->isNew());
}

AbstractNode* Node::appendChild(AbstractNode* childNode) {
	QDomNode newNode = qNode.ownerDocument().importNode(childNode->asQDomNode(), true);
	qNode.appendChild(newNode);
	return new Node(newNode, missBehavior, childNode->isNew());
}

AbstractNode* Node::replaceWith(AbstractNode* childNode) {
	QDomNode newNode = qNode.ownerDocument().importNode(childNode->asQDomNode(), true);
	qNode.parentNode().replaceChild(newNode, qNode);
	qNode = newNode;
	return new Node(newNode, missBehavior, childNode->isNew());
}

void Node::remove() {
	qNode.parentNode().removeChild(qNode);
	qNode = QDomNode();
}

//----------------------

RawXml::RawXml(DomNode& node) : node(node) {
}

const QString& RawXml::operator=(const QString& rawXml) {
	node.setRaw(rawXml);
}

QString RawXml::toString() {
	return node.toString();
}

DomAttribute::DomAttribute() {
}

DomAttribute::DomAttribute(QDomNode node, const QString& name, const QString& defaultValue) {
	QDomElement element = node.toElement();
	if (!element.isNull()) {
		attr = element.attributeNode(name);
		if (attr.isNull()) {
			element.setAttribute(name, defaultValue.isNull() ? name : defaultValue);
			attr = element.attributeNode(name);
		}
	}
}

QString DomAttribute::name() {
	return attr.name();
}

QString DomAttribute::value() {
	return attr.value();
}

QDomAttr DomAttribute::asQDomAttr() {
	return attr;
}

void DomAttribute::remove() {
	attr.ownerElement().removeAttributeNode(attr);
}

const QString& DomAttribute::operator=(const QString& str) {
	attr.setValue(str.isNull() ? attr.name() : str);
	return str;
}

QString DomAttribute::toString() {
	return name()+"="+value();
}

DomAttributes::DomAttributes(QDomNode node) : node(node) {
	QDomNamedNodeMap map = node.attributes();
	for (int i=0; i<map.count(); ++i) {
		QDomAttr attr = map.item(i).toAttr();
		if (attr.isNull()) continue;
		attributes[attr.name()] = DomAttribute(node, attr.name());
	}
}

int DomAttributes::size() {
	return attributes.size();
}

QHash<QString, DomAttribute>::iterator DomAttributes::begin() {
	return attributes.begin();
}

QHash<QString, DomAttribute>::iterator DomAttributes::end() {
	return attributes.end();
}

void DomAttributes::remove(const QString& name) {
	if (attributes.contains(name)) {
		DomAttribute attribute = attributes[name];
		attribute.remove();
		attributes.remove(name);
	}
}

DomAttribute& DomAttributes::operator[](const QString& name) {
	if (!attributes.contains(name)) {
		attributes.insert(name, DomAttribute(node, name));
	}
	return attributes[name];
}

QString DomAttributes::toString() {
	QString str;
	QTextStream stream(&str);
	for (DomAttribute attribute: attributes) {
		stream << attribute.toString() << " ";
	}
	
	return str;
}

QString DomNodeList::toString() {
	QString str;
	QTextStream stream(&str);
	for (DomNode& node: *this) {
		stream << node.toString() << endl;
	}
		
	return str;
}

DomNodeList DomNodeList::convert(QList<AbstractNode*> nodes) {
	DomNodeList list;
	for (AbstractNode* n: nodes) list << DomNode(n);
	return list;
}

DomNode::DomNode() : node(new NullNode()) {
}

DomNode::DomNode(AbstractNode* node) : node(node) {
}

DomNode::DomNode(const QString& text, dom::MissBehavior missBehavior) : node(new Node(text, missBehavior)) {
}

DomNode::DomNode(const char* text, dom::MissBehavior missBehavior) : node(new Node(text, missBehavior)) {
}

DomNode::DomNode(QDomNode qNode, dom::MissBehavior missBehavior) : node(new Node(qNode, missBehavior)) {
}

DomNode::DomNode(NodeCreator nodeCreator, dom::MissBehavior missBehavior) : node(new Node(nodeCreator, missBehavior)) {
}

DomNode::DomNode(NodeCreatorPlaceholder nodeCreatorPlaceholder, dom::MissBehavior missBehavior) : node(new Node(nodeCreatorPlaceholder(), missBehavior)) {
}

QDomNode DomNode::asQDomNode() {
	return node->asQDomNode();
}

QDomDocument DomNode::ownerDocument() {
	return node->asQDomNode().ownerDocument();
}

DomNode DomNode::createTextNode(const QString& text) {
	return ownerDocument().createTextNode(text);
}

DomNode  DomNode::createElement(const QString& tagName) {
	return ownerDocument().createElement(tagName);
}

DomNode  DomNode::createXml(const QString& xml) {
	QDomDocument doc;
	doc.setContent(xml);
	return ownerDocument().importNode(doc.documentElement(), true);
}

QString DomNode::toString() {
	return node->toString();
}

/*DomNode DomNode::select(const QString& selector) {
	//if (selector.startsWith("#")) {
	//	return ownerDocument().elementById(selector.mid(1));
	//}
	return DomNode();
}*/

DomNode DomNode::operator[](const QString& name) {
	return node->get(name);
}

DomNode DomNode::operator[](unsigned index) {
	DomNodeList list = all();
	if (index>=list.size()) return DomNode();
	return list[index];
}

DomAttributes DomNode::attributes() {
	return DomAttributes(node->asQDomNode());
}

DomAttribute DomNode::attribute(const QString& name, const QString& defaultValue) {
	return DomAttribute(node->asQDomNode(), name, defaultValue);
}

void DomNode::setAttribute(const QString& name, const QString& value) {
	attribute(name) = value;
}

void DomNode::removeAttribute(const QString& name) {
	attribute(name).remove();
}

bool DomNode::hasAttribute(const QString& name) {
	return node->asQDomNode().toElement().hasAttribute(name);
}

void DomNode::addClass(const QString& name) {
	DomAttribute attr = attribute("class", "");
	QStringList classes = attr.value().split(QRegExp("\\s+"), QString::SkipEmptyParts);
	if (classes.contains(name)) return;
	classes << name;
	attr = classes.join(" ");
}

void DomNode::removeClass(const QString& name) {
	DomAttribute attr = attribute("class", "");
	QStringList classes = attr.value().split(QRegExp("\\s+"), QString::SkipEmptyParts);
	if (!classes.contains(name)) return;
	classes.removeAll(name);
	attr = classes.join(" ");
}

bool DomNode::hasClass(const QString& name) {
	return hasAttribute("class") && attribute("class", "").value().split(QRegExp("\\s+"), QString::SkipEmptyParts).contains(name);
}

void DomNode::setId(const QString& value) {
	id() = value;
}

DomAttribute DomNode::id() {
	return attribute("id", "");
}

QString DomNode::getId() {
	return hasId() ? id().value() : QString();
}

bool DomNode::hasId() {
	return hasAttribute("id");
}

void DomNode::removeId() {
	removeAttribute("id");
}

QString DomNode::tagName() {
	return node->asQDomNode().toElement().tagName();
}

void DomNode::setTagName(const QString& name) {
	node->asQDomNode().toElement().setTagName(name);
}

DomNode DomNode::previous() {
	return node->asQDomNode().previousSibling();
}

DomNode DomNode::next() {
	return node->asQDomNode().nextSibling();
}

DomNode DomNode::previousElement() {
	return node->asQDomNode().previousSiblingElement();
}

DomNode DomNode::nextElement() {
	return node->asQDomNode().nextSiblingElement();
}

DomNode DomNode::prepend(DomNode otherNode) {
	return node->prepend(otherNode.node.data());
}

DomNode DomNode::append(DomNode otherNode) {
	return node->append(otherNode.node.data());
}

DomNode DomNode::prependChild(DomNode childNode) {
	return node->prependChild(childNode.node.data());
}

DomNode DomNode::appendChild(DomNode childNode) {
	return node->appendChild(childNode.node.data());
}

DomNode DomNode::operator=(DomNode otherNode) {
	return replaceWith(otherNode);
}

DomNode DomNode::replaceWith(DomNode otherNode) {
	return node->replaceWith(otherNode.node.data());
}

void DomNode::removeChildren() {
	for (DomNode child: children()) child.remove();
}

void DomNode::replaceChildren(DomNodeList newChildren) {
	removeChildren();
	for (DomNode newChild: newChildren) appendChild(newChild);
}

void DomNode::importChildrenFrom(DomNode otherNode) {
	replaceChildren(otherNode.children());
	otherNode.removeChildren();
}

DomNode DomNode::clone(bool deep) {
	return node->asQDomNode().cloneNode(deep);
}

void DomNode::remove() {
	node->remove();
}

void DomNode::setRaw(const QString& rawXml) {
	replaceWith(createXml(rawXml));
}

RawXml DomNode::raw() {
	return RawXml(*this);
}

DomNode DomNode::root() {
	return ownerDocument().documentElement();
}

DomNode DomNode::parent() {
	return node->parent();
}

DomNodeList DomNode::all() {
	return DomNodeList::convert(node->all());
}

DomNodeList DomNode::children() {
	return DomNodeList::convert(node->children());
}

DomNode DomNode::byId(const QString& id, bool global) {
	return global ? root().findById(id) : findById(id);
}

DomNode DomNode::findById(const QString& id) {
	if (getId()==id) return *this;
	
	for (DomNode child: children()) {
		DomNode n = child.findById(id);
		if (!n.isNull()) return n;
	}
	
	return DomNode();
}

void DomNode::setMissBehavior(MissBehavior missBehavior) {
	node->setMissBehavior(missBehavior);
}

bool DomNode::isNew() {
	return node->isNew();
}

bool DomNode::isNull() {
	return node->isNull();
}


