SET(LIBHDR_HDRS
    LibHDR.h
    Array2D.h
    Tag.h
    Channel.h
    Frame.h
    DLLDefines.h
    CoreObject.h
    CoreCallback.h
    FrameReader.h
    IStrategyReader.h)

SET(LIBHDR_SRCS
    Array2D.cpp
    Tag.cpp
    Channel.cpp
    Frame.cpp
    CoreObject.cpp
    CoreCallback.cpp
    FrameReader.cpp
    IStrategyReader.cpp)

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

ADD_LIBRARY(LibHDR ${LIB_TYPE} ${LIBHDR_HDRS} ${LIBHDR_SRCS})

