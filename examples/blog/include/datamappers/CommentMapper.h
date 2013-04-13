#pragma once

#include <DataMapper>
#include <models/Comment>

class CommentMapper : public DataMapper<CommentMapper, Comment, unsigned> {
	public:
		CommentMapper();
		~CommentMapper();
		
		Comment* newModel() const;
		void buildFromRecord(Comment* model, const QVariantMap& record) const;
		void buildRecordFrom(Comment* model, QVariantMap& record) const;
		QList<QString> selectVariables() const;
		QString identityFieldName() const;
		QString table() const;
		QString databaseId() const;
};
