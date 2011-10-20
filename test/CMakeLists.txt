find_package(Boost COMPONENTS thread REQUIRED) #

link_directories( ${Boost_LIBRARY_DIRS} )
include_directories( ${Boost_INCLUDE_DIRS} )

SET(LIBHDR_TEST_HDRS
    MockCallback.h
    ConsoleCallbackMT.h)

SET(LIBHDR_TEST_SRCS
    main.cpp)

INCLUDE_DIRECTORIES(${LibHDR_SOURCE_DIR}/algorithms
    ${LibHDR_SOURCE_DIR}/core
    ${LibHDR_SOURCE_DIR}/io)

LINK_DIRECTORIES(${LibHDR_SOURCE_DIR})

ADD_EXECUTABLE(LibHDR-test ${LIBHDR_TEST_HDRS} ${LIBHDR_TEST_SRCS})
TARGET_LINK_LIBRARIES(LibHDR-test LibHDR ${Boost_LIBRARIES})
