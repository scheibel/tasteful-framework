#pragma once

#include <controllers/LoggedInController.h>
#include <datamappers/BlogPostMapper.h>

#include <CrudController>

class BlogPostController : public LoggedInController, public CrudController<BlogPostController, BlogPostMapper> {
DEFINE_CRUD_ACTIONS();
public:
	BlogPostController();
protected:
	void beforeSave(BlogPost* blogPost);

	QList<BlogPost*> findAll();

	void renderListViewFor(const QHash<unsigned, BlogPost*>& blogEntries);
	void renderShowViewFor(BlogPost* blogEntry, unsigned id);
	void renderEditViewFor(BlogPost* blogEntry, unsigned id);
};
