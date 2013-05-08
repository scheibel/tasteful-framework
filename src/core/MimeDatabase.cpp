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

#include <internal/MimeDatabase>

#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QString>
#include <QStringList>

using namespace internal;

MimeDatabase MimeDatabase::instance;

MimeDatabase::MimeDatabase() {
	loadMimeTypes();
}

void MimeDatabase::loadMimeTypes() {
	QString homeFilename = QDir::home().filePath(".mime.types");
	QString filename = "/etc/mime.types";
	
	loadMimeTypesFromFilename(filename);
	loadMimeTypesFromFilename(homeFilename);
}

void MimeDatabase::loadMimeTypesFromFilename(const QString& filename) {
	QFile file(filename);
	
	if (file.open(QIODevice::ReadOnly)) {
		while (!file.atEnd()) {
			QString line = file.readLine();
			
			if (line.isEmpty() || line.startsWith("#")) {
				continue;
			}
			
			QStringList list = line.split(QRegExp("\\s+"));
			
			if (list.size()<2) {
				continue;
			}
			
			QString mimeType = list[0];
			for (unsigned i=1; i<list.size(); ++i) {
				addMimeType(mimeType, list[i]);
			}
		}
		
		file.close();
	}
}

void MimeDatabase::addMimeType(const QString& mimeType, const QString& extension) {
	mimeTypes.insert(extension, mimeType);
}

QString MimeDatabase::getMimeTypeFor(const QString& suffix, const QString& defaultValue) const {
	return mimeTypes.contains(suffix) ? mimeTypes.value(suffix) : defaultValue;
}

QString MimeDatabase::mimeTypeFor(const QString& suffix, const QString& defaultValue) {
	return instance.getMimeTypeFor(suffix, defaultValue);
}

QString MimeDatabase::mimeTypeForFilename(const QString& filename, const QString& defaultValue) {
	return mimeTypeFor(QFileInfo(filename).suffix(), defaultValue);
}

ContentType MimeDatabase::contentTypeFor(const QString& suffix, const QString& defaultValue) {
	return ContentType::fromString(mimeTypeFor(suffix, defaultValue));
}

ContentType MimeDatabase::contentTypeForFilename(const QString& filename, const QString& defaultValue) {
	return contentTypeFor(QFileInfo(filename).suffix(), defaultValue);
}
