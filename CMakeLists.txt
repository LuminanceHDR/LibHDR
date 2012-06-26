PROJECT(LibHDR)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" ON)

# Define project version
SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 0)
SET(${PROJECT_NAME}_PATCH_LEVEL 1)
SET(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL})

# set include path for FindXXX.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Define
IF(WIN32)
    FIND_PACKAGE(Boost REQUIRED)
    SET(Boost_USE_STATIC_LIBS   OFF)
    SET(Boost_USE_MULTITHREADED ON)
ELSE()
    FIND_PACKAGE(Boost COMPONENTS thread unit_test_framework REQUIRED)
    ADD_DEFINITIONS(-Wall)
ENDIF()

ENABLE_TESTING()

IF(WIN32)
    SET(LIB_NAME libhdr)
ELSE()
    SET(LIB_NAME hdr)
ENDIF()

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
# GIL contributions
INCLUDE_DIRECTORIES("/Users/Davide/Luminance/gil-contributions/gil_2")


SET(LIBHDR_HDRS )
SET(LIBHDR_SRCS )

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (doc)
