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

#include <tasteful-framework/Action.h>

namespace tastefulframework {

Action::~Action()
{
}

StringAction::StringAction(const QString & content)
    : m_content(content)
{
}

Response StringAction::operator()(Request & /*request*/) const
{
    return Response::forContent(m_content);
}

FileAction::FileAction(const QFile & file)
    : m_file(file.fileName())
{
}

Response FileAction::operator()(Request & /*request*/) const
{
    return Response::forFile(m_file);
}

DownloadAction::DownloadAction(const Download & download)
    : m_download(download)
{
}

Response DownloadAction::operator()(Request & /*request*/) const
{
    return m_download.getResponse();
}

ResponseAction::ResponseAction(const Response & response)
    : m_response(response)
{
}

Response ResponseAction::operator()(Request & /*request*/) const
{
    return m_response;
}

LambdaAction::LambdaAction(Lambda lambda)
    : m_lambda(lambda)
{
}

Response LambdaAction::operator()(Request & request) const
{
    return m_lambda(request);
}

} // namespace tastefulframework
