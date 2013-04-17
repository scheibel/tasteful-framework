#pragma once

#include <controllers/BlogController.h>

class LoggedInController : public BlogController {
public:
	LoggedInController();
protected:
	virtual bool isAuthorized() const;
	virtual void unauthorized();
};
