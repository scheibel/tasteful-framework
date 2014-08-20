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

#include <tasteful-framework/SignalXmlContentHandler.h>

namespace tastefulframework {

bool SignalXmlContentHandler::characters(const QString & ch)
{
    emit(charactersRead(ch));

    return true;
}

bool SignalXmlContentHandler::endDocument()
{
    emit(documentEnd());

    return true;
}

bool SignalXmlContentHandler::endElement(const QString & namespaceURI, const QString & localName, const QString & qName)
{
    emit(elementEnd(namespaceURI, localName, qName));

    return true;
}

bool SignalXmlContentHandler::endPrefixMapping(const QString & prefix)
{
    emit(prefixMappingEnd(prefix));

    return true;
}

QString SignalXmlContentHandler::errorString() const
{
    return QString();
}

bool SignalXmlContentHandler::ignorableWhitespace(const QString & ch)
{
    emit(ignorableWhitespaceRead(ch));

    return true;
}

bool SignalXmlContentHandler::processingInstruction(const QString & target, const QString & data)
{
    emit(processingInstructionRead(target, data));

    return true;
}

void SignalXmlContentHandler::setDocumentLocator(QXmlLocator * /*locator*/)
{
}

bool SignalXmlContentHandler::skippedEntity(const QString & name)
{
    emit(entitySkipped(name));

    return true;
}

bool SignalXmlContentHandler::startDocument()
{
    emit(documentStart());

    return true;
}

bool SignalXmlContentHandler::startElement(const QString & namespaceURI, const QString & localName, const QString & qName, const QXmlAttributes & atts)
{
    emit(elementStart(namespaceURI, localName, qName, atts));

    return true;
}

bool SignalXmlContentHandler::startPrefixMapping(const QString & /*prefix*/, const QString & /*uri*/)
{
    return true;
}

} // namespace tastefulframework
