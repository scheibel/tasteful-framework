#pragma once

#include <DataMapper>
#include <models/Tag>

class TagMapper : public DataMapper<TagMapper, Tag, unsigned> {
	public:
		TagMapper();
		~TagMapper();
		
		Tag* newModel() const;
		void buildFromRecord(Tag* model, const QVariantMap& record) const;
		void buildRecordFrom(Tag* model, QVariantMap& record) const;
		QList<QString> selectVariables() const;
		QString identityFieldName() const;
		QString table() const;
		QString databaseId() const;
		
		Tag* obtainByName(const QString& name);
};
