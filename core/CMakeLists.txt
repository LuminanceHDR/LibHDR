SET(LIBHDR_ALGO_HDRS
    CoreObject.h
    CoreCallback.h)

SET(LIBHDR_ALGO_SRCS
    CoreObject.cpp
    CoreCallback.cpp)

ADD_LIBRARY(core ${LIBHDR_ALGO_HDRS} ${LIBHDR_ALGO_SRCS})
