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

add_definitions(-std=c++0x)

QT4_WRAP_CPP(Framework_moc_sources
	include/AbstractSession
	include/internal/SessionPool
	include/Logger
	include/internal/RouteRegistry
	include/internal/Dispatcher
	include/internal/SignalXmlContentHandler
	include/internal/WebAppConfigReader
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
	src/views/TemplateLayout.cpp
	src/views/TemplateView.cpp
	src/views/DomHelper.cpp
)

set(Framework_headers
	include/WebApplication
	include/Request
	include/routing
	include/Download
	include/RestrictedController
	include/Concurrent
	include/UrlHelper
	include/Controller
	include/DataMapper
	include/XmlTransform
	include/Logger
	include/TemplateView
	include/WebAppConfig
	include/GenericSession
	include/startup
	include/AbstractSession
	include/View
	include/DomHelper
	include/CrudController
	include/RedirectException
	include/TemplateLayout
	include/Response
	include/DomNode
)

set(Framework_internal_headers
	include/internal/Action
	include/internal/FrontController
	include/internal/Database
	include/internal/SignalXmlContentHandler
	include/internal/SessionContainer
	include/internal/SqlBuilder
	include/internal/MimeDatabase
	include/internal/util.h
	include/internal/WebAppConfigReader
	include/internal/Dispatcher
	include/internal/SessionPool
	include/internal/SqlHelper
	include/internal/Route
	include/internal/FrameworkEntryPoint
	include/internal/RouteRegistry
	include/internal/Properties
	include/internal/ObjectConstructor
	include/internal/IdentityMap
)

add_library(TastefulFramework SHARED ${Framework_sources} ${Framework_moc_sources})

target_link_libraries(TastefulFramework ${QT_LIBRARIES} ${QT_QTSQL_LIBRARIES} ${TastefulServer_LIBRARY})

install(FILES ${Framework_headers} DESTINATION include/tastefulframework/)
install(FILES ${Framework_internal_headers} DESTINATION include/tastefulframework/internal)
install(TARGETS TastefulFramework
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
install(FILES "${CMAKE_SOURCE_DIR}/FindTastefulFramework.cmake" DESTINATION ${CMAKE_ROOT}/Modules)
