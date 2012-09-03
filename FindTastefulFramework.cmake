#
# Finds TastefulServer includes and library
#
# ${TastefulFramework_FOUND}
# ${TastefulFramework_INCLUDE_DIR}
# ${TastefulFramework_LIBRARY}

find_package(Qt4 COMPONENTS QtCore QtNetwork QtXml QtSql REQUIRED)
find_package(TastefulServer REQUIRED)

if(WIN_32)
	message(WARNING "Windows not yet supported")
else(WIN_32)
	find_path(TastefulFramework_INCLUDE_DIR WebApplication
		PATHS
		/usr/local/include/tastefulframework
		/usr/include/tastefulframework
		/opt/local/include/tastefulframework
	)
	find_library(TastefulFramework_LIBRARY libTastefulFramework.so
		PATHS
		/usr/local/lib
		/usr/lib
		/opt/local/lib
	)
endif(WIN_32)

find_package_handle_standard_args(TastefulFramework DEFAULT_MSG TastefulFramework_INCLUDE_DIR TastefulFramework_LIBRARY)