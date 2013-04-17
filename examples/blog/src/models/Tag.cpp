#include <models/Tag.h>

Tag::Tag() {
}

const QString& Tag::getName() const {
	return name;
}

void Tag::setName(const QString& newName) {
	name = newName;
}

