#pragma once

#include <controllers/BlogController>

class HomeController : public BlogController {
	public:
		HomeController();
		
		void index();
};
