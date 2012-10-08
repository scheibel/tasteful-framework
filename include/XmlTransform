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
#include <QHash>
#include <DomHelper>
#include <DomNode>

class XmlTransform : protected DomHelper {
	public:
		typedef void (XmlTransform::*Transform)(DomNode&) const;
	private:
		void transformRecursion(DomNode& node) const;
		void transformElement(DomNode& node) const;
		DomNode findFirstNodeWithAttribute(const DomNode& node, const QString& attribute) const;
	
		QHash<QString, Transform> transforms;
	protected:
		template <class T>
		void addTransform(const QString& selector, void (T::*transform)(DomNode&) const) {
			transforms.insert(selector, (Transform)transform);
		};
		void transform(DomNode& node) const;
		DomNode transformFile(const QString& filename) const;
		DomNode findContentNode(const DomNode& node) const;
};
