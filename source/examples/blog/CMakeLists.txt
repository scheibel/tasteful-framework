
set(target blog)
message(STATUS "Example ${target}")

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
    ${CMAKE_SOURCE_DIR}/source/tastefulframework/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#
# Libraries
#

set(libs
	${TASTEFULSERVER_LIBRARIES}
	tastefulframework
)

#
# Sources
#

set(header_path "${CMAKE_CURRENT_SOURCE_DIR}")
set(source_path "${CMAKE_CURRENT_SOURCE_DIR}")

set(sources
	${source_path}/main.cpp
	${source_path}/src/views/Layout.cpp
	${source_path}/src/views/AllBlogPostList.cpp
	${source_path}/src/views/SearchResult.cpp
	${source_path}/src/views/Registration.cpp
	${source_path}/src/views/BlogPostPartial.cpp
	${source_path}/src/views/BlogPostEdit.cpp
	${source_path}/src/views/Home.cpp
	${source_path}/src/views/SearchForm.cpp
	${source_path}/src/views/BlogView.cpp
	${source_path}/src/views/BlogPostShow.cpp
	${source_path}/src/views/Login.cpp
	${source_path}/src/views/TagPartial.cpp
	${source_path}/src/views/BlogPostList.cpp
	${source_path}/src/models/Tag.cpp
	${source_path}/src/models/BlogPost.cpp
	${source_path}/src/models/Author.cpp
	${source_path}/src/session/Session.cpp
	${source_path}/src/controllers/BlogController.cpp
	${source_path}/src/controllers/RegisterController.cpp
	${source_path}/src/controllers/LoggedInController.cpp
	${source_path}/src/controllers/AllBlogPostController.cpp
	${source_path}/src/controllers/BlogPostController.cpp
	${source_path}/src/controllers/LoginController.cpp
	${source_path}/src/controllers/SearchController.cpp
	${source_path}/src/controllers/HomeController.cpp
)

set(headers
	${include_path}/include/views/BlogPostEdit.h
	${include_path}/include/views/SearchResult.h
	${include_path}/include/views/AllBlogPostList.h
	${include_path}/include/views/BlogPostShow.h
	${include_path}/include/views/Registration.h
	${include_path}/include/views/Home.h
	${include_path}/include/views/Layout.h
	${include_path}/include/views/Login.h
	${include_path}/include/views/TagPartial.h
	${include_path}/include/views/SearchForm.h
	${include_path}/include/views/BlogView.h
	${include_path}/include/views/BlogPostPartial.h
	${include_path}/include/views/BlogPostList.h
	${include_path}/include/models/Author.h
	${include_path}/include/models/BlogPost.h
	${include_path}/include/models/Tag.h
	${include_path}/include/session/Session.h
	${include_path}/include/controllers/RegisterController.h
	${include_path}/include/controllers/LoggedInController.h
	${include_path}/include/controllers/LoginController.h
	${include_path}/include/controllers/AllBlogPostController.h
	${include_path}/include/controllers/HomeController.h
	${include_path}/include/controllers/SearchController.h
	${include_path}/include/controllers/BlogController.h
	${include_path}/include/controllers/BlogPostController.h
)

# Group source files
set(header_group "Header Files")
set(source_group "Source Files")
source_group_by_path(${header_path} "\\\\.h$|\\\\.hpp$" 
    ${header_group} ${headers})
source_group_by_path(${source_path} "\\\\.cpp$|\\\\.c$|\\\\.h$|\\\\.hpp$" 
    ${source_group} ${sources})

#
# Build executable
#

add_executable(${target} ${sources})

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
    DEBUG_POSTFIX               "d${DEBUG_POSTFIX}")

#
# Deployment
#

install(TARGETS ${target}
    RUNTIME DESTINATION ${INSTALL_BIN}
#   LIBRARY DESTINATION ${INSTALL_SHARED}
#   ARCHIVE DESTINATION ${INSTALL_LIB}
)
