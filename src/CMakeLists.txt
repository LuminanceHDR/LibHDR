CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/libhdr_version.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/libhdr_version.cpp)

SET(LIBHDR_HDRS
    libhdr_dlldefines.h
    libhdr_version.h
    libhdr.h
    libhdr/matrix.h
#    libhdr/array2d.h
    libhdr/tag.h
    libhdr/channel.h
    libhdr/frame.h
    libhdr/pixel.h
#    libhdr/frameexceptions.h
    libhdr/coreobject.h
    libhdr/corecallback.h
    libhdr/io/framereader.h
#    libhdr/io/pfscommon.h
    libhdr/io/pfsreader.h
#    libhdr/io/iocommon.h
#    libhdr/io/ioexceptions.h
#    libhdr/rotate.h
    libhdr/template/objectfactory.h
    libhdr/template/singleton.h
    libhdr/settings.h
)

SET(LIBHDR_SRCS
    ${CMAKE_CURRENT_BINARY_DIR}/libhdr_version.cpp
    libhdr/matrix.cpp
#    libhdr/array2d.cpp
    libhdr/tag.cpp
    libhdr/channel.cpp
    libhdr/frame.cpp
    libhdr/pixel.cpp
#    libhdr/frameexceptions.cpp
    libhdr/coreobject.cpp
    libhdr/corecallback.cpp
    libhdr/io/framereader.cpp
#    libhdr/io/pfscommon.cpp
    libhdr/io/pfsreader.cpp
#    libhdr/io/ioexceptions.cpp
#    libhdr/rotate.cpp
)

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

#ADD_SUBDIRECTORY(io)

ADD_LIBRARY(${LIB_NAME} ${LIB_TYPE} ${LIBHDR_HDRS} ${LIBHDR_SRCS})
TARGET_LINK_LIBRARIES(${LIB_NAME} ${Boost_LIBRARIES})


