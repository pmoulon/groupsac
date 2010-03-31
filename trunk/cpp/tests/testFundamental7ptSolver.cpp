/*
 * testLineFitting.cpp
 *
 *   Created on: Mar 25, 2010
 *       Author: nikai
 *  Description: unit tests for line fitting
 */

#include "CppUnitLite/TestHarness.h"
#include "estimators/Solver.h"
#include "estimators/Fundamental7ptSolver.h"

using namespace groupsac;
// |
// | :: estimators
// | :: ransac

#include "armadillo/include/armadillo"
using namespace arma;
// |
// | :: mat
// | :: vec

#include <memory>
// |
// | :: auto_ptr<T>
using namespace std;

//------------------------------
// Assert that test works
//------------------------------
TEST ( Fundamental7ptFittingSolver, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}

//------------------------------
// Test :
// - Fundamental7ptSolver on 7 points.
// - Assert the validity of the computed models
// - Assert fundamental matrix properties (det(F)=0, ...)
//------------------------------
TEST ( Fundamental7ptFittingSolver, Fundamental7pt )
{
  cout<< endl << "[LineFittingSolver::Fundamental7pt]"  << endl << endl;
  mat xy = 
    "723 887 1251 1243;\
    1091 699 1603 923;\
    1691 811 2067 1031;\
    447 635 787 484;\
    971  91 1355 363;\
    1903   447 2163  743;\
    1483 1555 1875 1715";
  xy=trans(xy);

  vector<mat> models;
  auto_ptr< estimators::Solver<mat,mat> > ptrSolver
    ( new estimators::Fundamental7ptSolver<mat,mat> );

  ptrSolver->solve(xy, models);

  //Test the expected properties of the fundamental matrix
  CHECK(models.size() == 3);
  // Test on fundamental matrix
  //   1. The determinant is 0 (rank deficient)
  //   2. The condition x'T*F*x = 0 is satisfied to precision.
  for (size_t i=0; i < models.size(); ++i)
  {
    const mat & F = models[i];
    DOUBLES_EQUAL(det(F),0.0,1e-8);
    for (size_t j=0; j < xy.n_cols; ++j)
    {
      vec A(3),B(3);
      B(0) = xy(2,j);
      B(1) = xy(3,j);
      B(2) = 1.0;
      A(0) = xy(0,j);
      A(1) = xy(1,j);
      A(2) = 1.0;
      double residual = dot( (A), F * B);
      DOUBLES_EQUAL(residual,0.0,1e-8);
    }
  }
}


/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

