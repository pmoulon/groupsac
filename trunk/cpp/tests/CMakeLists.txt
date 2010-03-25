#
# (C) 2010 Groupsac

IF (WIN32)
ADD_EXECUTABLE(mainTestRansac_LineFitting mainTestRansac_LineFitting.cpp)
TARGET_LINK_LIBRARIES(mainTestRansac_LineFitting
  ${CMAKE_SOURCE_DIR}/thirdParty/windowsLib/libf2c.lib
  ${CMAKE_SOURCE_DIR}/thirdParty/windowsLib/lapack.lib
  ${CMAKE_SOURCE_DIR}/thirdParty/windowsLib/blas.lib)
ELSE (WIN32)
ADD_EXECUTABLE(mainTestRansac_LineFitting mainTestRansac_LineFitting.cpp)
#lapack and blas must be installed on the machine
TARGET_LINK_LIBRARIES(mainTestRansac_LineFitting lapack blas)
ENDIF (WIN32)

add_executable(testLineFittingSolver testLineFittingSolver.cpp)
add_custom_target(testLineFittingSolver.run testLineFittingSolver)
target_link_libraries(testLineFittingSolver "CppUnitLite")
add_test(testLineFittingSolver testLineFittingSolver)
