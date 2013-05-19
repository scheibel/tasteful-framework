project(Blog)

find_package(Qt5Core REQUIRED)
find_package(TastefulServer REQUIRED)

include_directories("./include/" "../../include/" ${TastefulServer_INCLUDE_DIR})

add_definitions(-std=c++0x -Wreturn-type -Werror=return-type)

set(Blog_sources
	main.cpp
	
	src/controllers/BlogController.cpp
	src/controllers/HomeController.cpp
	src/controllers/LoggedInController.cpp
	src/controllers/LoginController.cpp
	src/controllers/RegisterController.cpp
	src/controllers/AllBlogPostController.cpp
	src/controllers/SearchController.cpp
	src/controllers/BlogPostController.cpp
	
	src/models/Author.cpp
	src/models/BlogPost.cpp
	src/models/Tag.cpp
	
	src/session/Session.cpp
	
	src/views/AllBlogPostList.cpp
	src/views/BlogView.cpp
	src/views/BlogPostEdit.cpp
	src/views/BlogPostList.cpp
	src/views/BlogPostShow.cpp
	src/views/BlogPostPartial.cpp
	src/views/Home.cpp
	src/views/Layout.cpp
	src/views/Login.cpp
	src/views/Registration.cpp
	src/views/SearchForm.cpp
	src/views/SearchResult.cpp
	src/views/TagPartial.cpp
)

add_executable(Blog ${Blog_sources})

target_link_libraries(Blog TastefulFramework ${TastefulServer_LIBRARY})

qt5_use_modules(Blog Core Network Xml Sql)