/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012-2014 Lux, Scheibel
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

#include <tastefulframework/DomNode.h>

#include <QStringList>
#include <QRegExp>

#include <tastefulframework/DomHelper.h>

namespace tastefulframework {

DomNode::DomNode()
{
}

DomNode::DomNode(const QDomNode & node)
    : m_node(node)
{
}

DomNode::DomNode(const QString & text)
    : m_node(QDomNodeCreator::create(text))
{
}

DomNode::DomNode(const char * text)
    : m_node(QDomNodeCreator::create(text))
{
}

DomNode::DomNode(const NodeCreator & nodeCreator)
    : m_node(QDomNodeCreator::create(nodeCreator))
{
}

DomNode::DomNode(const NodeCreatorPlaceholder & nodeCreatorPlaceholder)
    : m_node(QDomNodeCreator::create(nodeCreatorPlaceholder()))
{
}

DomNode::DomNode(const DomNodeProducer & nodeProducer)
    : m_node(nodeProducer.toDomNode().m_node)
{
}

DomNode::operator QDomNode() const
{
    return asQDomNode();
}

QDomNode DomNode::asQDomNode() const
{
    return m_node;
}

QDomDocument DomNode::document() const
{
    return m_node.ownerDocument();
}

void DomNode::writeOnStream(QTextStream & stream) const
{
    stream << m_node;
}

DomNodeList DomNode::operator[](const QString & selector) const
{
    return find(selector);
}

DomNodeList DomNode::find(const QString & selector) const
{
    DomNodeList list;

    if (!isElement())
    {
        return list;
    }
    QDomNodeList childNodes = m_node.toElement().childNodes();
    for (int i = 0;i<childNodes.size();++i)
    {
        QDomElement child = childNodes.at(i).toElement();
        if (child.isNull())
        {
            continue;
        }
        if (child.tagName()==selector)
        {
            list << child;
        }
    }

    return list;
}

DomNode DomNode::first(const QString & selector) const
{
    if (!isElement())
    {
        return DomNode();
    }

    QDomNodeList childNodes = m_node.toElement().childNodes();
    for (int i = 0;i<childNodes.size();++i)
    {
        QDomElement child = childNodes.at(i).toElement();
        if (child.isNull())
        {
            continue;
        }
        if (child.tagName()==selector)
        {
            return child;
        }
    }

    return DomNode();
}

DomAttributes DomNode::attributes()
{
    return DomAttributes(m_node);
}

const DomAttributes DomNode::attributes() const
{
    return DomAttributes(m_node);
}

DomAttribute DomNode::attribute(const QString & name, const QString & defaultValue)
{
    return DomAttribute(m_node, name, defaultValue);
}

const DomAttribute DomNode::attribute(const QString & name, const QString & defaultValue) const
{
    return DomAttribute(m_node, name, defaultValue, false);
}

QString DomNode::getAttribute(const QString & name) const
{
    return attribute(name).value();
}

DomAttribute DomNode::operator()(const QString & name, const QString & defaultValue)
{
    return attribute(name, defaultValue);
}

DomAttribute DomNode::operator()(const QString & name, const QString & defaultValue) const
{
    return attribute(name, defaultValue);
}

void DomNode::setAttribute(const QString & name, const QString & value)
{
    attribute(name) = value;
}

void DomNode::removeAttribute(const QString & name)
{
    attribute(name).remove();
}

bool DomNode::hasAttribute(const QString & name) const
{
    return m_node.toElement().hasAttribute(name);
}

void DomNode::addClass(const QString & name)
{
    DomAttribute attr = attribute("class", "");
    QStringList classes = attr.value().split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (classes.contains(name))
    {
        return;
    }
    classes << name;
    attr = classes.join(" ");
}

void DomNode::removeClass(const QString & name)
{
    DomAttribute attr = attribute("class", "");
    QStringList classes = attr.value().split(QRegExp("\\s+"), QString::SkipEmptyParts);

    if (!classes.contains(name))
    {
        return;
    }
    classes.removeAll(name);
    attr = classes.join(" ");
}

bool DomNode::hasClass(const QString & name) const
{
    return hasAttribute("class") && attribute("class", "").value().split(QRegExp("\\s+"), QString::SkipEmptyParts).contains(name);
}

void DomNode::setId(const QString & value)
{
    id() = value;
}

DomAttribute DomNode::id()
{
    return attribute("id", "");
}

const DomAttribute DomNode::id() const
{
    return attribute("id", "");
}

QString DomNode::getId() const
{
    return hasId() ? id().value() : QString();
}

bool DomNode::hasId() const
{
    return hasAttribute("id");
}

void DomNode::removeId()
{
    removeAttribute("id");
}

QString DomNode::tagName() const
{
    return m_node.toElement().tagName();
}

void DomNode::setTagName(const QString & name)
{
    m_node.toElement().setTagName(name);
}

DomNode DomNode::previous() const
{
    return m_node.previousSibling();
}

DomNode DomNode::next() const
{
    return m_node.nextSibling();
}

DomNode DomNode::previousElement() const
{
    return m_node.previousSiblingElement();
}

DomNode DomNode::nextElement()  const
{
    return m_node.nextSiblingElement();
}

DomNode &DomNode::prepend(const DomNode & otherNode)
{
    if (isNull())
    {
        return *this;
    }
    // importNode()?
    QDomNode newNode = document().importNode(otherNode.asQDomNode(), true);
    m_node.parentNode().insertBefore(newNode, m_node);

    return *this;
}

DomNode &DomNode::append(const DomNode & otherNode)
{
    if (isNull())
    {
        return *this;
    }
    QDomNode newNode = document().importNode(otherNode.asQDomNode(), true);
    m_node.parentNode().insertAfter(newNode, m_node);

    return *this;
}

DomNode &DomNode::prependChild(const DomNode & childNode)
{
    if (isNull())
    {
        return *this;
    }
    QDomNode newNode = document().importNode(childNode.asQDomNode(), true);
    m_node.insertBefore(newNode, m_node.firstChild());

    return *this;
}

DomNode &DomNode::appendChild(const DomNode & childNode)
{
    if (isNull())
    {
        return *this;
    }
    QDomNode newNode = document().importNode(childNode.asQDomNode(), true);
    m_node.appendChild(newNode);

    return *this;
}

DomNode &DomNode::operator<<(const DomNode & childNode)
{
    appendChild(childNode);

    return *this;
}

DomNode &DomNode::operator=(const DomNode & otherNode)
{
    replaceWith(otherNode);

    return *this;
}

DomNode &DomNode::replaceWith(const DomNode & otherNode)
{
    if (isNull())
    {
        return *this;
    }
    QDomNode newNode = document().importNode(otherNode.asQDomNode(), true);
    m_node.parentNode().replaceChild(newNode, m_node);
    m_node = newNode;

    return *this;
}

void DomNode::removeChildren()
{
    for (DomNode & child : children())
    {
        child.remove();
    }
}

void DomNode::replaceChildren(const DomNodeList & newChildren)
{
    removeChildren();
    appendChildren(newChildren);
}

void DomNode::replaceChildren(const DomNode & newChild)
{
    replaceChildren(DomNodeList { newChild });
}

void DomNode::appendChildren(const DomNodeList & newChildren)
{
    for (const DomNode & newChild : newChildren)
    {
        appendChild(newChild);
    }
}

void DomNode::transferChildrenFrom(DomNode otherNode, bool removeOldChildren)
{
    if (removeOldChildren)
    {
        removeChildren();
    }
    appendChildren(otherNode.children());
    otherNode.removeChildren();
}

DomNode DomNode::clone(bool deep) const
{
    if (isNull())
    {
        return *this;
    }

    return m_node.cloneNode(deep);
}

DomNode DomNode::remove()
{
    m_node.parentNode().removeChild(m_node);
    QDomNode oldNode = m_node;
    m_node = QDomNode();

    return oldNode;
}

void DomNode::setRaw(const QString & rawXml)
{
    if (isNull())
    {
        return;
    }
    QDomDocument doc;
    doc.setContent(rawXml);
    replaceWith(document().importNode(doc.documentElement(), true));
}

RawXml DomNode::raw()
{
    return RawXml(*this);
}

InnerXml DomNode::inner()
{
    return InnerXml(*this);
}

void DomNode::setInner(const DomNode & otherNode)
{
    replaceChildren(otherNode);
}

void DomNode::setInner(const DomNodeList & nodeList)
{
    replaceChildren(nodeList);
}

DomNode DomNode::root() const
{
    if (isNull())
    {
        return *this;
    }

    return document().documentElement();
}

DomNode DomNode::parent() const
{
    if (isNull())
    {
        return *this;
    }
    QDomNode parentNode = m_node.parentNode();
    if (parentNode.isNull())
    {
        return DomNode();
    }

    return parentNode;
}

DomNode DomNode::firstChild() const
{
    if (isNull())
    {
        return *this;
    }
    QDomNode childNode = m_node.firstChild();
    if (childNode.isNull())
    {
        return DomNode();
    }

    return childNode;
}

bool DomNode::operator==(const DomNode & otherNode)
{
    return m_node==otherNode.m_node;
}

DomNodeList DomNode::children() const
{
    DomNodeList list;

    if (!isElement())
    {
        return list;
    }
    QDomNodeList childNodes = m_node.toElement().childNodes();
    for (int i = 0;i<childNodes.size();++i)
    {
        list << childNodes.at(i);
    }

    return list;
}

DomNode DomNode::child(int index) const
{
    DomNodeList list = children();

    if (index>=list.size())
    {
        return DomNode();
    }

    return list[index];
}

DomNode DomNode::byId(const QString & id, bool global) const
{
    return global ? root().findById(id) : findById(id);
}

DomNode DomNode::findById(const QString & id) const
{
    if (getId()==id)
    {
        return *this;
    }

    for (DomNode child : children())
    {
        DomNode n = child.findById(id);
        if (!n.isNull())
        {
            return n;
        }
    }

    return DomNode();
}

bool DomNode::isNull() const
{
    return m_node.isNull();
}

bool DomNode::isElement() const
{
    return m_node.isElement();
}

bool DomNode::isText() const
{
    return m_node.isText();
}

// ---------------------------------------

QDomNodeCreator QDomNodeCreator::s_instance;
RawXml::RawXml(DomNode & node)
    : m_node(node)
{
}

const QString &RawXml::operator=(const QString & rawXml)
{
    m_node.setRaw(rawXml);

    return rawXml;
}

void RawXml::writeOnStream(QTextStream & stream) const
{
    m_node.writeOnStream(stream);
}

InnerXml::InnerXml(DomNode & node)
    : m_node(node)
{
}

const DomNode &InnerXml::operator=(const DomNode & otherNode)
{
    m_node.replaceChildren(DomNodeList { otherNode });

    return otherNode;
}

const DomNodeList &InnerXml::operator=(const DomNodeList & nodeList)
{
    m_node.replaceChildren(nodeList);

    return nodeList;
}

const DomNodeList &InnerXml::operator=(const std::initializer_list<DomNode> & initializerList)
{
    return *this = DomNodeList(initializerList);
}

void InnerXml::writeOnStream(QTextStream & stream) const
{
    m_node.children().writeOnStream(stream);
}

DomAttribute::DomAttribute()
{
}

DomAttribute::DomAttribute(const QDomNode & node, const QString & name, const QString & defaultValue, bool create)
{
    QDomElement element = node.toElement();

    if (!element.isNull())
    {
        m_attr = element.attributeNode(name);
        if (m_attr.isNull())
        {
            m_attr = node.ownerDocument().createAttribute(name);
            m_attr.setValue(defaultValue.isNull() ? name : defaultValue);
            if (create)
            {
                element.setAttributeNode(m_attr);
            }
        }
    }
}

QString DomAttribute::name() const
{
    return m_attr.name();
}

QString DomAttribute::value() const
{
    return m_attr.value();
}

QDomAttr DomAttribute::asQDomAttr() const
{
    return m_attr;
}

void DomAttribute::remove()
{
    m_attr.ownerElement().removeAttributeNode(m_attr);
}

const QVariant &DomAttribute::operator=(const QVariant & value)
{
    m_attr.setValue(value.isNull() ? m_attr.name() : value.toString());

    return value;
}

bool DomAttribute::operator==(const DomAttribute & otherAttribute) const
{
    return name() == otherAttribute.name() && value() == otherAttribute.value();
}

void DomAttribute::writeOnStream(QTextStream & stream) const
{
    stream << (name() + "=" + value());
}

DomAttributes::DomAttributes(const QDomNode & node)
    : m_node(node)
{
    QDomNamedNodeMap map = node.attributes();

    for (int i = 0;i<map.count();++i)
    {
        QDomAttr attr = map.item(i).toAttr();
        if (attr.isNull())
        {
            continue;
        }
        m_attributes[attr.name()] = DomAttribute(node, attr.name());
    }
}

int DomAttributes::size() const
{
    return m_attributes.size();
}

QHash<QString, DomAttribute>::iterator DomAttributes::begin()
{
    return m_attributes.begin();
}

QHash<QString, DomAttribute>::iterator DomAttributes::end()
{
    return m_attributes.end();
}

QHash<QString, DomAttribute>::const_iterator DomAttributes::begin() const
{
    return m_attributes.begin();
}

QHash<QString, DomAttribute>::const_iterator DomAttributes::end() const
{
    return m_attributes.end();
}

void DomAttributes::remove(const QString & name)
{
    if (m_attributes.contains(name))
    {
        DomAttribute attribute = m_attributes[name];
        attribute.remove();
        m_attributes.remove(name);
    }
}

DomAttribute &DomAttributes::operator[](const QString & name)
{
    if (!m_attributes.contains(name))
    {
        m_attributes.insert(name, DomAttribute(m_node, name));
    }

    return m_attributes[name];
}

DomAttribute DomAttributes::operator[](const QString & name) const
{
    if (!m_attributes.contains(name))
    {
        return DomAttribute();
    }

    return m_attributes[name];
}

bool DomAttributes::operator==(const DomAttributes & otherAttributes) const
{
    return m_attributes == otherAttributes.m_attributes;
}

void DomAttributes::writeOnStream(QTextStream & stream) const
{
    QList<QString> attributeNames = m_attributes.keys();
    for (int i = 0;i<attributeNames.size();++i)
    {
        if (i>0)
        {
            stream << " ";
        }
        stream << m_attributes[attributeNames[i]].toString();
    }
}

DomNodeList::DomNodeList()
{
}

DomNodeList::DomNodeList(const std::initializer_list<DomNode> & list)
{
    for (const DomNode & node : list)
    {
        append(node);
    }
}

void DomNodeList::writeOnStream(QTextStream & stream) const
{
    for (const DomNode & node : * this)
    {
        stream << node.toString() << endl;
    }
}

} // namespace tastefulframework
