#pragma once

#include <controllers/BlogController.h>

class RegisterController : public BlogController {
public:
	RegisterController();
	
	void index();
	void signup();
};
