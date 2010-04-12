#
# (C) 2010 Groupsac

# Library 
IF (WIN32)
  SET(LAPACK_BLAS_LIB ${LAPACK_BLAS_LIB} 
    ${CMAKE_SOURCE_DIR}/thirdParty/windowsLib/libf2c.lib
    ${CMAKE_SOURCE_DIR}/thirdParty/windowsLib/lapack.lib
    ${CMAKE_SOURCE_DIR}/thirdParty/windowsLib/blas.lib)
ELSE (WIN32)
  SET(LAPACK_BLAS_LIB ${LAPACK_BLAS_LIB} lapack blas)
ENDIF (WIN32)

ADD_EXECUTABLE(mainTestRansac_LineFitting mainTestRansac_LineFitting.cpp)
TARGET_LINK_LIBRARIES(mainTestRansac_LineFitting ${LAPACK_BLAS_LIB})

add_executable(testLineFittingSolver testLineFittingSolver.cpp)
add_custom_target(testLineFittingSolver.run testLineFittingSolver)
TARGET_LINK_LIBRARIES(testLineFittingSolver "CppUnitLite" ${LAPACK_BLAS_LIB})
add_test(testLineFittingSolver testLineFittingSolver)

add_executable(testFundamental7ptFittingSolver testFundamental7ptSolver.cpp)
add_custom_target(testFundamental7ptFittingSolver.run Fundamental7ptFittingSolver)
TARGET_LINK_LIBRARIES(testFundamental7ptFittingSolver "CppUnitLite" ${LAPACK_BLAS_LIB})
add_test(testFundamental7ptFittingSolver testFundamental7ptFittingSolver)

add_executable(testRobustRansacFundamental7ptSolver testRobustRansacFundamental7ptSolver.cpp)
add_custom_target(testRobustRansacFundamental7ptSolver.run Fundamental7ptFittingRobustSolver)
TARGET_LINK_LIBRARIES(testRobustRansacFundamental7ptSolver "CppUnitLite" ${LAPACK_BLAS_LIB})
add_test(testRobustRansacFundamental7ptSolver testRobustRansacFundamental7ptSolver)
