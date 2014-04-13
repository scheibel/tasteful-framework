
# Target
set(target tastefulframework)
message(STATUS "Lib ${target}")

#
# External libraries
#

find_package(Qt5Core 5.0 REQUIRED)
find_package(TastefulServer REQUIRED)

#
# Includes
#

include_directories(
	${TASTEFULSERVER_INCLUDES}
)

include_directories(
    BEFORE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#
# Libraries
#

set(libs
	${TASTEFULSERVER_LIBRARIES}
)

#
# Compiler definitions
#

if (OPTION_BUILD_STATIC)
    add_definitions("-DTASTEFULFRAMEWORK_STATIC")
else()
    add_definitions("-DTASTEFULFRAMEWORK_EXPORTS")
endif()

#
# Sources
#

set(include_path "${CMAKE_CURRENT_SOURCE_DIR}/include/${target}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/source")

set(sources
	${source_path}/core/SignalXmlContentHandler.cpp
	${source_path}/core/WebApplication.cpp
	${source_path}/core/Properties.cpp
	${source_path}/core/StringConvertible.cpp
	${source_path}/core/Logger.cpp
	${source_path}/core/DomNode.cpp
	${source_path}/core/WebAppConfig.cpp
	${source_path}/core/WebAppConfigReader.cpp
	${source_path}/core/MimeDatabase.cpp
	${source_path}/database/SqlBuilder.cpp
	${source_path}/database/Database.cpp
	${source_path}/database/SqlHelper.cpp
	${source_path}/frontend/FrameworkEntryPoint.cpp
	${source_path}/frontend/RouteRegistry.cpp
	${source_path}/frontend/Action.cpp
	${source_path}/frontend/Request.cpp
	${source_path}/frontend/Route.cpp
	${source_path}/frontend/Controller.cpp
	${source_path}/frontend/Dispatcher.cpp
	${source_path}/frontend/FrontController.cpp
	${source_path}/frontend/routing.cpp
	${source_path}/frontend/GenericSession.cpp
	${source_path}/frontend/Response.cpp
	${source_path}/frontend/SessionPool.cpp
	${source_path}/frontend/RestrictedController.cpp
	${source_path}/frontend/SessionContainer.cpp
	${source_path}/frontend/Download.cpp
	${source_path}/frontend/AbstractSession.cpp
	${source_path}/views/TemplateView.cpp
	${source_path}/views/View.cpp
	${source_path}/views/XmlTransform.cpp
	${source_path}/views/TemplatedLayout.cpp
	${source_path}/views/LayoutedTemplateView.cpp
	${source_path}/views/Partial.cpp
	${source_path}/views/NodeTransformation.cpp
	${source_path}/views/DomHelper.cpp
)

set(api_includes
	${include_path}/AbstractSession.h
	${include_path}/Action.h
	${include_path}/ActiveRecordDataMapper.h
	${include_path}/ActiveRecord.h
	${include_path}/Concurrent.h
	${include_path}/Controller.h
	${include_path}/CrudController.h
	${include_path}/Database.h
	${include_path}/DataMapper.h
	${include_path}/Dispatcher.h
	${include_path}/DomHelper.h
	${include_path}/DomNode.h
	${include_path}/Download.h
	${include_path}/FrameworkEntryPoint.h
	${include_path}/FrontController.h
	${include_path}/GenericSession.h
	${include_path}/IdentityMap.h
	${include_path}/LayoutedTemplateView.h
	${include_path}/Logger.h
	${include_path}/MimeDatabase.h
	${include_path}/NodeTransformation.h
	${include_path}/ObjectConstructor.h
	${include_path}/Partial.h
	${include_path}/Properties.h
	${include_path}/QHashExtension.h
	${include_path}/RedirectException.h
	${include_path}/Request.h
	${include_path}/Response.h
	${include_path}/RestrictedController.h
	${include_path}/Route.h
	${include_path}/RouteRegistry.h
	${include_path}/routing.h
	${include_path}/SessionContainer.h
	${include_path}/SessionPool.h
	${include_path}/SignalXmlContentHandler.h
	${include_path}/SqlBuilder.h
	${include_path}/SqlHelper.h
	${include_path}/startup.h
	${include_path}/StringConvertible.h
	${include_path}/tastefulframework_api.h
	${include_path}/TemplatedLayout.h
	${include_path}/TemplateView.h
	${include_path}/UrlHelper.h
	${include_path}/View.h
	${include_path}/WebAppConfig.h
	${include_path}/WebAppConfigReader.h
	${include_path}/WebApplication.h
	${include_path}/XmlTransform.h
)

# Group source files
set(header_group "Header Files (API)")
set(source_group "Source Files")
source_group_by_path(${include_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${api_includes})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})

#
# Build library
#

if(OPTION_BUILD_STATIC)
    add_library(${target} ${api_includes} ${sources})
else()
    add_library(${target} SHARED ${api_includes} ${sources})
endif()

target_link_libraries(${target} ${libs})
qt5_use_modules(${target} Core Network Xml Sql)

set_target_properties(${target}
    PROPERTIES
    LINKER_LANGUAGE              CXX
    FOLDER                      "${IDE_FOLDER}"
    COMPILE_DEFINITIONS_DEBUG   "${DEFAULT_COMPILE_DEFS_DEBUG}"
    COMPILE_DEFINITIONS_RELEASE "${DEFAULT_COMPILE_DEFS_RELEASE}"
    COMPILE_FLAGS               "${DEFAULT_COMPILE_FLAGS}"
    LINK_FLAGS_DEBUG            "${DEFAULT_LINKER_FLAGS_DEBUG}"
    LINK_FLAGS_RELEASE          "${DEFAULT_LINKER_FLAGS_RELEASE}"
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}"
    INCLUDE_PATH	            ${include_path})

#
# Deployment
#

# Library
install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
    LIBRARY DESTINATION ${INSTALL_SHARED}
    ARCHIVE DESTINATION ${INSTALL_LIB}
)

# Header files
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${target} DESTINATION ${INSTALL_INCLUDE})
