SET(LIBHDR_HDRS ${LIBHDR_HDRS} PARENT_SCOPE)

FIND_PACKAGE(TIFF REQUIRED)
FIND_PACKAGE(jpeg REQUIRED)

INCLUDE_DIRECTORIES(${LibHDR_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${TIFF_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})

# LINK_DIRECTORIES(${LibHDR_SOURCE_DIR}/src)
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
LINK_DIRECTORIES(${TIFF_LIBRARY_DIRS})
LINK_DIRECTORIES(${JPEG_LIBRARY_DIRS})

#ADD_LIBRARY(testutils STATIC test_utils.cpp test_utils.h)

#ADD_EXECUTABLE(test_corecallback
#    mockcallback.h
#    consolecallbackmt.h
#    test_corecallback.cpp)
#TARGET_LINK_LIBRARIES(test_corecallback ${LIB_NAME} ${Boost_LIBRARIES} testutils)
#ADD_TEST(test_corecallback ${CMAKE_CURRENT_BINARY_DIR}/test_corecallback)

#ADD_EXECUTABLE(test_matrix_copyonwrite
#    test_matrix_copyonwrite.cpp)
#TARGET_LINK_LIBRARIES(test_matrix_copyonwrite ${LIB_NAME} ${Boost_LIBRARIES} testutils)
#ADD_TEST(test_copy_on_write_no_copy ${CMAKE_CURRENT_BINARY_DIR}/test_matrix_copyonwrite 1)
#ADD_TEST(test_copy_on_write_copy ${CMAKE_CURRENT_BINARY_DIR}/test_matrix_copyonwrite 2)
#ADD_TEST(test_copy_on_write_function_parameter_no_copy ${CMAKE_CURRENT_BINARY_DIR}/test_matrix_copyonwrite 3)
#ADD_TEST(test_copy_on_write_leak_and_performance_check ${CMAKE_CURRENT_BINARY_DIR}/test_matrix_copyonwrite 4)

#ADD_EXECUTABLE(test_factory
#    test_factory.cpp)
#TARGET_LINK_LIBRARIES(test_factory ${LIB_NAME} ${Boost_LIBRARIES} testutils)
#ADD_TEST(test_factory_list ${CMAKE_CURRENT_BINARY_DIR}/test_factory 1)
#ADD_TEST(test_factory_basic_retrieve ${CMAKE_CURRENT_BINARY_DIR}/test_factory 2)

#ADD_EXECUTABLE(libhdr_stats
#    libhdr_stats.cpp)
#TARGET_LINK_LIBRARIES(libhdr_stats ${LIB_NAME} ${Boost_LIBRARIES})

#ADD_EXECUTABLE(test_tiffio test_tiffio.cpp)
#TARGET_LINK_LIBRARIES(test_tiffio ${LIB_NAME} ${Boost_LIBRARIES})

#ADD_EXECUTABLE(test_pixel test_pixel.cpp)
#TARGET_LINK_LIBRARIES(test_pixel ${LIB_NAME} ${Boost_LIBRARIES})
#ADD_TEST(test_pixel_conversion_to_8bit ${CMAKE_CURRENT_BINARY_DIR}/test_pixel)

#ADD_EXECUTABLE(test_io test_io.cpp)
#TARGET_LINK_LIBRARIES(test_io ${LIB_NAME})

#ADD_EXECUTABLE(test_merge test_merge.cpp)
#TARGET_LINK_LIBRARIES(test_merge ${LIB_NAME})

#ADD_EXECUTABLE(test_matrix_iterator test_matrix_iterator.cpp)
#TARGET_LINK_LIBRARIES(test_matrix_iterator ${LIB_NAME})

ADD_EXECUTABLE(test_gil test_gil.cpp ${LIBHDR_HDRS})
TARGET_LINK_LIBRARIES(test_gil ${TIFF_LIBRARIES} ${JPEG_LIBRARIES})

ADD_EXECUTABLE(test_gamma test_gamma.cpp ${LIBHDR_HDRS})
TARGET_LINK_LIBRARIES(test_gamma ${TIFF_LIBRARIES} ${JPEG_LIBRARIES})
