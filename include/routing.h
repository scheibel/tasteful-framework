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

#include <internal/RouteRegistry>

using namespace internal;

extern RouteActionAssigner ROOT;
extern RouteActionAssigner ROBOTS_TXT;
extern RouteActionAssigner FAV_ICON;

RouteActionAssigner GET(const QString& urlPattern);
RouteActionAssigner PUT(const QString& urlPattern);
RouteActionAssigner POST(const QString& urlPattern);
RouteActionAssigner DELETE(const QString& urlPattern);

template <class CrudControllerSubclass>
void registerCrudActions(const QString& urlPattern) {
	GET(urlPattern) = &CrudControllerSubclass::index;
	GET(urlPattern+"/:id") = &CrudControllerSubclass::show;
	GET(urlPattern+"/new") = &CrudControllerSubclass::create;
	GET(urlPattern+"/:id/edit") = &CrudControllerSubclass::edit;
	POST(urlPattern+"/save") = &CrudControllerSubclass::save;
	GET(urlPattern+"/:id/delete") = &CrudControllerSubclass::remove;
	DELETE(urlPattern+"/:id/delete") = &CrudControllerSubclass::remove;
}
