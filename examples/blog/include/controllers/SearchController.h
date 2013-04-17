#pragma once

#include <controllers/BlogController>

class SearchController : public BlogController {
	public:
		SearchController();
		
		void index();
		void find();
		void findPost();
};
