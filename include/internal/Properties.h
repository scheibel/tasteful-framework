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

#include <QString>
#include <QSettings>
#include <internal/util.h>

namespace internal {
	class Properties {
	public:
		Properties(const QString& filename);
		~Properties();
		
		QString getFilename() const;
		
		template <typename T>
		T property(const QString& key, const T& defaultValue) const {
			QVariant value = settings->value(key);
			
			return value.isValid() ? value.value<T>() : defaultValue;
		}
		
		QVariant basicProperty(const QString& key) const {
			return settings->value(key);
		}
		
		template <typename T>
		T property(const QString& section, const QString& field, const T& defaultValue) const {
			return property<T>(section + "/" + field, defaultValue);
		}
	private:
		QString filename;
		QSettings* settings;
	};
}