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

#pragma once

#include <tastefulframework/DomHelper.h>

namespace tastefulframework {

template <typename T, typename... Args>
void NodeCreator::add(T t, Args... args)
{
    addModifier(t);
    add(args...);
}

template <typename... Args>
NodeCreator NodeCreatorPlaceholder::operator()(Args... args) const
{
	NodeCreator NodeCreator(name);

	NodeCreator.add(args...);

	return NodeCreator;
}

DEFINE_TAG(DomHelper, a)
DEFINE_TAG(DomHelper, abbr)
DEFINE_TAG(DomHelper, acronym)
DEFINE_TAG(DomHelper, address)
DEFINE_TAG(DomHelper, applet)
DEFINE_TAG(DomHelper, area)
DEFINE_TAG(DomHelper, article)
DEFINE_TAG(DomHelper, aside)
DEFINE_TAG(DomHelper, audio)
DEFINE_TAG(DomHelper, b)
DEFINE_TAG(DomHelper, base)
DEFINE_TAG(DomHelper, basefont)
DEFINE_TAG(DomHelper, bdi)
DEFINE_TAG(DomHelper, bdo)
DEFINE_TAG(DomHelper, big)
DEFINE_TAG(DomHelper, blockquote)
DEFINE_TAG(DomHelper, body)
DEFINE_TAG(DomHelper, br)
DEFINE_TAG(DomHelper, button)
DEFINE_TAG(DomHelper, canvas)
DEFINE_TAG(DomHelper, caption)
DEFINE_TAG(DomHelper, center)
DEFINE_TAG(DomHelper, cite)
DEFINE_TAG(DomHelper, code)
DEFINE_TAG(DomHelper, col)
DEFINE_TAG(DomHelper, colgroup)
DEFINE_TAG(DomHelper, command)
DEFINE_TAG(DomHelper, datalist)
DEFINE_TAG(DomHelper, dd)
DEFINE_TAG(DomHelper, del)
DEFINE_TAG(DomHelper, details)
DEFINE_TAG(DomHelper, dfn)
DEFINE_TAG(DomHelper, dir)
DEFINE_TAG(DomHelper, div)
DEFINE_TAG(DomHelper, dl)
DEFINE_TAG(DomHelper, dt)
DEFINE_TAG(DomHelper, em)
DEFINE_TAG(DomHelper, embed)
DEFINE_TAG(DomHelper, fieldset)
DEFINE_TAG(DomHelper, figcaption)
DEFINE_TAG(DomHelper, figure)
DEFINE_TAG(DomHelper, font)
DEFINE_TAG(DomHelper, footer)
DEFINE_TAG(DomHelper, form)
DEFINE_TAG(DomHelper, frame)
DEFINE_TAG(DomHelper, frameset)
DEFINE_TAG(DomHelper, h1)
DEFINE_TAG(DomHelper, h2)
DEFINE_TAG(DomHelper, h3)
DEFINE_TAG(DomHelper, h4)
DEFINE_TAG(DomHelper, h5)
DEFINE_TAG(DomHelper, h6)
DEFINE_TAG(DomHelper, head)
DEFINE_TAG(DomHelper, header)
DEFINE_TAG(DomHelper, hgroup)
DEFINE_TAG(DomHelper, hr)
DEFINE_TAG(DomHelper, html)
DEFINE_TAG(DomHelper, i)
DEFINE_TAG(DomHelper, iframe)
DEFINE_TAG(DomHelper, img)
DEFINE_TAG(DomHelper, input)
DEFINE_TAG(DomHelper, ins)
DEFINE_TAG(DomHelper, keygen)
DEFINE_TAG(DomHelper, kbd)
DEFINE_TAG(DomHelper, label)
DEFINE_TAG(DomHelper, legend)
DEFINE_TAG(DomHelper, li)
DEFINE_TAG(DomHelper, link)
DEFINE_TAG(DomHelper, map)
DEFINE_TAG(DomHelper, mark)
DEFINE_TAG(DomHelper, menu)
DEFINE_TAG(DomHelper, meta)
DEFINE_TAG(DomHelper, meter)
DEFINE_TAG(DomHelper, nav)
DEFINE_TAG(DomHelper, noframes)
DEFINE_TAG(DomHelper, noscript)
DEFINE_TAG(DomHelper, object)
DEFINE_TAG(DomHelper, ol)
DEFINE_TAG(DomHelper, optgroup)
DEFINE_TAG(DomHelper, option)
DEFINE_TAG(DomHelper, output)
DEFINE_TAG(DomHelper, p)
DEFINE_TAG(DomHelper, param)
DEFINE_TAG(DomHelper, pre)
DEFINE_TAG(DomHelper, progress)
DEFINE_TAG(DomHelper, q)
DEFINE_TAG(DomHelper, rp)
DEFINE_TAG(DomHelper, rt)
DEFINE_TAG(DomHelper, ruby)
DEFINE_TAG(DomHelper, s)
DEFINE_TAG(DomHelper, samp)
DEFINE_TAG(DomHelper, script)
DEFINE_TAG(DomHelper, section)
DEFINE_TAG(DomHelper, select)
DEFINE_TAG(DomHelper, small)
DEFINE_TAG(DomHelper, source)
DEFINE_TAG(DomHelper, span)
DEFINE_TAG(DomHelper, strike)
DEFINE_TAG(DomHelper, strong)
DEFINE_TAG(DomHelper, style)
DEFINE_TAG(DomHelper, sub)
DEFINE_TAG(DomHelper, summary)
DEFINE_TAG(DomHelper, sup)
DEFINE_TAG(DomHelper, table)
DEFINE_TAG(DomHelper, tbody)
DEFINE_TAG(DomHelper, td)
DEFINE_TAG(DomHelper, textarea)
DEFINE_TAG(DomHelper, tfoot)
DEFINE_TAG(DomHelper, th)
DEFINE_TAG(DomHelper, thead)
DEFINE_TAG(DomHelper, time)
DEFINE_TAG(DomHelper, title)
DEFINE_TAG(DomHelper, tr)
DEFINE_TAG(DomHelper, track)
DEFINE_TAG(DomHelper, tt)
DEFINE_TAG(DomHelper, u)
DEFINE_TAG(DomHelper, ul)
DEFINE_TAG(DomHelper, var)
DEFINE_TAG(DomHelper, video)
DEFINE_TAG(DomHelper, wbr)

DEFINE_CUSTOM_TAG(DomHelper, formbutton) {
	return input(type("button"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, checkbox) {
	return input(type("checkbox"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, file) {
	return input(type("file"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, hidden) {
	return input(type("hidden"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, imagebutton) {
	return input(type("image"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, password) {
	return input(type("password"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, radiobutton) {
	return input(type("radio"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, resetbutton) {
	return input(type("reset"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, submitbutton) {
	return input(type("submit"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, textfield) {
	return input(type("text"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, colorchooser) {
	return input(type("color"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, datepicker) {
	return input(type("date"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, datetimepicker) {
	return input(type("datetime"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, localdatetimepicker) {
	return input(type("datetime-local"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, emailfield) {
	return input(type("email"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, monthpicker) {
	return input(type("month"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, numberfield) {
	return input(type("number"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, rangeslider) {
	return input(type("range"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, searchfield) {
	return input(type("search"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, telephonefield) {
	return input(type("tel"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, timefield) {
	return input(type("time"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, urlfield) {
	return input(type("url"), args...);
}
DEFINE_CUSTOM_TAG(DomHelper, weekpicker) {
	return input(type("week"), args...);
}

} // namespace tastefulframework
