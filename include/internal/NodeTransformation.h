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

#include <DomNode>

#include <functional>

class XmlTransform;

namespace internal {
	class NodeTransformation {
	public:
		virtual void operator()(DomNode& node) const = 0;
	};
	
	template <typename T>
	class MethodNodeTransformation : public NodeTransformation {
	public:
		typedef void (T::*MethodPointer)(DomNode&) const;
	
		MethodNodeTransformation(XmlTransform* transform, MethodPointer methodPointer) : transform(transform), methodPointer(methodPointer) {
		}
		
		void operator()(DomNode& node) const {
			(dynamic_cast<const T*>(transform)->*methodPointer)(node);
		}
	private:
		XmlTransform* transform;
		MethodPointer methodPointer;
	};

	class LambdaNodeTransformation : public NodeTransformation {
	public:
		typedef std::function<void(DomNode&)> Lambda;
		LambdaNodeTransformation(Lambda lambda);
		
		void operator()(DomNode& node) const;
	private:
		Lambda lambda;
	};
}