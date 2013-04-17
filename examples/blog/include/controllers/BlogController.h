#pragma once

#include <session/Session.h>

#include <RestrictedController>

class BlogController : public RestrictedController {
	public:
		BlogController();
		
		Session* getSession() const;
	protected:
		virtual bool isAuthorized() const;
};
