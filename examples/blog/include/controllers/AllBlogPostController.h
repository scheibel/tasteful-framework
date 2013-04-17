#pragma once

#include <controllers/BlogController.h>

class AllBlogPostController : public BlogController {
public:
	AllBlogPostController();
	
	void index();
	void show();
};
