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

#include <tasteful-framework/Logger.h>

#include <stdio.h>

namespace tastefulframework {

LogDevice::LogDevice()
    : m_logDevice(nullptr)
{
    setLogDevice(getStdOut());
}

LogDevice::LogDevice(QFile * file)
    : m_logDevice(nullptr)
{
    setLogDevice(file);
}

QFile * LogDevice::getStdOut()
{
    QFile * file = new QFile();

    file->open(stdout, QIODevice::WriteOnly);

    return file;
}

LogDevice::~LogDevice()
{
    if (m_logDevice)
    {
        m_logDevice->flush();
        m_logDevice->close();
        delete m_logDevice;
    }
}

QFile * LogDevice::operator=(QFile * file)
{
    setLogDevice(file);

    return file;
}

void LogDevice::setLogDevice(QFile * file)
{
    if (m_logDevice)
    {
        m_logDevice->flush();
        m_logDevice->close();
        delete m_logDevice;
    }

    m_logDevice = file;
    if (!m_logDevice->isOpen())
    {
        m_logDevice->open(QIODevice::WriteOnly);
    }

    if (!file->isWritable())
    {
        m_logDevice = nullptr;
    }
}

void LogDevice::directWrite(const QByteArray & val)
{
    if (m_logDevice)
    {
        m_logDevice->write(val);
        m_logDevice->flush();
    }
}

void LogDevice::queueWrite(const QByteArray & val)
{
    QMetaObject::invokeMethod(this, "directWrite", Qt::QueuedConnection, Q_ARG(QByteArray, val));
}

// ------------------------------

Logger logger()
{
    return Logger();
}

Logger &Logger::warning()
{
    write("warning: ");

    return *this;
}

Logger &Logger::error()
{
    write("error: ");

    return *this;
}

LogDevice Logger::s_logDevice;
void Logger::setLogDevice(QFile * file)
{
    s_logDevice = file;
}

Logger::Logger()
{
}

Logger::Logger(const Logger & /*logger*/)
: QObject()
{
}

Logger::~Logger()
{
    if (!m_bytes.isEmpty())
    {
        s_logDevice.queueWrite(m_bytes);
        s_logDevice.queueWrite("\n");
    }
}

void Logger::write(const QString & val)
{
    m_bytes.append(val);
}

void Logger::write(const QByteArray & val)
{
    m_bytes.append(val);
}

void Logger::write(const char * val)
{
    m_bytes.append(QString(val));
}

Logger &Logger::operator<<(const QString & val)
{
    write(val);

    return *this;
}

Logger &Logger::operator<<(const QByteArray & val)
{
    write(val);

    return *this;
}

Logger &Logger::operator<<(const char * val)
{
    write(val);

    return *this;
}

Logger &Logger::operator<<(std::string val)
{
    write(QString::fromStdString(val));

    return *this;
}

Logger &Logger::operator<<(QChar val)
{
    write(QString(val));

    return *this;
}

Logger &Logger::operator<<(char val)
{
    write(QString(QChar(val)));

    return *this;
}

Logger &Logger::operator<<(bool val)
{
    write(val ? "true" : "false");

    return *this;
}

Logger &Logger::operator<<(short val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(unsigned short val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(int val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(unsigned int val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(long val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(unsigned long val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(float val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(double val)
{
    write(QString::number(val));

    return *this;
}

Logger &Logger::operator<<(long double val)
{
    write(QString::number((double)val));

    return *this;
}

Logger &Logger::operator<<(const void * val)
{
    write("0x" + QString::number((quintptr)val, 16));

    return *this;
}

} // namespace tastefulframework
