CONFIGURE_FILE(
${CMAKE_CURRENT_SOURCE_DIR}/libhdr_version.cpp.in
${CMAKE_CURRENT_BINARY_DIR}/libhdr_version.cpp
)

SET(SRCS
#LIBHDR BASE
    ${CMAKE_CURRENT_BINARY_DIR}/libhdr_version.cpp
#LIBHDR CORE
#    libhdr/tag.cpp
#    libhdr/frame.cpp
#    libhdr/channel.cpp
#    libhdr/image.cpp
#    libhdr/pixel.cpp
#   libhdr/frameexceptions.cpp
#    libhdr/coreobject.cpp
#    libhdr/corecallback.cpp
#   libhdr/rotate.cpp
# EXIF
    ${CMAKE_SOURCE_DIR}/src/libhdr/exif/exif_data.cpp
#LIBHDR IO
#    libhdr/io/framereader.cpp
#   libhdr/io/pfscommon.cpp
#    libhdr/io/pfsreader.cpp
#    libhdr/io/ioexceptions.cpp
#    libhdr/io/framewriter.cpp
#    libhdr/io/tiffwriter.cpp
#    libhdr/io/tiffreader.cpp
#    libhdr/io/exrwriter.cpp
#    libhdr/io/jpegreader.cpp
#LIBHDR MERGE
#    libhdr/merge/mergeexceptions.cpp
#    libhdr/merge/mergeoperator.cpp
#    libhdr/merge/debevec97.cpp
#    libhdr/merge/responses.cpp
#    libhdr/merge/weights.cpp
)

SET(LIBHDR_SRCS ${LIBHDR_SRCS} ${SRCS} PARENT_SCOPE)


