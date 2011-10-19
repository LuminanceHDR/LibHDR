PROJECT(LibHDR)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

add_subdirectory (algorithms)
add_subdirectory (core)
add_subdirectory (tmo)
add_subdirectory (io)
add_subdirectory (test)

ADD_LIBRARY(LibHDR SHARED LibHDR.h)
TARGET_LINK_LIBRARIES(LibHDR algorithms)
