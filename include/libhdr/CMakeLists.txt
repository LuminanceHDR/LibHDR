add_subdirectory (io)

FILE(GLOB HDRS "*.hpp")

SET(LIBHDR_HDRS ${LIBHDR_HDRS} ${HDRS} PARENT_SCOPE)
