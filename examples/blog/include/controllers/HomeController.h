#pragma once

#include <controllers/BlogController.h>

class HomeController : public BlogController {
public:
	HomeController();
	
	void index();
};
