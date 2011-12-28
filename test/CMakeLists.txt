INCLUDE_DIRECTORIES(${LibHDR_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

LINK_DIRECTORIES(${LibHDR_SOURCE_DIR}/src)
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

ADD_EXECUTABLE(test_corecallback
    mockcallback.h
    consolecallbackmt.h
    test_corecallback.cpp)
TARGET_LINK_LIBRARIES(test_corecallback LibHDR ${Boost_LIBRARIES})

ADD_EXECUTABLE(test_matrix_copyonwrite
    test_matrix_copyonwrite.cpp)
TARGET_LINK_LIBRARIES(test_matrix_copyonwrite LibHDR ${Boost_LIBRARIES})

ADD_TEST(test_corecallback ${CMAKE_CURRENT_BINARY_DIR}/test_corecallback)
ADD_TEST(test_copy_on_write_no_copy ${CMAKE_CURRENT_BINARY_DIR}/test_matrix_copyonwrite 1)
ADD_TEST(test_copy_on_write_copy ${CMAKE_CURRENT_BINARY_DIR}/test_matrix_copyonwrite 2)
