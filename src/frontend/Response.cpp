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

#include <Response>
#include <QFileInfo>

MimeDatabase Response::mimeDatabase;

Response::Response(unsigned statusCode) {
	setStatusCode(statusCode);
	setHeader(http::Server, "tasteful server");
}

HttpResponse& Response::asHttpResponse() {
	return *(HttpResponse*)this;
}

void Response::setMimeType(QString mimeType) {
	contentType.setTypeAndSubtype(mimeType);
}

void Response::setMimeTypeForFileName(QString filename) {
	setMimeType(mimeDatabase.getMimeTypeFor(filename));
}

void Response::setSession(AbstractSession* session) {
	setCookie("sessionId", session->getIdentifier()).setPath("/");
}

Response& Response::asDownload(QString name) {
	setMimeTypeForFileName(name);
	setHeader(http::ContentDisposition,"attachment;filename=\""+name+"\"");
	return *this;
}
 
 Response Response::notFound() {
	return Response(http::NotFound);
}

Response Response::redirect(QString url) {
	Response response(http::Found);
	response.setHeader(http::Location, url);
	return response;
}

Response Response::redirectPermanently(QString url) {
	Response response(http::MovedPermanently);
	response.setHeader(http::Location, url);
	return response;
}

Response Response::forContent(QString content, unsigned statusCode) {
	Response response(statusCode);
	response.setContent(content.toUtf8());
	return response;
}

Response Response::forContent(QByteArray content, unsigned statusCode) {
	Response response(statusCode);
	response.setContent(content);
	return response;
}

Response Response::forFile(QFile& file) {
	if (!file.open(QIODevice::ReadOnly)) {
		return Response::notFound();
	}
	QByteArray content = file.readAll().data();
	file.close();
	
	Response response = Response::forContent(content);
	response.setMimeTypeForFileName(file.fileName());
	return response;
}

 Response Response::download(QFile& file, QString name) {
	Response response = Response::forFile(file);
	if (name.isNull()) name = QFileInfo(file).fileName();
	return response.asDownload(name);
}

Response Response::download(QByteArray content, QString name) {
	return Response::forContent(content).asDownload(name);
}

Response Response::accessDenied() {
	return Response(http::Forbidden);
}

