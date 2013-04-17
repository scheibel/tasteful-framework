#pragma once

#include <controllers/BlogController.h>

class LoginController : public BlogController {
public:
	LoginController();
	
	void index();
	void login();
	void logout();
};
