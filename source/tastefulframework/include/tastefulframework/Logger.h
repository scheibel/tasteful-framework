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

#include <QObject>
#include <QString>
#include <QByteArray>
#include <string>
#include <QFile>

#include <tastefulframework/tastefulframework_api.h>

class TASTEFULFRAMEWORK_API LogDevice : public QObject
{
    Q_OBJECT

public:
    LogDevice();
    LogDevice(QFile * file);
    ~LogDevice();

    QFile * operator=(QFile * file);

    void queueWrite(const QByteArray & val);

private slots:
    void directWrite(const QByteArray & val);

private:
    QFile * logDevice;
    static QFile* getStdOut();

    void setLogDevice(QFile * file);
};

class TASTEFULFRAMEWORK_API Logger : public QObject
{
    Q_OBJECT

public:
    Logger();
    Logger(const Logger & logger);
    ~Logger();

    Logger&warning();
    Logger&error();
    static void setLogDevice(QFile * file);
    Logger &operator<<(const QString & val);
    Logger &operator<<(const QByteArray & val);
    Logger &operator<<(const char * val);
    Logger &operator<<(std::string val);
    Logger &operator<<(QChar val);
    Logger &operator<<(char val);
    Logger &operator<<(bool val);
    Logger &operator<<(short val);
    Logger &operator<<(unsigned short val);
    Logger &operator<<(int val);
    Logger &operator<<(unsigned int val);
    Logger &operator<<(long val);
    Logger &operator<<(unsigned long val);
    Logger &operator<<(float val);
    Logger &operator<<(double val);
    Logger &operator<<(long double val);
    Logger &operator<<(const void * val);

private:
    static LogDevice logDevice;
    QByteArray bytes;

    void write(const char * val);
    void write(const QString & val);
    void write(const QByteArray & val);
};

Logger logger();
