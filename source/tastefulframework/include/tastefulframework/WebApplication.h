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

#include <tastefulframework/WebAppConfig.h>
#include <QCoreApplication>
#include <tastefulserver/HttpServer.h>
#include <tastefulserver/HttpsServer.h>
#include <QDir>
#include <tastefulframework/FrontController.h>

#include <tastefulframework/tastefulframework_api.h>

class TASTEFULFRAMEWORK_API WebApplication {
	public:
		WebApplication(int& argc, char** argv);
		~WebApplication();

		int run() const;

		template<class SessionClass> void setSessionClass();

		QStringList arguments() const;

		void setUpFromConfig(const QString& configFile);
		void setUpFromConfig(const WebAppConfig& config);

		void addServer(const ServerConfig& serverConfig);
		void addServer(const QHostAddress& address, unsigned port);
		void addSecureServer(const QHostAddress& address, unsigned port, const QString& certificateFile, const QString& privateKeyFile);
		void addSecureServer(const QHostAddress& address, unsigned port, const QSslCertificate& certificate, const QSslKey& privateKey);

		void addMySqlDatabase(const QString& hostName, const QString& databaseName, const QString& userName, const QString& password, const QString& id=QString());
		void addSqliteDatabase(const QString& fileName, const QString& id=QString());
		void addDatabase(const QString& databaseType, const QString& hostName, const QString& databaseName, const QString& userName, const QString& password, const QString& id=QString());
		void addDatabase(const DatabaseConfig& dbConfig);

		void addPublicDirectory(const QString& dir);
		void addResourceDirectory(const QString& dir);
		void addPublicDirectories(const QStringList& dirs);
		void addResourceDirectories(const QStringList& dirs);
		template<typename T, typename... Rest>
		void addPublicDirectories(const T& dir, Rest... dirs) {
			addPublicDirectory(dir);
			addPublicDirectories(dirs...);
		}
		template<typename T, typename... Rest>
		void addResourceDirectories(const T& dir, Rest... dirs) {
			addResourceDirectory(dir);
			addResourceDirectories(dirs...);
		}
	protected:
		QString getPath(const QString& dir) const;
	private:
		QDir rootDir;
		QCoreApplication app;
        QList<tastefulserver::HttpServer*> servers;
		FrontController* frontController;

		void addPublicDirectories();
		void addResourceDirectories();

		void shutdown(int exitCode = 0);
		void stopServers();
};

template<class SessionClass>
void WebApplication::setSessionClass() {
	frontController->setSessionClass<SessionClass>();
}
