#
# (C) 2010 NICTA

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(ARMA_MAJOR 0)
SET(ARMA_MINOR 9)
SET(ARMA_PATCH 4)

MESSAGE(STATUS "Configuring Armadillo ${ARMA_MAJOR}.${ARMA_MINOR}.${ARMA_PATCH}")

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build_aux/cmake/Modules/")

INCLUDE(CheckIncludeFileCXX)
INCLUDE(CheckLibraryExists)
INCLUDE(FindBoost)

INCLUDE(ARMA_CheckProto)
INCLUDE(ARMA_CheckMathProto)

#SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )

PROJECT(armadillo CXX)

#CMAKE_REQUIRED_FLAGS = string of compile command line flags
#CMAKE_REQUIRED_DEFINITIONS = list of macros to define (-DFOO=bar)
#CMAKE_REQUIRED_LIBRARIES = list of libraries to link


SET(ARMA_USE_LAPACK false)
SET(ARMA_USE_BLAS   false)
SET(ARMA_USE_ATLAS  false)
SET(ARMA_USE_BOOST  false)


IF(WIN32)
  MESSAGE(STATUS "")
  MESSAGE(STATUS "WARNING:")
  MESSAGE(STATUS "Automatic installation was not tested on this platform.")
  MESSAGE(STATUS "If it doesn't work, please try the manual installation")
  MESSAGE(STATUS "(described in the README.txt file), or simply use the")
  MESSAGE(STATUS "include folder directly.")
  MESSAGE(STATUS "")
ENDIF(WIN32)


IF(APPLE)
  SET(ARMA_OS macos)
  
  SET(ARMA_USE_LAPACK true)
  SET(ARMA_USE_BLAS   true)
  
  # Under MacOS, the current version of ARMA_FindCLAPACK can get confused between
  # two incompatible versions of "clapack.h" (one provided by the system and one
  # provided by ATLAS).  As such, use of ATLAS under MacOS is disabled for now.
  
ELSE(APPLE)
  SET(ARMA_OS unix)
  
  #INCLUDE(ARMA_FindMKL)
  
  ## Uncomment the line above if you want to use the Intel Math Kernel Library (MKL).
  ## You may also need to further configure your operating system in order to get 
  ## MKL working properly.  See "README.txt" for more information.
  
  
  IF(MKL_FOUND)
    
    SET(ARMA_USE_BLAS true)
    SET(ARMA_USE_LAPACK true)
    
  ELSE(MKL_FOUND)
    
    INCLUDE(ARMA_FindLAPACK)
    INCLUDE(ARMA_FindBLAS)
    
    IF(LAPACK_FOUND)
      SET(ARMA_USE_LAPACK true)
    ENDIF(LAPACK_FOUND)
    
    IF(BLAS_FOUND)
      SET(ARMA_USE_BLAS true)
    ENDIF(BLAS_FOUND)
    
    INCLUDE(ARMA_FindCLAPACK)
    INCLUDE(ARMA_FindCBLAS)
    
    IF(CLAPACK_FOUND AND CBLAS_FOUND)
      MESSAGE(STATUS "CLAPACK_INCLUDE_DIR = ${CLAPACK_INCLUDE_DIR}")
      MESSAGE(STATUS "CBLAS_INCLUDE_DIR   = ${CBLAS_INCLUDE_DIR}")
      IF(${CLAPACK_INCLUDE_DIR} STREQUAL ${CBLAS_INCLUDE_DIR})
        SET(ARMA_USE_ATLAS true)
        SET(ARMA_ATLAS_INCLUDE_DIR ${CLAPACK_INCLUDE_DIR})
      ENDIF(${CLAPACK_INCLUDE_DIR} STREQUAL ${CBLAS_INCLUDE_DIR})
    ENDIF(CLAPACK_FOUND AND CBLAS_FOUND)
  
  ENDIF(MKL_FOUND)
  
ENDIF(APPLE)


FIND_PACKAGE(Boost)

IF(Boost_FOUND)
  
  MESSAGE(STATUS "Boost_MAJOR_VERSION = ${Boost_MAJOR_VERSION}")
  MESSAGE(STATUS "Boost_MINOR_VERSION = ${Boost_MINOR_VERSION}")
  
  IF(Boost_MAJOR_VERSION GREATER 0)
    IF(Boost_MINOR_VERSION GREATER 33)
      SET(ARMA_USE_BOOST true)
      MESSAGE(STATUS "Boost_INCLUDE_DIR = ${Boost_INCLUDE_DIR}")
    ENDIF(Boost_MINOR_VERSION GREATER 33)
  ENDIF(Boost_MAJOR_VERSION GREATER 0)
  
ENDIF(Boost_FOUND)

IF(ARMA_USE_BOOST STREQUAL false)
  MESSAGE(STATUS "Boost libraries either not found or their version is too low (version 1.34 or later is good).")
  MESSAGE(STATUS "( It's possible that CMake didn't find the particular version of Boost you may have. )")
  MESSAGE(STATUS "( If that's the case, please edit include/armadillo_bits/config.hpp manually. )")
ENDIF(ARMA_USE_BOOST STREQUAL false)


# If Boost libraries were found, explicitly check if Boost's date_time library is also present.
# This is due to the non-standard packaging of Boost libraries on Debian and Ubuntu systems,
# where certain individual Boost libraries are packaged separately.

IF(ARMA_USE_BOOST STREQUAL true)
  SET(CMAKE_REQUIRED_INCLUDES ${CMAKE_REQUIRED_INCLUDES} ${Boost_INCLUDE_DIR})
  CHECK_INCLUDE_FILE_CXX("boost/date_time/posix_time/posix_time.hpp" ARMA_USE_BOOST_DATE)
