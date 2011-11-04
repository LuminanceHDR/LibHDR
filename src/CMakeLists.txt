SET(LIBHDR_HDRS
    DLLDefines.h
    LibHDR.h
    LibHDR/Array2D.h
    LibHDR/Tag.h
    LibHDR/Channel.h
    LibHDR/Frame.h
    LibHDR/FrameExceptions.h
    LibHDR/CoreObject.h
    LibHDR/CoreCallback.h
    LibHDR/IO/FrameReaderFactory.h
    LibHDR/IO/IFrameReader.h
    LibHDR/IO/PFSCommon.h
    LibHDR/IO/PFSReader.h
    LibHDR/IO/IOCommon.h
    LibHDR/IO/IOExceptions.h
    LibHDR/rotate.h)

SET(LIBHDR_SRCS
    LibHDR/Array2D.cpp
    LibHDR/Tag.cpp
    LibHDR/Channel.cpp
    LibHDR/Frame.cpp
    LibHDR/FrameExceptions.cpp
    LibHDR/CoreObject.cpp
    LibHDR/CoreCallback.cpp
    LibHDR/IO/FrameReaderFactory.cpp
    LibHDR/IO/IFrameReader.cpp
    LibHDR/IO/PFSCommon.cpp
    LibHDR/IO/PFSReader.cpp
    LibHDR/IO/IOExceptions.cpp
    LibHDR/rotate.cpp)

include_directories("${CMAKE_SOURCE_DIR}/src")

# Allow the developer to select if Dynamic or Static libraries are built
OPTION (BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
# Set the LIB_TYPE variable to STATIC
SET (LIB_TYPE STATIC)
IF (BUILD_SHARED_LIBS)
  # User wants to build Dynamic Libraries, so change the LIB_TYPE variable to CMake keyword 'SHARED'
  SET (LIB_TYPE SHARED)
ENDIF (BUILD_SHARED_LIBS)

ADD_LIBRARY(LibHDR ${LIB_TYPE} ${LIBHDR_HDRS} ${LIBHDR_SRCS})

