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

#include <tastefulframework/TemplatedLayout.h>
#include <QTextStream>

namespace tastefulframework {

TemplatedLayout::TemplatedLayout(const QString & filename)
    : m_filename(filename)
{
}

const QString &TemplatedLayout::filename() const
{
    return m_filename;
}

void TemplatedLayout::setFilename(const QString & filename)
{
    m_filename = filename;
}

void TemplatedLayout::layout(DomNode & node) const
{
    if (node.isNull())
    {
        return;
    }

    DomNode layoutNode = transformFile(m_filename);

    mergeHead(layoutNode.first("head"), node.first("head"));

    DomNode contentNode = findContentNode(layoutNode);
    contentNode.removeAttribute("data-content");

    contentNode.transferChildrenFrom(findContentNode(node), true);

    node = layoutNode;
}

void TemplatedLayout::mergeHead(DomNode targetHead, DomNode sourceHead) const
{
    if (targetHead.isNull() || sourceHead.isNull())
    {
        return;
    }

    for (DomNode & sourceHeadChild : sourceHead.children())
    {
        if (sourceHeadChild.isNull())
        {
            continue;
        }

        bool duplicate = false;

        for (DomNode & targetHeadChild : targetHead.children())
        {
            if (targetHeadChild.isNull())
            {
                continue;
            }

            if (sameNodes(sourceHeadChild, targetHeadChild))
            {
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
        {
            targetHead << sourceHeadChild;
        }
    }
}

bool TemplatedLayout::sameNodes(DomNode & node1, DomNode & node2) const
{
    if (node1.tagName()!=node2.tagName())
    {
        return false;
    }

    return node1.attributes() == node2.attributes();
    // TODO: take text into account
}

} // namespace tastefulframework
