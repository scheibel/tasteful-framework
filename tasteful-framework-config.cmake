
# TASTEFULF_RAMEWORK_FOUND

# TASTEFUL_FRAMEWORK_INCLUDES
# TASTEFUL_FRAMEWORK_LIBRARIES

# TASTEFUL_FRAMEWORK_LIBRARY
# TASTEFUL_FRAMEWORK_LIBRARY_RELEASE
# TASTEFUL_FRAMEWORK_LIBRARY_DEBUG
# TASTEFUL_FRAMEWORK_INCLUDE_DIR

include(FindPackageHandleStandardArgs)

if(CMAKE_CURRENT_LIST_FILE)
    get_filename_component(TASTEFUL_FRAMEWORK_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
endif()

file(TO_CMAKE_PATH "$ENV{PROGRAMFILES}" ENVPROGRAMFILES)
file(TO_CMAKE_PATH "$ENV{TASTEFUL_FRAMEWORK_DIR}" ENVTASTEFUL_FRAMEWORK_DIR)

set(LIB_PATHS   
    ${TASTEFUL_FRAMEWORK_DIR}/build
    ${TASTEFUL_FRAMEWORK_DIR}/build/Release
    ${TASTEFUL_FRAMEWORK_DIR}/build/Debug
    ${TASTEFUL_FRAMEWORK_DIR}/build-release
    ${TASTEFUL_FRAMEWORK_DIR}/build-debug
    ${ENVTASTEFUL_FRAMEWORK_DIR}/lib
    ${TASTEFUL_FRAMEWORK_DIR}/lib
    ${ENVPROGRAMFILES}/tasteful-framework/lib
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

    if (${LIB_NAME} STREQUAL "tasteful-framework")
        set(LIB_NAME_UPPER TASTEFUL_FRAMEWORK)
        set(LIBNAME tasteful_framework)
    else()
        string(TOUPPER TASTEFUL_FRAMEWORK_${LIB_NAME} LIB_NAME_UPPER)
        set(LIBNAME tasteful-framework-${LIB_NAME})
    endif()

    find_path(${LIB_NAME_UPPER}_INCLUDE_DIR ${HEADER}
        ${ENVTASTEFUL_FRAMEWORK_DIR}/include
        ${ENVTASTEFUL_FRAMEWORK_DIR}/source/${LIBNAME}/include
        ${TASTEFUL_FRAMEWORK_DIR}/include
        ${TASTEFUL_FRAMEWORK_DIR}/source/${LIBNAME}/include
        ${ENVPROGRAMFILES}/TASTEFUL_FRAMEWORK/include
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

    set(TASTEFUL_FRAMEWORK_INCLUDES  ${TASTEFUL_FRAMEWORK_INCLUDES}  ${${LIB_NAME_UPPER}_INCLUDE_DIR})
    set(TASTEFUL_FRAMEWORK_LIBRARIES ${TASTEFUL_FRAMEWORK_LIBRARIES} ${${LIB_NAME_UPPER}_LIBRARY})

    # DEBUG
    #message("${LIB_NAME_UPPER}_INCLUDE_DIR     = ${${LIB_NAME_UPPER}_INCLUDE_DIR}")
    #message("${LIB_NAME_UPPER}_LIBRARY_RELEASE = ${${LIB_NAME_UPPER}_LIBRARY_RELEASE}")
    #message("${LIB_NAME_UPPER}_LIBRARY_DEBUG   = ${${LIB_NAME_UPPER}_LIBRARY_DEBUG}")
    #message("${LIB_NAME_UPPER}_LIBRARY         = ${${LIB_NAME_UPPER}_LIBRARY}")

endmacro()

find(tasteful-framework   tasteful-framework/tasteful-framework_api.h             ${LIB_PATHS})

# DEBUG
#message("TASTEFUL_FRAMEWORK_INCLUDES  = ${TASTEFUL_FRAMEWORK_INCLUDES}")
#message("TASTEFUL_FRAMEWORK_LIBRARIES = ${TASTEFUL_FRAMEWORK_LIBRARIES}")

find_package_handle_standard_args(TASTEFUL_FRAMEWORK DEFAULT_MSG TASTEFUL_FRAMEWORK_LIBRARIES TASTEFUL_FRAMEWORK_INCLUDES)
mark_as_advanced(TASTEFUL_FRAMEWORK_FOUND)
