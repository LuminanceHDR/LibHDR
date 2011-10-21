SET(LIBHDR_IO_HDRS
    FrameReader.h
    IStrategyReader.h)

SET(LIBHDR_IO_SRCS
    FrameReader.cpp
    IStrategyReader.cpp)

ADD_LIBRARY(io ${LIBHDR_IO_HDRS}) ${LIBHDR_IO_SRCS})