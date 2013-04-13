#pragma once

#include <QString>

class Tag {
	public:
		Tag();
		~Tag();
		
		QString getName();
		void setName(QString newName);
	private:
		QString name;
};
