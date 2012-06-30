add_subdirectory (libhdr)

FILE(GLOB HDRS "*.hpp")

SET(LIBHDR_HDRS ${LIBHDR_HDRS} ${HDRS} PARENT_SCOPE)
