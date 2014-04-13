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

#include <QXmlContentHandler>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

class TASTEFULFRAMEWORK_API SignalXmlContentHandler : public QObject, public QXmlContentHandler
{
    Q_OBJECT

signals:
    void charactersRead(const QString & ch);
    void documentEnd();
    void elementEnd(const QString & namespaceURI, const QString & localName, const QString & qName);
    void prefixMappingEnd(const QString & prefix);
    void ignorableWhitespaceRead(const QString & ch);
    void processingInstructionRead(const QString & target, const QString & data);
    void entitySkipped(const QString & name);
    void documentStart();
    void elementStart(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);
    void prefixMappingStart(const QString & prefix, const QString & uri);

public:
    virtual bool characters(const QString & ch);
    virtual bool endDocument();
    virtual bool endElement(const QString & namespaceURI, const QString & localName, const QString & qName);
    virtual bool endPrefixMapping(const QString & prefix);
    virtual QString errorString() const;
    virtual bool ignorableWhitespace(const QString & ch);
    virtual bool processingInstruction(const QString & target, const QString & data);
    virtual void setDocumentLocator(QXmlLocator * locator);
    virtual bool skippedEntity(const QString & name);
    virtual bool startDocument();
    virtual bool startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts);
    virtual bool startPrefixMapping(const QString & prefix, const QString & uri);
};

} // namespace tastefulframework
