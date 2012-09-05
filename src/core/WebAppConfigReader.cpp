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

#include <internal/WebAppConfigReader>

#include <QXmlSimpleReader>
#include <QFileInfo>

#include<QDebug>

using namespace internal;

WebAppConfigReader::WebAppConfigReader(const QString& filename) : filename(filename) {
}

QString WebAppConfigReader::getFilename() const {
	return filename;
}

WebAppConfig WebAppConfigReader::parse() {
	config = WebAppConfig();
	config.rootDir = QFileInfo(filename).path();
	
	QXmlSimpleReader reader;
	SignalXmlContentHandler handler;
	QFile file(filename);
	QXmlInputSource source(&file);
	
	connect(
		&handler, SIGNAL(elementStart(const QString&, const QString&, const QString&, const QXmlAttributes&)),
		this, SLOT(startElement(const QString&, const QString&, const QString&, const QXmlAttributes&))
	);
	connect(
		&handler, SIGNAL(elementEnd(const QString&, const QString&, const QString&)),
		this, SLOT(endElement(const QString&, const QString&, const QString&))
	);
	connect(
		&handler, SIGNAL(charactersRead(const QString&)),
		this, SLOT(characters(const QString&))
	);
	
	reader.setContentHandler(&handler);
	reader.parse(&source);
	
	return config;
}

void WebAppConfigReader::startElement(const QString& namespaceURI, const QString& localName, const QString& qName, const QXmlAttributes& atts) {
	element = localName;
	pathElements << element;
	path = pathElements.join("/");
	
	if (path=="application/server") {
		config.servers << ServerConfig();
	} else if (path=="application/database") {
		config.databases << DatabaseConfig();
	}
}

void WebAppConfigReader::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
	pathElements.removeLast();
	path = pathElements.join("/");
	element = pathElements.isEmpty() ? QString() : pathElements.last();
}

void WebAppConfigReader::characters(const QString& ch) {
	if (path.startsWith("application/server/")) {
		handleServer(ch);
	} else if (path.startsWith("application/database/")) {
		handleDatabase(ch);
	} else if (path.startsWith("application/directories/")) {
		handleDirectories(ch);
	} else if (path.startsWith("application/")) {
		handleApplication(ch);
	}
}

void WebAppConfigReader::handleApplication(const QString& ch) {
	if (pathElements.size()!=2) return;
	if (element=="name") {
		config.name = ch;
	} else if (element=="threadcount") {
		config.threadCount = ch.toInt();
	}
}

void WebAppConfigReader::handleDirectories(const QString& ch) {
	if (pathElements.size()!=3) return;
	if (element=="public") {
		config.publicDirs << ch;
	} else if (element=="resource") {
		config.resourceDirs << ch;
	}
}

void WebAppConfigReader::handleServer(const QString& ch) {
	if (pathElements.size()!=3) return;
	ServerConfig& serverConfig = config.servers.last();
	if (element=="host") {
		serverConfig.host = ch;
	} else if (element=="port") {
		serverConfig.port = ch.toUInt();
	} else if (element=="certificate") {
		serverConfig.certificate = ch;
	} else if (element=="privatekey") {
		serverConfig.privateKey = ch;
	}
}

void WebAppConfigReader::handleDatabase(const QString& ch) {
	if (pathElements.size()!=3) return;
	DatabaseConfig& dbConfig = config.databases.last();
	if (element=="type") {
		dbConfig.type = ch;
	} else if (element=="host") {
		dbConfig.host = ch;
	} else if (element=="name") {
		dbConfig.name = ch;
	} else if (element=="user") {
		dbConfig.user = ch;
	} else if (element=="password") {
		dbConfig.password = ch;
	} else if (element=="id") {
		dbConfig.id = ch;
	}
}

