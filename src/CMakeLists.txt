SET(LIBHDR_ALGO_HDRS
	LibHDR.h
    CoreObject.h
    CoreCallback.h)

SET(LIBHDR_ALGO_SRCS
    CoreObject.cpp
    CoreCallback.cpp)

ADD_LIBRARY(LibHDR SHARED ${LIBHDR_HDRS} ${LIBHDR_SRCS})
