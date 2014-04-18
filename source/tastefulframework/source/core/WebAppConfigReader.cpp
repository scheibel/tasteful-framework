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

#include <tastefulframework/WebAppConfigReader.h>

#include <QFileInfo>

#include <tastefulframework/SignalXmlContentHandler.h>

namespace tastefulframework {

WebAppConfigReader::WebAppConfigReader(const QString & filename)
    : m_filename(filename)
{
}

QString WebAppConfigReader::getFilename() const
{
    return m_filename;
}

WebAppConfig WebAppConfigReader::parse()
{
    m_config = WebAppConfig();
    m_config.rootDir = QFileInfo(m_filename).path();

    QXmlSimpleReader reader;
    SignalXmlContentHandler handler;
    QFile file(m_filename);
    QXmlInputSource source(&file);

    connect(&handler, SIGNAL(elementStart(const QString &, const QString &, const QString &, const QXmlAttributes &)), this, SLOT(startElement(const QString &, const QString &, const QString &, const QXmlAttributes &)));
    connect(&handler, SIGNAL(elementEnd(const QString &, const QString &, const QString &)), this, SLOT(endElement(const QString &, const QString &, const QString &)));
    connect(&handler, SIGNAL(charactersRead(const QString &)), this, SLOT(characters(const QString &)));

    reader.setContentHandler(&handler);
    reader.parse(&source);

    return m_config;
}

void WebAppConfigReader::startElement(const QString & /*namespaceURI*/, const QString & localName, const QString & /*qName*/, const QXmlAttributes & /*atts*/)
{
    m_element = localName;
    m_pathElements << m_element;
    m_path = m_pathElements.join("/");

    if (m_path=="application/server")
    {
        m_config.servers << ServerConfig();
    }
    else if (m_path=="application/database")
    {
        m_config.databases << DatabaseConfig();
    }
}

void WebAppConfigReader::endElement(const QString & /*namespaceURI*/, const QString & /*localName*/, const QString & /*qName*/)
{
    m_pathElements.removeLast();
    m_path = m_pathElements.join("/");
    m_element = m_pathElements.isEmpty() ? QString() : m_pathElements.last();
}

void WebAppConfigReader::characters(const QString & ch)
{
    if (m_path.startsWith("application/server/"))
    {
        handleServer(ch);
    }
    else if (m_path.startsWith("application/database/"))
    {
        handleDatabase(ch);
    }
    else if (m_path.startsWith("application/directories/"))
    {
        handleDirectories(ch);
    }
    else if (m_path.startsWith("application/"))
    {
        handleApplication(ch);
    }
}

void WebAppConfigReader::handleApplication(const QString & ch)
{
    if (m_pathElements.size()!=2)
    {
        return;
    }
    if (m_element=="name")
    {
        m_config.name = ch;
    }
    else if (m_element=="threadcount")
    {
        m_config.threadCount = ch.toInt();
    }
}

void WebAppConfigReader::handleDirectories(const QString & ch)
{
    if (m_pathElements.size()!=3)
    {
        return;
    }
    if (m_element=="public")
    {
        m_config.publicDirs << ch;
    }
    else if (m_element=="resource")
    {
        m_config.resourceDirs << ch;
    }
}

void WebAppConfigReader::handleServer(const QString & ch)
{
    if (m_pathElements.size()!=3)
    {
        return;
    }
    ServerConfig & serverConfig = m_config.servers.last();
    if (m_element=="host")
    {
        serverConfig.host = ch;
    }
    else if (m_element=="port")
    {
        serverConfig.port = ch.toUInt();
    }
    else if (m_element=="certificate")
    {
        serverConfig.certificate = ch;
    }
    else if (m_element=="privatekey")
    {
        serverConfig.privateKey = ch;
    }
}

void WebAppConfigReader::handleDatabase(const QString & ch)
{
    if (m_pathElements.size()!=3)
    {
        return;
    }
    DatabaseConfig & dbConfig = m_config.databases.last();
    if (m_element=="type")
    {
        dbConfig.type = ch;
    }
    else if (m_element=="host")
    {
        dbConfig.host = ch;
    }
    else if (m_element=="name")
    {
        dbConfig.name = ch;
    }
    else if (m_element=="user")
    {
        dbConfig.user = ch;
    }
    else if (m_element=="password")
    {
        dbConfig.password = ch;
    }
    else if (m_element=="id")
    {
        dbConfig.id = ch;
    }
}

} // namespace tastefulframework
