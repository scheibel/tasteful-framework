#pragma once

#include <QString>

class Tag {
public:
	Tag();
	
	const QString& getName() const;
	void setName(const QString& newName);
private:
	QString name;
};
