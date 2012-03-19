CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/libhdr_version.cpp.in ${CMAKE_CURRENT_BINARY_DIR}/libhdr_version.cpp)

SET(LIBHDR_HDRS
#LIBHDR BASE
    libhdr_dlldefines.h
    libhdr_version.h
    libhdr.h
# LIBHDR CORE
    libhdr/matrix.h
#   libhdr/array2d.h
    libhdr/tag.h
    libhdr/frame.h
    libhdr/channel.h
    libhdr/image.h
    libhdr/pixel.h
#   libhdr/frameexceptions.h
    libhdr/coreobject.h
    libhdr/corecallback.h
    libhdr/settings.h
# EXIF
    libhdr/exif/exifdata.h
# TEMPLATE
    libhdr/template/objectfactory.h
    libhdr/template/singleton.h
#LIBHDR IO
    libhdr/io/framereader.h
    libhdr/io/framereader.aux.h
#   libhdr/io/pfscommon.h
    libhdr/io/pfsreader.h
    libhdr/io/iocommon.h
    libhdr/io/ioexceptions.h
    libhdr/io/framewriter.h
    libhdr/io/framewriter.aux.h
    libhdr/io/tiffwriter.h
    libhdr/io/tiffreader.h
    libhdr/io/magickreader.h
)

SET(LIBHDR_SRCS
#LIBHDR BASE
    ${CMAKE_CURRENT_BINARY_DIR}/libhdr_version.cpp
#LIBHDR CORE
    libhdr/matrix.cpp
#   libhdr/array2d.cpp
    libhdr/tag.cpp
    libhdr/frame.cpp
    libhdr/channel.cpp
    libhdr/image.cpp
    libhdr/pixel.cpp
#   libhdr/frameexceptions.cpp
    libhdr/coreobject.cpp
    libhdr/corecallback.cpp
#   libhdr/rotate.cpp
# EXIF
    libhdr/exif/exifdata.cpp
#LIBHDR IO
    libhdr/io/framereader.cpp
#   libhdr/io/pfscommon.cpp
    libhdr/io/pfsreader.cpp
    libhdr/io/ioexceptions.cpp
    libhdr/io/framewriter.cpp
    libhdr/io/tiffwriter.cpp
    libhdr/io/tiffreader.cpp
    libhdr/io/magickreader.cpp
)

FIND_PACKAGE(TIFF REQUIRED)
FIND_PACKAGE(ImageMagick COMPONENTS Magick++ REQUIRED)
FIND_PACKAGE(Exiv2 REQUIRED)

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ImageMagick_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${EXIV2_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
LINK_DIRECTORIES(${TIFF_LIBRARY_DIRS})

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

ADD_LIBRARY(${LIB_NAME} ${LIB_TYPE} ${LIBHDR_HDRS} ${LIBHDR_SRCS})
TARGET_LINK_LIBRARIES(${LIB_NAME}
    ${Boost_LIBRARIES}
    ${TIFF_LIBRARIES}
    ${ImageMagick_LIBRARIES}
    ${EXIV2_LIBRARIES})


