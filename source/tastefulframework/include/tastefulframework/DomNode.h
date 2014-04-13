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

#pragma once

#include <functional>
#include <QString>
#include <QDomNode>
#include <QList>
#include <QHash>
#include <tastefulframework/DomHelper.h>
#include <QTextStream>
#include <QSharedPointer>
#include <initializer_list>
#include <tastefulframework/StringConvertible.h>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class NodeCreator;
class DomNodeList;
class DomAttribute;
class DomAttributes;
class RawXml;
class InnerXml;
class DomNodeProducer;

class TASTEFULFRAMEWORK_API DomNode : public StringConvertible
{
public:
    DomNode();
    DomNode(const DomNode & node) = default;
    DomNode(const QDomNode & node);
    DomNode(const QString & text);
    DomNode(const char * text);
    DomNode(const NodeCreator & nodeCreator);
    DomNode(const NodeCreatorPlaceholder & nodeCreatorPlaceholder);
    DomNode(const DomNodeProducer & nodeProducer);

    virtual void writeOnStream(QTextStream & stream) const;

    QDomNode asQDomNode() const;
    operator QDomNode() const;

    bool isNull() const;
    bool isElement() const;
    bool isText() const;

    QDomDocument document() const;
    DomNode root() const;
    DomNode parent() const;
    DomNode firstChild() const;

    DomNode previous() const;
    DomNode next() const;
    DomNode previousElement() const;
    DomNode nextElement() const;

    QString tagName() const;
    void setTagName(const QString & name);

    bool operator==(const DomNode & otherNode);

    DomNodeList operator[](const QString & selector) const;
    DomNodeList find(const QString & selector) const;
    DomNode first(const QString & selector) const;
    DomNodeList children() const;
    DomNode child(int index) const;

    DomNode byId(const QString & id, bool global = false) const;

    DomAttributes attributes();
    const DomAttributes attributes() const;
    DomAttribute attribute(const QString & name, const QString & defaultValue = QString());
    QString getAttribute(const QString & name) const;
    const DomAttribute attribute(const QString & name, const QString & defaultValue = QString()) const;
    DomAttribute operator()(const QString & name, const QString & defaultValue = QString());
    DomAttribute operator()(const QString & name, const QString & defaultValue = QString()) const;
    void setAttribute(const QString & name, const QString & value = QString());
    void removeAttribute(const QString & name);
    bool hasAttribute(const QString & name) const;

    void addClass(const QString & name);
    void removeClass(const QString & name);
    bool hasClass(const QString & name) const;

    void setId(const QString & value);
    DomAttribute id();
    const DomAttribute id() const;
    QString getId() const;
    bool hasId() const;
    void removeId();

    void removeChildren();
    void replaceChildren(const DomNodeList & newChildren);
    void replaceChildren(const DomNode & newChild);
    void appendChildren(const DomNodeList & newChildren);
    void transferChildrenFrom(DomNode otherNode, bool removeOldChildren = false);

    template <typename... T>
    void replaceChildren(T... newChildren)
    {
        removeChildren();
        appendChildren(newChildren...);
    }

    void appendChildren()
    {
    }

    template <typename T, typename... Rest>
    void appendChildren(T child, Rest... rest)
    {
        appendChild(child);
        appendChildren(rest...);
    }

    DomNode clone(bool deep = true) const;

    DomNode&prepend(const DomNode & otherNode);
    DomNode&append(const DomNode & otherNode);
    DomNode&prependChild(const DomNode & childNode);
    DomNode&appendChild(const DomNode & childNode);
    DomNode &operator<<(const DomNode & childNode);
    DomNode &operator=(const DomNode & otherNode);
    DomNode&replaceWith(const DomNode & otherNode);
    DomNode remove();

    RawXml raw();
    void setRaw(const QString & rawXml);
    InnerXml inner();
    void setInner(const DomNode & otherNode);
    void setInner(const DomNodeList & nodeList);

protected:
    QDomNode node;

    DomNode findById(const QString & id) const;
};

class TASTEFULFRAMEWORK_API RawXml : public StringConvertible
{
public:
    RawXml(DomNode & node);

    const QString &operator=(const QString & rawXml);
    virtual void writeOnStream(QTextStream & stream) const;

private:
    DomNode & node;
};

class DomNodeList;

class TASTEFULFRAMEWORK_API InnerXml : public StringConvertible
{
public:
    InnerXml(DomNode & node);

    const DomNode &operator=(const DomNode & otherNode);
    const DomNodeList &operator=(const DomNodeList & nodeList);
    const DomNodeList &operator=(const std::initializer_list<DomNode> & initializerList);
    virtual void writeOnStream(QTextStream & stream) const;

private:
    DomNode & node;
};

class TASTEFULFRAMEWORK_API DomAttribute : public StringConvertible
{
public:
    DomAttribute();
    DomAttribute(const QDomNode & node, const QString & name, const QString & defaultValue = QString(), bool create = true);

    QString name() const;
    QString value() const;

    void remove();

    QDomAttr asQDomAttr() const;
    const QVariant &operator=(const QVariant & value);
    bool operator==(const DomAttribute & otherAttribute) const;

    virtual void writeOnStream(QTextStream & stream) const;

private:
    QDomAttr attr;
};

class TASTEFULFRAMEWORK_API DomAttributes : public StringConvertible
{
public:
    DomAttributes(const QDomNode & node);

    int size() const;

    QHash<QString, DomAttribute>::iterator begin();
    QHash<QString, DomAttribute>::iterator end();
    QHash<QString, DomAttribute>::const_iterator begin() const;
    QHash<QString, DomAttribute>::const_iterator end() const;

    void remove(const QString & name);

    DomAttribute &operator[](const QString & name);
    DomAttribute operator[](const QString & name) const;
    bool operator==(const DomAttributes & otherAttributes) const;

    virtual void writeOnStream(QTextStream & stream) const;

private:
    QDomNode node;
    QHash<QString, DomAttribute> attributes;
};

class TASTEFULFRAMEWORK_API DomNodeList : public QList<DomNode>, public StringConvertible
{
public:
    DomNodeList();
    DomNodeList(const std::initializer_list<DomNode> & list);

    virtual void writeOnStream(QTextStream & stream) const;
};

class TASTEFULFRAMEWORK_API DomNodeProducer
{
public:
    virtual DomNode toDomNode() const = 0;
};

class TASTEFULFRAMEWORK_API QDomNodeCreator
{
public:
    static QDomNode create(const QString & text)
    {
        return instance()._create(text);
    }

    static QDomNode create(const NodeCreator & nodeCreator)
    {
        return instance()._create(nodeCreator);
    }

    static QDomNodeCreator&instance()
    {
        return _instance;
    }

private:
    static QDomNodeCreator _instance;

    QDomNodeCreator()
    {
        emptyDocument.setContent(QString("<empty>"));
    }

    QDomDocument emptyDocument;

    QDomNode _create(const QString & text)
    {
        return emptyDocument.createTextNode(text);
    }

    QDomNode _create(const NodeCreator & nodeCreator)
    {
        return nodeCreator(emptyDocument);
    }

};

} // namespace tastefulframework
