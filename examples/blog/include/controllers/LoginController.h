#pragma once

#include <controllers/BlogController>

class LoginController : public BlogController {
	public:
		LoginController();
		
		void index();
		void login();
		void logout();
};
