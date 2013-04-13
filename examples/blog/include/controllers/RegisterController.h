#pragma once

#include <controllers/BlogController>

class RegisterController : public BlogController {
	public:
		RegisterController();
		
		void index();
		void signup();
};
