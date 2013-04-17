#pragma once

#include <controllers/BlogController.h>

class SearchController : public BlogController {
	public:
		SearchController();
		
		void index();
		void find();
		void findPost();
};
