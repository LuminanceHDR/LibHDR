add_subdirectory (io)
add_subdirectory (exif)

FILE(GLOB HDRS "*.hpp")

SET(LIBHDR_HDRS ${LIBHDR_HDRS} ${HDRS} PARENT_SCOPE)
