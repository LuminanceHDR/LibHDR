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
    libhdr/details/resourcehandler.h
    libhdr/details/misc.h
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
    libhdr/io/exrwriter.h
    libhdr/io/jpegreader.h
#LIBHDR MERGE
    libhdr/merge/mergeexceptions.h
    libhdr/merge/mergeoperator.h
    libhdr/merge/debevec97.h
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
    libhdr/io/exrwriter.cpp
    libhdr/io/jpegreader.cpp
#LIBHDR MERGE
    libhdr/merge/mergeexceptions.cpp
    libhdr/merge/mergeoperator.cpp
    libhdr/merge/debevec97.cpp
)

IF(MSVC)
    # Windows Section

    SET(OPENEXR_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include/OpenEXR")
    SET(TIFF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include/libtiff")
    SET(LIBRAW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include/libraw")
    SET(FFTWF_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include/fftw3")
    SET(GSL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include/gsl")
    SET(GSLCBLAS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include/gsl")
    SET(EXIV2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../DEPs/include" "${CMAKE_SOURCE_DIR}/../DEPs/include/exiv2")
    
    # Test
    # Davide 2012.04.01 - No more Magick... it's not an April's fool! :)
    # SET(ImageMagick_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../../ImageMagick-6.7.6" "${CMAKE_SOURCE_DIR}/../../ImageMagick-6.7.6/Magick++/lib")
    
    # Enable multi processor compilation
    ADD_DEFINITIONS(/MP)

    # Enable SSE2
    ADD_DEFINITIONS(/arch:SSE2)
    
    # Disable warning 4251 ('identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2')
    ADD_DEFINITIONS(/wd4251)
    
    IF (BUILD_SHARED_LIBS)
        ADD_DEFINITIONS(-DLibHDR_EXPORTS)
    ENDIF()
    
    ADD_DEFINITIONS(-DUNICODE )
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -DOPENEXR_DLL -D_REENTRANT)
    SET(FFTWF_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/fftw3/libfftw3f-3.lib")
    ADD_DEFINITIONS(-DHAVE_FFTW3F)
    
    SET(OPENEXR_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/OpenEXR/Half.lib")
    SET(OPENEXR_LIBRARIES ${OPENEXR_LIBRARIES} "${CMAKE_SOURCE_DIR}/../DEPs/lib/OpenEXR/Iex.lib")
    SET(OPENEXR_LIBRARIES ${OPENEXR_LIBRARIES} "${CMAKE_SOURCE_DIR}/../DEPs/lib/OpenEXR/IlmImf.lib")
    
    SET(TIFF_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/libtiff/libtiff.lib")
    
    SET(LIBRAW_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/libraw/libraw.lib")
    
    SET(GSL_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/gsl/gsl.lib")
    SET(GSLCBLAS_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/gsl/cblas.lib")
    
    SET(EXIV2_LIBRARIES "${CMAKE_SOURCE_DIR}/../DEPs/lib/exiv2/exiv2.lib")
    
    # Davide 2012.04.01 - No more Magick
    # SET(ImageMagick_LIBRARIES "${CMAKE_SOURCE_DIR}/../../ImageMagick-6.7.6/VisualMagick/lib/CORE_RL_Magick++_.lib")

ELSE()
    # Unix & Apple part
    FIND_PACKAGE(TIFF REQUIRED)
    FIND_PACKAGE(Exiv2 REQUIRED)
    FIND_PACKAGE(OpenEXR REQUIRED)
    FIND_PACKAGE(jpeg REQUIRED)
    FIND_PACKAGE(LCMS2 REQUIRED)
ENDIF()

INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/src")
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${EXIV2_INCLUDE_DIR})
INCLUDE_DIRECTORIES("${OPENEXR_INCLUDE_DIR}/OpenEXR")
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${LCMS2_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
LINK_DIRECTORIES(${TIFF_LIBRARY_DIRS})
LINK_DIRECTORIES(${JPEG_LIBRARY_DIRS})
LINK_DIRECTORIES(${LCMS2_LIBRARY_DIRS})

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
    ${EXIV2_LIBRARIES}
    ${OPENEXR_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${LCMS2_LIBRARIES})


