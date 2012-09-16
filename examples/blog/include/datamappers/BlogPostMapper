#pragma once

#include <DataMapper>
#include <models/BlogPost>

class BlogPostMapper : public DataMapper<BlogPostMapper, BlogPost, unsigned> {
	public:
		BlogPostMapper();
		~BlogPostMapper();
		
		BlogPost* newModel() const;
		void buildFromRecord(BlogPost* model, const QVariantMap& record) const;
		void buildRecordFrom(BlogPost* model, QVariantMap& record) const;
		QList<QString> selectVariables() const;
		QString identityFieldName() const;
		QString table() const;
		void saveRelationsOf(BlogPost* model) const;
		QString databaseId() const;
};
