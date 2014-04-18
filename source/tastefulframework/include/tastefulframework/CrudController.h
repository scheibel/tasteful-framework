/**
 * (C) LGPL-3
 *
 * Tasteful Framework <https://github.com/scheibel/tasteful-framework>
 *
 * Copyright: 2012-2014 Lux, Scheibel
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

#include <tastefulframework/Controller.h>
#include <tastefulserver/QVariantTree.h>

namespace tastefulframework {

template <class ControllerClass, class MapperClass>
class CrudController : public virtual Controller
{
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
    virtual void beforeSave(Model * model);
    virtual void saved(Model * model);
    virtual void created(Model * model);
    virtual void beforeDelete(Model * model);
    virtual void deleted(Model * model);
    virtual void renderListViewFor(const QHash<Identity, Model *> & models) = 0;
    virtual void renderShowViewFor(Model * model, Identity id) = 0;
    virtual void renderEditViewFor(Model * model, Identity id) = 0;
    virtual QList<Model *> findAll();
    MapperClass & getDataMapper();
    QHash<Identity, Model *> allModels();
};

#define DEFINE_CRUD_ACTIONS() \
public: \
    void index() { \
        CrudController::index(); \
    }; \
        \
    void show() { \
        CrudController::show(); \
    }; \
        \
    void create() { \
        CrudController::create(); \
    }; \
        \
    void edit() { \
        CrudController::edit(); \
    }; \
        \
    void save() { \
        CrudController::save(); \
    }; \
        \
    void remove() { \
        CrudController::remove(); \
    }; \

} // namespace tastefulframework

#include <tastefulframework/CrudController.hpp>
