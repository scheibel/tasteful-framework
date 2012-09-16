#pragma once

#include <RestrictedController>
#include <session/Session>

class BlogController : public RestrictedController {
	public:
		BlogController();
		
		Session* getSession() const;
	protected:
		virtual bool isAuthorized() const;
};
