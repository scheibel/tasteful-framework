
# TASTEFULFRAMEWORK_FOUND

# TASTEFULFRAMEWORK_INCLUDES
# TASTEFULFRAMEWORK_LIBRARIES

# TASTEFULFRAMEWORK_LIBRARY
# TASTEFULFRAMEWORK_LIBRARY_RELEASE
# TASTEFULFRAMEWORK_LIBRARY_DEBUG
# TASTEFULFRAMEWORK_INCLUDE_DIR

include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(TASTEFULFRAMEWORK_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENVPROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{TASTEFULFRAMEWORK_DIR}" ENVTASTEFULFRAMEWORK_DIR)

set(LIB_PATHS   
    ${TASTEFULFRAMEWORK_DIR}/build
    ${TASTEFULFRAMEWORK_DIR}/build/Release
    ${TASTEFULFRAMEWORK_DIR}/build/Debug
    ${TASTEFULFRAMEWORK_DIR}/build-release
    ${TASTEFULFRAMEWORK_DIR}/build-debug
    ${ENVTASTEFULFRAMEWORK_DIR}/lib
    ${TASTEFULFRAMEWORK_DIR}/lib
    ${ENVPROGRAMFILES}/TASTEFULFRAMEWORK/lib
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    /usr/lib64
    /usr/local/lib64
    /sw/lib64
    /opt/local/lib64
)

macro (find LIB_NAME HEADER)
    set(HINT_PATHS ${ARGN})

    if (${LIB_NAME} STREQUAL "TASTEFULFRAMEWORK")
        set(LIB_NAME_UPPER TASTEFULFRAMEWORK)
        set(LIBNAME TASTEFULFRAMEWORK)
    else()
        string(TOUPPER TASTEFULFRAMEWORK_${LIB_NAME} LIB_NAME_UPPER)
        set(LIBNAME TASTEFULFRAMEWORK${LIB_NAME})
    endif()

    find_path(${LIB_NAME_UPPER}_INCLUDE_DIR ${HEADER}
        ${ENVTASTEFULFRAMEWORK_DIR}/include
        ${ENVTASTEFULFRAMEWORK_DIR}/source/${LIBNAME}/include
        ${TASTEFULFRAMEWORK_DIR}/include
        ${TASTEFULFRAMEWORK_DIR}/source/${LIBNAME}/include
        ${ENVPROGRAMFILES}/TASTEFULFRAMEWORK/include
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        DOC "The directory where ${header} resides")

    find_library(${LIB_NAME_UPPER}_LIBRARY_RELEASE
        NAMES ${LIBNAME}
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} library")
    find_library(${LIB_NAME_UPPER}_LIBRARY_DEBUG
        NAMES ${LIBNAME}d
        PATHS ${HINT_PATHS}
        DOC "The ${LIB_NAME} debug library")
    
    if(${LIB_NAME_UPPER}_LIBRARY_RELEASE AND ${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY "optimized" ${${LIB_NAME_UPPER}_LIBRARY_RELEASE} "debug" ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    elseif(${LIB_NAME_UPPER}_LIBRARY_RELEASE)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_RELEASE})
    elseif(${LIB_NAME_UPPER}_LIBRARY_DEBUG)
        set(${LIB_NAME_UPPER}_LIBRARY ${${LIB_NAME_UPPER}_LIBRARY_DEBUG})
    endif()

    set(TASTEFULFRAMEWORK_INCLUDES  ${TASTEFULFRAMEWORK_INCLUDES}  ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    set(TASTEFULFRAMEWORK_LIBRARIES ${TASTEFULFRAMEWORK_LIBRARIES} ${${LIB_NAME_UPPER}_LIBRARY})

    # DEBUG
    #message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
    #message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
    #message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
    #message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endmacro()

find(TASTEFULFRAMEWORK   TASTEFULFRAMEWORK/TASTEFULFRAMEWORK_api.h             ${LIB_PATHS})

# DEBUG
#message("TASTEFULFRAMEWORK_INCLUDES  = ${TASTEFULFRAMEWORK_INCLUDES}")
#message("TASTEFULFRAMEWORK_LIBRARIES = ${TASTEFULFRAMEWORK_LIBRARIES}")

find_package_handle_standard_args(TASTEFULFRAMEWORK DEFAULT_MSG TASTEFULFRAMEWORK_LIBRARIES TASTEFULFRAMEWORK_INCLUDES)
mark_as_advanced(TASTEFULFRAMEWORK_FOUND)
