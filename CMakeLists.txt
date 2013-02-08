cmake_minimum_required(VERSION 2.6)

project(TastefulFramework)

option(WITH_EXAMPLES "Compile with examples" OFF)

if (WITH_EXAMPLES)
	message ("-- Compile Tasteful Server WITH examples")
	
	add_subdirectory(examples)
else (WITH_EXAMPLES)
	message ("-- Compile Tasteful Server WITHOUT examples")
endif (WITH_EXAMPLES)

find_package(Qt4 COMPONENTS QtCore QtSql QtXml QtNetwork REQUIRED)
find_package(TastefulServer REQUIRED)
include(${QT_USE_FILE})

include_directories("./include/" ${TastefulServer_INCLUDE_DIR})

add_definitions(-std=c++0x -Wreturn-type -Werror=return-type)

QT4_WRAP_CPP(Framework_moc_sources
	include/AbstractSession.h
	include/internal/SessionPool.h
	include/Logger.h
	include/internal/RouteRegistry.h
	include/internal/Dispatcher.h
	include/internal/SignalXmlContentHandler.h
	include/internal/WebAppConfigReader.h
)

set(Framework_sources
	src/core/Properties.cpp
	src/core/Logger.cpp
	src/core/SignalXmlContentHandler.cpp
	src/core/WebAppConfig.cpp
	src/core/WebAppConfigReader.cpp
	src/core/WebApplication.cpp
	src/core/MimeDatabase.cpp
	src/core/DomNode.cpp
	
	src/frontend/FrameworkEntryPoint.cpp
	src/frontend/FrontController.cpp
	src/frontend/AbstractSession.cpp
	src/frontend/GenericSession.cpp
	src/frontend/Controller.cpp
	src/frontend/RestrictedController.cpp
	src/frontend/Action.cpp
	src/frontend/Request.cpp
	src/frontend/Dispatcher.cpp
	src/frontend/Response.cpp
	src/frontend/Route.cpp
	src/frontend/RouteRegistry.cpp
	src/frontend/Download.cpp
	src/frontend/routing.cpp
	src/frontend/SessionContainer.cpp
	src/frontend/SessionPool.cpp
	
	src/database/Database.cpp
	src/database/SqlBuilder.cpp
	src/database/SqlHelper.cpp
	
	src/views/View.cpp
	src/views/XmlTransform.cpp
	src/views/TemplatedLayout.cpp
	src/views/TemplateView.cpp
	src/views/LayoutedTemplateView.cpp
	src/views/DomHelper.cpp
	src/views/Partial.cpp
)

set(Framework_headers
	include/WebApplication.h
	include/WebApplication
	include/Request.h
	include/Request
	include/routing.h
	include/routing
	include/Download.h
	include/Download
	include/RestrictedController.h
	include/RestrictedController
	include/Concurrent.h
	include/Concurrent
	include/UrlHelper.h
	include/UrlHelper
	include/Controller.h
	include/Controller
	include/DataMapper.h
	include/DataMapper
	include/XmlTransform.h
	include/XmlTransform
	include/Logger.h
	include/Logger
	include/TemplateView.h
	include/TemplateView
	include/WebAppConfig.h
	include/WebAppConfig
	include/GenericSession.h
	include/GenericSession
	include/startup.h
	include/startup
	include/AbstractSession.h
	include/AbstractSession
	include/View.h
	include/View
	include/DomHelper.h
	include/DomHelper
	include/CrudController.h
	include/CrudController
	include/RedirectException.h
	include/RedirectException
	include/TemplatedLayout.h
	include/TemplatedLayout
	include/Response.h
	include/Response
	include/DomNode.h
	include/DomNode
	include/Partial.h
	include/Partial
)

set(Framework_internal_headers
	include/internal/Action.h
	include/internal/Action
	include/internal/FrontController.h
	include/internal/FrontController
	include/internal/Database.h
	include/internal/Database
	include/internal/SignalXmlContentHandler.h
	include/internal/SignalXmlContentHandler
	include/internal/SessionContainer.h
	include/internal/SessionContainer
	include/internal/SqlBuilder.h
	include/internal/SqlBuilder
	include/internal/MimeDatabase.h
	include/internal/MimeDatabase
	include/internal/util.h
	include/internal/WebAppConfigReader.h
	include/internal/WebAppConfigReader
	include/internal/Dispatcher.h
	include/internal/Dispatcher
	include/internal/SessionPool.h
	include/internal/SessionPool
	include/internal/SqlHelper.h
	include/internal/SqlHelper
	include/internal/Route.h
	include/internal/Route
	include/internal/FrameworkEntryPoint.h
	include/internal/FrameworkEntryPoint
	include/internal/RouteRegistry.h
	include/internal/RouteRegistry
	include/internal/Properties.h
	include/internal/Properties
	include/internal/ObjectConstructor.h
	include/internal/ObjectConstructor
	include/internal/IdentityMap.h
	include/internal/IdentityMap
)

add_library(TastefulFramework SHARED ${Framework_sources} ${Framework_moc_sources} ${Framework_headers} ${Framework_internal_headers})

target_link_libraries(TastefulFramework ${QT_LIBRARIES} ${QT_QTSQL_LIBRARIES} ${TastefulServer_LIBRARY})

install(FILES ${Framework_headers} DESTINATION include/tastefulframework/)
install(FILES ${Framework_internal_headers} DESTINATION include/tastefulframework/internal)
install(TARGETS TastefulFramework
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
install(FILES "${CMAKE_SOURCE_DIR}/FindTastefulFramework.cmake" DESTINATION ${CMAKE_ROOT}/Modules)
