#pragma once

#include <models/Author.h>

#include <AbstractSession>

class Session : public AbstractSession {
public:
	Session();
	
	bool isLoggedIn();
	Author* author;
};
