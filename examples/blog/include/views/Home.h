#pragma once

#include <models/BlogPost.h>
#include <views/BlogView.h>

#include <QList>

class Home : public BlogView {
public:
	Home(Session* session, const QList<BlogPost*>& blogPosts);
	
	void recentPosts(DomNode& node) const;
private:
	QList<BlogPost*> blogPosts;
};