ENDIF(ARMA_USE_BOOST STREQUAL true)

IF(MKL_FOUND)
  
  SET(ARMA_LIBS ${ARMA_LIBS} ${MKL_LIBRARIES})
  
ELSE(MKL_FOUND)
  
  IF(ARMA_USE_BLAS STREQUAL true)
    SET(ARMA_LIBS ${ARMA_LIBS} ${BLAS_LIBRARIES})
  ENDIF(ARMA_USE_BLAS STREQUAL true)
  
  IF(ARMA_USE_LAPACK STREQUAL true)
    SET(ARMA_LIBS ${ARMA_LIBS} ${LAPACK_LIBRARIES})
  ENDIF(ARMA_USE_LAPACK STREQUAL true)
  
  IF(ARMA_USE_ATLAS STREQUAL true)
    SET(ARMA_LIBS ${ARMA_LIBS} ${CBLAS_LIBRARIES})
    SET(ARMA_LIBS ${ARMA_LIBS} ${CLAPACK_LIBRARIES})
  ENDIF(ARMA_USE_ATLAS STREQUAL true)
  
ENDIF(MKL_FOUND)


IF(APPLE)
  SET(ARMA_LIBS ${ARMA_LIBS} "-framework Accelerate")  # or "-framework accelerate" ?
  MESSAGE(STATUS "MacOS X detected. Added '-framework Accelerate' to compiler flags")
ENDIF(APPLE)

MESSAGE(STATUS "ARMA_LIBS = ${ARMA_LIBS}")


ARMA_CHECK_MATH_PROTO("isfinite" "std" "cmath"  ARMA_HAVE_STD_ISFINITE)
ARMA_CHECK_MATH_PROTO("isinf"    "std" "cmath"  ARMA_HAVE_STD_ISINF)
ARMA_CHECK_MATH_PROTO("isnan"    "std" "cmath"  ARMA_HAVE_STD_ISNAN)
ARMA_CHECK_MATH_PROTO("log1p"    ""    "cmath"  ARMA_HAVE_LOG1P)

ARMA_CHECK_PROTO("snprintf"     "std" "cstdio"     ARMA_HAVE_STD_SNPRINTF)
ARMA_CHECK_PROTO("gettimeofday" ""    "sys/time.h" ARMA_HAVE_GETTIMEOFDAY)


MESSAGE(STATUS "Generating 'include/armadillo_bits/config.hpp'")
CONFIGURE_FILE(include/armadillo_bits/config.hpp.cmake include/armadillo_bits/config.hpp)

MESSAGE(STATUS "Generating 'examples/Makefile'")
CONFIGURE_FILE(examples/Makefile.cmake examples/Makefile)


IF(ARMA_USE_BOOST STREQUAL true)
  INCLUDE_DIRECTORIES(include ${Boost_INCLUDE_DIR})
ELSE(ARMA_USE_BOOST STREQUAL true)
  INCLUDE_DIRECTORIES(include)
ENDIF(ARMA_USE_BOOST STREQUAL true)


## For any library that is not in a default location,
## embed its path into the Armadillo runtime library.
## Examples of default locations are "/lib", "/usr/lib",
## or as specified in "/etc/ld.so.conf".
##
## Path embedding is not recommended unless you know
## what you're doing.  It might be better to add the
## path to the "/etc/ld.so.conf" file and then run "ldconfig".
##
#SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
#SET(CMAKE_BUILD_WITH_INSTALL_RPATH  FALSE)
#SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE)


ADD_LIBRARY( armadillo SHARED src/pull_libs )
TARGET_LINK_LIBRARIES( armadillo ${ARMA_LIBS} )

SET_TARGET_PROPERTIES(armadillo PROPERTIES VERSION ${ARMA_MAJOR}.${ARMA_MINOR}.${ARMA_PATCH} SOVERSION 0)

# As Red Hat Enterprise Linux (and related systems such as Fedora)
# does not search /usr/local/lib by default, we need to place the
# library in /usr

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

MESSAGE(STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")


# Allow for the "lib" directory to be specified on the command line

IF(NOT LIB_INSTALL_DIR)
  IF(UNIX AND NOT APPLE)   # I don't know how Mac OS handles 64 bit systems
    IF(CMAKE_SIZEOF_VOID_P EQUAL 8)
      MESSAGE(STATUS "Detected 64 bit system")
      SET(LIB_INSTALL_DIR "lib64")
    ELSE(CMAKE_SIZEOF_VOID_P EQUAL 8)
      SET(LIB_INSTALL_DIR "lib")
    ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
  
  ELSE(UNIX AND NOT APPLE)
    SET(LIB_INSTALL_DIR "lib")
  ENDIF(UNIX AND NOT APPLE)
ENDIF(NOT LIB_INSTALL_DIR)

MESSAGE(STATUS "LIB_INSTALL_DIR = ${LIB_INSTALL_DIR}")

# Allow for the "include" directory to be specified on the command line

IF(NOT INCLUDE_INSTALL_DIR)
  SET(INCLUDE_INSTALL_DIR "include")
ENDIF(NOT INCLUDE_INSTALL_DIR)

MESSAGE(STATUS "INCLUDE_INSTALL_DIR = ${INCLUDE_INSTALL_DIR}")


# Note that the trailing / character in "include/" is critical

INSTALL(DIRECTORY include/ DESTINATION ${INCLUDE_INSTALL_DIR}
PATTERN ".svn" EXCLUDE
PATTERN "*.cmake" EXCLUDE
PATTERN "*~" EXCLUDE
PATTERN "*orig" EXCLUDE
)


INSTALL(TARGETS armadillo DESTINATION ${LIB_INSTALL_DIR})



