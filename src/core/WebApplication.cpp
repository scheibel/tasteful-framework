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

#include <WebApplication>

#include <internal/Database>
#include <internal/FrontController>
#include <QString>
#include <QFileInfo>
#include <QStringList>
#include <Logger>

using namespace internal;

WebApplication::WebApplication(int& argc, char** argv) : app(argc, argv) {
	rootDir = app.applicationDirPath();
	frontController = new FrontController();
	QFile* logFile = new QFile("log.txt");
	logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
	Logger::setLogDevice(logFile);
}

WebApplication::~WebApplication() {
	for (HttpServer* server: servers) {
		delete server;
	}
	delete frontController;
}

int WebApplication::run() {
	return app.exec();
}

QStringList WebApplication::arguments() {
	static QStringList _arguments = app.arguments();
	return _arguments;
}

QString WebApplication::getPath(const QString& dir) {
	return QDir::isRelativePath(dir) ? rootDir.filePath(dir) : dir;
}

void WebApplication::addPublicDirectory(const QString& dir) {
	QDir::addSearchPath("public", getPath(dir));
}

void WebApplication::addResourceDirectory(const QString& dir) {
	QDir::addSearchPath("resources", getPath(dir));
}

void WebApplication::addPublicDirectories(QStringList dirs) {
	for (QString& dir: dirs) addPublicDirectory(dir);
}

void WebApplication::addResourceDirectories(QStringList dirs) {
	for (QString& dir: dirs) addResourceDirectory(dir);
}

void WebApplication::addPublicDirectories() {
	// break condition for recursive template, no implementation
}

void WebApplication::addResourceDirectories() {
	// break condition for recursive template, no implementation
}

void WebApplication::addServer(const ServerConfig& serverConfig) {
	QString host = serverConfig.host;
	unsigned port = serverConfig.port;
	QHostAddress address = QHostAddress::Any;
	if (host=="localhost") {
		address = QHostAddress::LocalHost;
	} else if (!host.isEmpty()) {
		address = QHostAddress(host);
	}
	if (!serverConfig.certificate.isNull() && !serverConfig.privateKey.isNull()) {
		addSecureServer(address, port, getPath(serverConfig.certificate), getPath(serverConfig.privateKey));
	} else {
		addServer(address, port);
	}
}

void WebApplication::addServer(const QHostAddress& address, unsigned port) {
	HttpServer* server = new HttpServer(FrameworkEntryPoint(frontController));
	server->listen(address, port);
	servers << server;
}

void WebApplication::addSecureServer(const QHostAddress& address, unsigned port, const QString& certificateFile, const QString& privateKeyFile) {
	QFile certFile(certificateFile);
	if (!certFile.open(QIODevice::ReadOnly)) {
		throw QString("Cannot open file: "+certificateFile);
	}
	QSslCertificate certificate(certFile.readAll(), QSsl::Pem);
	certFile.close();
	QFile keyFile(privateKeyFile);
	if (!keyFile.open(QIODevice::ReadOnly)) {
		throw QString("Cannot open file: "+privateKeyFile);
	}
	QSslKey privateKey(keyFile.readAll(), QSsl::Rsa);
	keyFile.close();
	addSecureServer(address, port, certificate, privateKey);
}

void WebApplication::addSecureServer(const QHostAddress& address, unsigned port, QSslCertificate certificate, QSslKey privateKey) {
	HttpsServer* server = new HttpsServer(certificate, privateKey, FrameworkEntryPoint(frontController));
	server->listen(address, port);
	servers << server;
}

void WebApplication::addMySqlDatabase(const QString& hostName, const QString& databaseName, const QString& userName, const QString& password, const QString& id) {
	addDatabase("QMYSQL", hostName, databaseName, userName, password, id);
}

void WebApplication::addSqliteDatabase(const QString& fileName, const QString& id) {
	addDatabase("QSQLITE", QString(), fileName, QString(), QString(), id);
}

void WebApplication::addDatabase(const QString& databaseType, const QString& hostName, const QString& databaseName, const QString& userName, const QString& password, const QString& id) {
	addDatabase({ databaseType, hostName, databaseName, userName, password, id });
}

void WebApplication::addDatabase(const DatabaseConfig& dbConfig) {
	Database::add(dbConfig);
}

void WebApplication::setUpFromConfig(const QString& configFile) {
	setUpFromConfig(WebAppConfig::fromFile(configFile));
}

void WebApplication::setUpFromConfig(const WebAppConfig& config) {
	rootDir = config.rootDir;
	TcpServer::setNumThreads(config.threadCount);
	
	addResourceDirectories(config.resourceDirs);
	addPublicDirectories(config.publicDirs);
	
	for (const ServerConfig& serverConfig: config.servers) {
		addServer(serverConfig);
	}
	
	for (const DatabaseConfig& dbConfig: config.databases) {
		addDatabase(dbConfig);
	}
}
