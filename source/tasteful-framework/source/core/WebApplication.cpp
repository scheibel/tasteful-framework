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

#include <tasteful-framework/WebApplication.h>

#include <QString>
#include <QFileInfo>
#include <QStringList>

#include <tasteful-server/HttpCallbackServer.h>

#include <tasteful-framework/Database.h>
#include <tasteful-framework/FrontController.h>
#include <tasteful-framework/Logger.h>
#include <tasteful-framework/FrameworkEntryPoint.h>

namespace tastefulframework {

WebApplication::WebApplication(int & argc, char ** argv)
    : m_app(argc, argv)
{
    m_rootDir = m_app.applicationDirPath();
    m_frontController = new FrontController();
}

WebApplication::~WebApplication()
{
    stopServers();
    delete m_frontController;
}

int WebApplication::run() const
{
    return m_app.exec();
}

void WebApplication::shutdown(int /*exitCode*/)
{
    stopServers();
    logger() << "shutting down...";
    QTimer::singleShot(0, &m_app, SLOT(quit()));
}

void WebApplication::stopServers()
{
    qDeleteAll(m_servers);
    m_servers.clear();
}

QStringList WebApplication::arguments() const
{
    static QStringList _arguments = m_app.arguments();

    return _arguments;
}

QString WebApplication::getPath(const QString & dir) const
{
    return QDir::isRelativePath(dir) ? m_rootDir.filePath(dir) : dir;
}

void WebApplication::addPublicDirectory(const QString & dir)
{
    QDir::addSearchPath("public", getPath(dir));
}

void WebApplication::addResourceDirectory(const QString & dir)
{
    QDir::addSearchPath("resources", getPath(dir));
}

void WebApplication::addPublicDirectories(const QStringList & dirs)
{
    for (const QString & dir : dirs)
    {
        addPublicDirectory(dir);
    }
}

void WebApplication::addResourceDirectories(const QStringList & dirs)
{
    for (const QString & dir : dirs)
    {
        addResourceDirectory(dir);
    }
}

void WebApplication::addPublicDirectories()
{
    // break condition for recursive template, no implementation
}

void WebApplication::addResourceDirectories()
{
    // break condition for recursive template, no implementation
}

void WebApplication::addServer(const ServerConfig & serverConfig)
{
    QString host = serverConfig.host;
    unsigned port = serverConfig.port;
    QHostAddress address = QHostAddress::Any;

    if (host=="localhost")
    {
        address = QHostAddress::LocalHost;
    }
    else if (!host.isEmpty())
    {
        address = QHostAddress(host);
    }
    if (!serverConfig.certificate.isNull() && !serverConfig.privateKey.isNull())
    {
        //addSecureServer(address, port, getPath(serverConfig.certificate), getPath(serverConfig.privateKey));
    }
    else
    {
        addServer(address, port);
    }
}

void WebApplication::addServer(const QHostAddress & address, unsigned port)
{
    tastefulserver::HttpServer * server = new tastefulserver::HttpCallbackServer(FrameworkEntryPoint(m_frontController));

    server->listen(address, port);
    m_servers << server;
}

/*void WebApplication::addSecureServer(const QHostAddress & address, unsigned port, const QString & certificateFile, const QString & privateKeyFile)
{
    QFile certFile(certificateFile);

    if (!certFile.open(QIODevice::ReadOnly))
    {
        logger().error() << "Cannot open file: " << certificateFile;
        logger() << "No SSL server added";
        shutdown(1);

        return;
    }
    QSslCertificate certificate(certFile.readAll(), QSsl::Pem);
    certFile.close();
    QFile keyFile(privateKeyFile);
    if (!keyFile.open(QIODevice::ReadOnly))
    {
        logger().error() << "Cannot open file: " << privateKeyFile;
        logger() << "No SSL server added";
        shutdown(1);

        return;
    }
    QSslKey privateKey(keyFile.readAll(), QSsl::Rsa);
    keyFile.close();
    addSecureServer(address, port, certificate, privateKey);
}
*/

/*void WebApplication::addSecureServer(const QHostAddress & address, unsigned port, const QSslCertificate & certificate, const QSslKey & privateKey)
{
    tastefulserver::HttpsServer * server = new tastefulserver::HttpsServer(certificate, privateKey, FrameworkEntryPoint(m_frontController));

    server->listen(address, port);
    m_servers << server;
}*/

void WebApplication::addMySqlDatabase(const QString & hostName, const QString & databaseName, const QString & userName, const QString & password, const QString & id)
{
    addDatabase("QMYSQL", hostName, databaseName, userName, password, id);
}

void WebApplication::addSqliteDatabase(const QString & fileName, const QString & id)
{
    addDatabase("QSQLITE", QString(), fileName, QString(), QString(), id);
}

void WebApplication::addDatabase(const QString & databaseType, const QString & hostName, const QString & databaseName, const QString & userName, const QString & password, const QString & id)
{
    addDatabase({ databaseType, hostName, databaseName, userName, password, id });
}

void WebApplication::addDatabase(const DatabaseConfig & dbConfig)
{
    if ((dbConfig.type == "QSQLITE") || (dbConfig.type == "sqlite"))
    {
        Database::add({ dbConfig.type, dbConfig.host, getPath(dbConfig.name), dbConfig.user, dbConfig.password, dbConfig.id });

        return;
    }

    Database::add(dbConfig);
}

void WebApplication::setUpFromConfig(const QString & configFile)
{
    if (!QFileInfo(configFile).isReadable())
    {
        logger().warning() << "Config File \"" << configFile << "\" is not readable";
        logger().warning() << "WebApplication not set up";

        return;
    }
    setUpFromConfig(WebAppConfig::fromFile(configFile));
}

void WebApplication::setUpFromConfig(const WebAppConfig & config)
{
    m_rootDir = config.rootDir;
    tastefulserver::TcpServer::setNumThreads(config.threadCount);

    addResourceDirectories(config.resourceDirs);
    addPublicDirectories(config.publicDirs);

    for (const ServerConfig & serverConfig : config.servers)
    {
        addServer(serverConfig);
    }

    for (const DatabaseConfig & dbConfig : config.databases)
    {
        addDatabase(dbConfig);
    }
}

} // namespace tastefulframework
