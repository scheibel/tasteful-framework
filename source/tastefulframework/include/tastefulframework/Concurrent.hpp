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

#include <tastefulframework/Concurrent.h>

namespace tastefulframework {

template <class T>
Concurrent<T>::Concurrent()
    : m_object(nullptr)
{
}

template <class T>
Concurrent<T>::Concurrent(T * object)
    : m_object(object)
{
}

template <class T>
template <typename R, typename... Args>
R Concurrent<T>::perform(R (T::* mp)(Args...), Args... args)
{
        m_mutex.lock();
        R ret = (m_object->*mp)(args...);
        m_mutex.unlock();

        return ret;
}

template <class T>
template <typename R, typename... Args>
R Concurrent<T>::perform(R (T::* mp)(Args...) const, Args... args)
{
        m_mutex.lock();
        R ret = (m_object->*mp)(args...);
        m_mutex.unlock();

        return ret;
}

template <class T>
void Concurrent<T>::execute(std::function<void(T *)> function)
{
        m_mutex.lock();
        function(m_object);
        m_mutex.unlock();
}

} // namespace tastefulframework
