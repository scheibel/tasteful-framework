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

#include <tastefulframework/Logger.h>
#include <stdio.h>

LogDevice::LogDevice() : logDevice(nullptr) {
	setLogDevice(getStdOut());
}

LogDevice::LogDevice(QFile* file) : logDevice(nullptr) {
	setLogDevice(file);
}

QFile* LogDevice::getStdOut() {
	QFile* file = new QFile();
	file->open(stdout, QIODevice::WriteOnly);
	return file;
}

LogDevice::~LogDevice() {
	if (logDevice) {
		logDevice->flush();
		logDevice->close();
		delete logDevice;
	}
}

QFile* LogDevice::operator=(QFile* file) {
	setLogDevice(file);

	return file;
}

void LogDevice::setLogDevice(QFile* file) {
	if (logDevice) {
		logDevice->flush();
		logDevice->close();
		delete logDevice;
	}

	logDevice = file;
	if (!logDevice->isOpen()) logDevice->open(QIODevice::WriteOnly);

	if (!file->isWritable()) {
		logDevice = nullptr;
	}
}

void LogDevice::directWrite(const QByteArray& val) {
	if (logDevice) {
		logDevice->write(val);
		logDevice->flush();
	}
}

void LogDevice::queueWrite(const QByteArray& val) {
	QMetaObject::invokeMethod(this, "directWrite", Qt::QueuedConnection, Q_ARG(QByteArray, val));
}

//------------------------------

Logger logger() {
	return Logger();
}

Logger& Logger::warning()
{
	write("warning: ");
	return *this;
}

Logger& Logger::error()
{
	write("error: ");
	return *this;
}

LogDevice Logger::logDevice;

void Logger::setLogDevice(QFile* file) {
	logDevice = file;
}

Logger::Logger() {
}

Logger::Logger(const Logger& logger) {
}

Logger::~Logger() {
	if (!bytes.isEmpty()) {
		logDevice.queueWrite(bytes);
		logDevice.queueWrite("\n");
	}
}

void Logger::write(const QString& val) {
	bytes.append(val);
}

void Logger::write(const QByteArray& val) {
	bytes.append(val);
}

void Logger::write(const char* val) {
	bytes.append(QString(val));
}

Logger& Logger::operator<<(const QString& val) {
	write(val);
	return *this;
}

Logger& Logger::operator<<(const QByteArray& val) {
	write(val);
	return *this;
}

Logger& Logger::operator<<(const char* val) {
	write(val);
	return *this;
}

Logger& Logger::operator<<(std::string val) {
	write(QString::fromStdString(val));
	return *this;
}

Logger& Logger::operator<<(QChar val) {
	write(QString(val));
	return *this;
}
Logger& Logger::operator<<(char val) {
	write(QString(QChar(val)));
	return *this;
}

Logger& Logger::operator<<(bool val) {
	write(val?"true":"false");
	return *this;
}

Logger& Logger::operator<<(short val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(unsigned short val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(int val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(unsigned int val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(long val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(unsigned long val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(float val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(double val) {
	write(QString::number(val));
	return *this;
}

Logger& Logger::operator<<(long double val) {
	write(QString::number((double)val));
	return *this;
}

Logger& Logger::operator<<(const void* val) {
	write("0x"+QString::number((quintptr)val, 16));
	return *this;
}
