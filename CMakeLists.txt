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

INCLUDE("${CMAKE_SOURCE_DIR}/cmake/FindLibHDRDeps.cmake")

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

SET(LIBHDR_HDRS )
SET(LIBHDR_SRCS )

add_subdirectory (include)
add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (doc)

# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

ADD_LIBRARY(${LIB_NAME} ${LIB_TYPE} ${LIBHDR_HDRS} ${LIBHDR_SRCS})
TARGET_LINK_LIBRARIES(${LIB_NAME}
#    ${Boost_LIBRARIES}
#    ${TIFF_LIBRARIES}
    ${EXIV2_LIBRARIES}
#    ${OPENEXR_LIBRARIES}
#    ${JPEG_LIBRARIES}
#    ${LCMS2_LIBRARIES}
)
