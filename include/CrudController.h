/**
  * (C) LGPL-3
  *
  * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
  *
  * Copyright: 2012 Lux, Scheibel
  * Authors:
  *     Roland Lux <rollux2000@googlemail.com>
  *     Willy Scheibel <willyscheibel@gmx.de>
  *
  * This file is part of Tasteful Framework.
  *
  * Tasteful Framework is free software: you can redistribute it and/or modify
  * it under the terms of the GNU Lesser General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * Tasteful Framework is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU Lesser General Public License for more details.
  *
  * You should have received a copy of the GNU Lesser General Public License
  * along with Tasteful Framework.  If not, see <http://www.gnu.org/licenses/>.
  **/

#pragma once

#include <Controller>

template <class ControllerClass, class MapperClass>
class CrudController : public virtual Controller {
	public:
		typedef typename MapperClass::Model Model;
		typedef typename MapperClass::Identity Identity;

		virtual void index();
		virtual void show();
		virtual void create();
		virtual void edit();
		virtual void save();
		virtual void remove();
	protected:
		virtual void beforeSave(Model* model);
		virtual void saved(Model* model);
		virtual void created(Model* model);
		virtual void beforeDelete(Model* model);
		virtual void deleted(Model* model);

		virtual void renderListViewFor(const QHash<Identity, Model*>& models) = 0;
		virtual void renderShowViewFor(Model* model, Identity id) = 0;
		virtual void renderEditViewFor(Model* model, Identity id) = 0;

		virtual QList<Model*> findAll();

		MapperClass& getDataMapper();
		QHash<Identity, Model*> allModels();
};

#define DEFINE_CRUD_ACTIONS() \
	public:\
		void index() {\
			CrudController::index();\
		};\
		\
		void show() {\
			CrudController::show();\
		};\
		\
		void create() {\
			CrudController::create();\
		};\
		\
		void edit() {\
			CrudController::edit();\
		};\
		\
		void save() {\
			CrudController::save();\
		};\
		\
		void remove() {\
			CrudController::remove();\
		};\

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::index() {
	renderListViewFor(allModels());
}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::show() {
	Identity id = parameters["id"].value<Identity>();

	renderShowViewFor(getDataMapper().get(id), id);
}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::create() {
	renderEditViewFor(nullptr, Identity());
}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::edit() {
	Identity id = parameters["id"].value<Identity>();

	renderEditViewFor(getDataMapper().get(id), id);
}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::save() {
	Identity id = parameters["id"].value<Identity>();
	Model* model = nullptr;
	QVariantMap record;

	if (getDataMapper().isValidId(id)) {
		model = getDataMapper().get(id);
	} else {
		model = getDataMapper().newModel();
	}

	for (const QString& key : getDataMapper().selectVariables()) {
		if (parameters.contains(key)) {
			record[key] = parameters[key].asQVariant();
		}
	}

	if (model) {
		getDataMapper().buildFromRecord(model, record);
		beforeSave(model);
		getDataMapper().save(model);
	}
	
	redirect(url(&ControllerClass::index));
}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::remove() {
	Identity id = parameters["id"].value<Identity>();

	Model* model = getDataMapper().get(id);

	if (model) {
		getDataMapper().remove(model);
	}

	redirect(url(&ControllerClass::index));
}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::beforeSave(Model* model) {

}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::saved(Model* model) {

}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::created(Model* model) {

}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::beforeDelete(Model* model) {

}

template <class ControllerClass, class MapperClass>
void CrudController<ControllerClass, MapperClass>::deleted(Model* model) {

}

template <class ControllerClass, class MapperClass>
MapperClass& CrudController<ControllerClass, MapperClass>::getDataMapper() {
	static MapperClass& dataMapper = MapperClass::instance();

	return dataMapper;
}

template <class ControllerClass, class MapperClass>
QList<typename MapperClass::Model*> CrudController<ControllerClass, MapperClass>::findAll() {
	return getDataMapper().all();
}

template <class ControllerClass, class MapperClass>
QHash<typename MapperClass::Identity, typename MapperClass::Model*> CrudController<ControllerClass, MapperClass>::allModels() {
	QHash<Identity, Model*> models;

	for (Model* model : findAll()) {
		models.insert(getDataMapper().idOf(model), model);
	}

	return models;
};
