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

#include <functional>

#include <QString>
#include <QList>
#include <QDomDocument>

#include <tastefulframework/tastefulframework_api.h>

namespace tastefulframework {

#define DECLARE_TAG(tagname) \
    template <typename... Args> \
    NodeCreator tagname(Args... args) const

#define DEFINE_TAG(classname, tagname) \
    template <typename... Args> \
    NodeCreator classname::tagname(Args... args) const {\
        return tag(#tagname)(args...);\
    }

#define DEFINE_CUSTOM_TAG(classname, tagname) \
    template <typename... Args> \
    NodeCreator classname::tagname(Args... args) const

#define DECLARE_ATTRIBUTE(attributename) \
    TagModifier attributename(const QString &attributename) const

#define DEFINE_ATTRIBUTE(classname, attributename) \
    TagModifier classname::attributename(const QString &value) const { \
        return attribute(#attributename, value); \
    }

class DomNode;

typedef std::function<void (QDomElement &)> TagModifier;

class NodeCreatorPlaceholder;

class TASTEFULFRAMEWORK_API NodeCreator
{
public:
    NodeCreator();
    NodeCreator(const QString & name);
    NodeCreator(const NodeCreatorPlaceholder & placeholder);

    void add()       /*ignore*/
    {
    }

    template <typename T, typename... Args>
    void add(T t, Args... args);

    QDomElement operator()(QDomDocument doc) const;
    void operator()(QDomNode node) const;

private:
    void addModifier(TagModifier modifier);
    void addModifier(const NodeCreator & creator);
    void addModifier(const NodeCreatorPlaceholder & creatorPlaceholder);

    void addModifier(const DomNode & node);
    void addModifier(const QDomNode & node);

    void addModifier(const QString & text);
    void addModifier(const char * text);
    void addModifier(int i);
    void addModifier(unsigned u);
    void addModifier(long i);
    void addModifier(double d);

    QString m_name;
    QList<TagModifier> m_modifiers;
    bool m_null;
};

class TASTEFULFRAMEWORK_API NodeCreatorPlaceholder
{
public:
    NodeCreatorPlaceholder(const QString & name)
        : m_name(name)
    {
    }

    template <typename... Args>
    NodeCreator operator()(Args... args) const;

private:
    QString m_name;
};

class TASTEFULFRAMEWORK_API DomHelper
{
public:
    QDomDocument loadDocument(const QString & filename) const;

    NodeCreatorPlaceholder tag(const QString & name) const;
    TagModifier attribute(const QString & name, const QString & value) const;

    // convenience attributes
    TagModifier cssClass(const QString & name) const;

    // convenience tags
    DECLARE_TAG(formbutton);
    DECLARE_TAG(checkbox);
    DECLARE_TAG(file);
    DECLARE_TAG(hidden);
    DECLARE_TAG(imagebutton);
    DECLARE_TAG(password);
    DECLARE_TAG(radiobutton);
    DECLARE_TAG(resetbutton);
    DECLARE_TAG(submitbutton);
    DECLARE_TAG(textfield);
    DECLARE_TAG(colorchooser);
    DECLARE_TAG(datepicker);
    DECLARE_TAG(datetimepicker);
    DECLARE_TAG(localdatetimepicker);
    DECLARE_TAG(emailfield);
    DECLARE_TAG(monthpicker);
    DECLARE_TAG(numberfield);
    DECLARE_TAG(rangeslider);
    DECLARE_TAG(searchfield);
    DECLARE_TAG(telephonefield);
    DECLARE_TAG(timefield);
    DECLARE_TAG(urlfield);
    DECLARE_TAG(weekpicker);

    DECLARE_ATTRIBUTE(name);
    DECLARE_ATTRIBUTE(id);
    DECLARE_ATTRIBUTE(href);
    DECLARE_ATTRIBUTE(type);
    DECLARE_ATTRIBUTE(rel);
    DECLARE_ATTRIBUTE(value);

    DECLARE_TAG(a);
    DECLARE_TAG(abbr);
    DECLARE_TAG(acronym);
    DECLARE_TAG(address);
    DECLARE_TAG(applet);
    DECLARE_TAG(area);
    DECLARE_TAG(article);
    DECLARE_TAG(aside);
    DECLARE_TAG(audio);
    DECLARE_TAG(b);
    DECLARE_TAG(base);
    DECLARE_TAG(basefont);
    DECLARE_TAG(bdi);
    DECLARE_TAG(bdo);
    DECLARE_TAG(big);
    DECLARE_TAG(blockquote);
    DECLARE_TAG(body);
    DECLARE_TAG(br);
    DECLARE_TAG(button);
    DECLARE_TAG(canvas);
    DECLARE_TAG(caption);
    DECLARE_TAG(center);
    DECLARE_TAG(cite);
    DECLARE_TAG(code);
    DECLARE_TAG(col);
    DECLARE_TAG(colgroup);
    DECLARE_TAG(command);
    DECLARE_TAG(datalist);
    DECLARE_TAG(dd);
    DECLARE_TAG(del);
    DECLARE_TAG(details);
    DECLARE_TAG(dfn);
    DECLARE_TAG(dir);
    DECLARE_TAG(div);
    DECLARE_TAG(dl);
    DECLARE_TAG(dt);
    DECLARE_TAG(em);
    DECLARE_TAG(embed);
    DECLARE_TAG(fieldset);
    DECLARE_TAG(figcaption);
    DECLARE_TAG(figure);
    DECLARE_TAG(font);
    DECLARE_TAG(footer);
    DECLARE_TAG(form);
    DECLARE_TAG(frame);
    DECLARE_TAG(frameset);
    DECLARE_TAG(h1);
    DECLARE_TAG(h2);
    DECLARE_TAG(h3);
    DECLARE_TAG(h4);
    DECLARE_TAG(h5);
    DECLARE_TAG(h6);
    DECLARE_TAG(head);
    DECLARE_TAG(header);
    DECLARE_TAG(hgroup);
    DECLARE_TAG(hr);
    DECLARE_TAG(html);
    DECLARE_TAG(i);
    DECLARE_TAG(iframe);
    DECLARE_TAG(img);
    DECLARE_TAG(input);
    DECLARE_TAG(ins);
    DECLARE_TAG(keygen);
    DECLARE_TAG(kbd);
    DECLARE_TAG(label);
    DECLARE_TAG(legend);
    DECLARE_TAG(li);
    DECLARE_TAG(link);
    DECLARE_TAG(map);
    DECLARE_TAG(mark);
    DECLARE_TAG(menu);
    DECLARE_TAG(meta);
    DECLARE_TAG(meter);
    DECLARE_TAG(nav);
    DECLARE_TAG(noframes);
    DECLARE_TAG(noscript);
    DECLARE_TAG(object);
    DECLARE_TAG(ol);
    DECLARE_TAG(optgroup);
    DECLARE_TAG(option);
    DECLARE_TAG(output);
    DECLARE_TAG(p);
    DECLARE_TAG(param);
    DECLARE_TAG(pre);
    DECLARE_TAG(progress);
    DECLARE_TAG(q);
    DECLARE_TAG(rp);
    DECLARE_TAG(rt);
    DECLARE_TAG(ruby);
    DECLARE_TAG(s);
    DECLARE_TAG(samp);
    DECLARE_TAG(script);
    DECLARE_TAG(section);
    DECLARE_TAG(select);
    DECLARE_TAG(small);
    DECLARE_TAG(source);
    DECLARE_TAG(span);
    DECLARE_TAG(strike);
    DECLARE_TAG(strong);
    DECLARE_TAG(style);
    DECLARE_TAG(sub);
    DECLARE_TAG(summary);
    DECLARE_TAG(sup);
    DECLARE_TAG(table);
    DECLARE_TAG(tbody);
    DECLARE_TAG(td);
    DECLARE_TAG(textarea);
    DECLARE_TAG(tfoot);
    DECLARE_TAG(th);
    DECLARE_TAG(thead);
    DECLARE_TAG(time);
    DECLARE_TAG(title);
    DECLARE_TAG(tr);
    DECLARE_TAG(track);
    DECLARE_TAG(tt);
    DECLARE_TAG(u);
    DECLARE_TAG(ul);
    DECLARE_TAG(var);
    DECLARE_TAG(video);
    DECLARE_TAG(wbr);
};

} // namespace tastefulframework

#include <tastefulframework/DomHelper.hpp>
