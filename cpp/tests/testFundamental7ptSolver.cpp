/*
 * testFundamental7ptSolver.cpp
 *
 *   Created on: Apr 10, 2010
 *       Author: pmoulon
 *  Description: unit tests for fundamental 7point fitting
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
      vec A(2),B(2);
      B(0) = xy(2,j);
      B(1) = xy(3,j);
      A(0) = xy(0,j);
      A(1) = xy(1,j);
      double residual = estimators::EpipolarDistanceError::Error(F,A,B);
      DOUBLES_EQUAL(residual,0.0,1e-8);
    }
  }

  //-- Inliers  
  // Compute inliers indices
  vector<int> inliersIndices = 
    ((estimators::Fundamental7ptSolver<mat,mat>*)
      ptrSolver.get())->defaultEvaluator(models, xy, 2.0);
  CHECK(inliersIndices.size()==7);
  for(unsigned int i=0;i<inliersIndices.size();++i)
    CHECK(inliersIndices[i]==i);
}


TEST ( Fundamental7ptFittingSolver, SampsonError ) {

  mat F=" 0 0 0; 0 0 -1; 0 1 0";
  // Fundamental matrix corresponding to pure translation.

  vec x0="0 0", y0="  0   0"; // Good match (at infinity).
  vec x1="0 0", y1="100   0"; // Good match (no vertical disparity).
  vec x2="0 0", y2="0.0 0.1"; // Small error (a bit of vertical disparity).
  vec x3="0 0", y3="  0   1"; // Bigger error.
  vec x4="0 0", y4="  0  10"; // Biggest error.
  vec x5="0 0", y5="100  10"; // Biggest error with horizontal disparity.

  double dists[6];
  dists[0] = estimators::SampsonError::Error(F, x0, y0),
  dists[1] = estimators::SampsonError::Error(F, x1, y1),
  dists[2] = estimators::SampsonError::Error(F, x2, y2),
  dists[3] = estimators::SampsonError::Error(F, x3, y3),
  dists[4] = estimators::SampsonError::Error(F, x4, y4),
  dists[5] = estimators::SampsonError::Error(F, x5, y5);

  // The expected distance are two times (one per image) the distance from the
  // point to the reprojection of the best triangulated point.  For this
  // particular example this reprojection is the midpoint between the point and
  // the epipolar line.
  DOUBLES_EQUAL(0.0, dists[0],1e-8);
  DOUBLES_EQUAL(0.0, dists[1],1e-8);
  DOUBLES_EQUAL(2.0 * estimators::Square(0.1 / 2.0), dists[2],1e-3);
  DOUBLES_EQUAL(2.0 * estimators::Square(1.0 / 2.0), dists[3],1e-3);
  DOUBLES_EQUAL(2.0 * estimators::Square(10. / 2.0), dists[4],1e-3);
  DOUBLES_EQUAL(2.0 * estimators::Square(10. / 2.0), dists[5],1e-3);
}

TEST ( Fundamental7ptFittingSolver, SymmetricEpipolarDistanceError ) {

  mat F=" 0 0 0; 0 0 -1; 0 1 0";
  // Fundamental matrix corresponding to pure translation.

  vec x0="0 0", y0="  0   0"; // Good match (at infinity).
  vec x1="0 0", y1="100   0"; // Good match (no vertical disparity).
  vec x2="0 0", y2="0.0 0.1"; // Small error (a bit of vertical disparity).
  vec x3="0 0", y3="  0   1"; // Bigger error.
  vec x4="0 0", y4="  0  10"; // Biggest error.
  vec x5="0 0", y5="100  10"; // Biggest error with horizontal disparity.

  double dists[6];
  dists[0] = estimators::SymmetricEpipolarDistanceError::Error(F, x0, y0),
  dists[1] = estimators::SymmetricEpipolarDistanceError::Error(F, x1, y1),
  dists[2] = estimators::SymmetricEpipolarDistanceError::Error(F, x2, y2),
  dists[3] = estimators::SymmetricEpipolarDistanceError::Error(F, x3, y3),
  dists[4] = estimators::SymmetricEpipolarDistanceError::Error(F, x4, y4),
  dists[5] = estimators::SymmetricEpipolarDistanceError::Error(F, x5, y5);

  // The expected distance are two times (one per image) the distance from the
  // point to the reprojection of the best triangulated point.  For this
  // particular example this reprojection is the midpoint between the point and
  // the epipolar line.
  DOUBLES_EQUAL(0.0, dists[0],1e-8);
  DOUBLES_EQUAL(0.0, dists[1],1e-8);
  DOUBLES_EQUAL(2.0 * estimators::Square(0.1 / 2.0), dists[2],1e-3);
  DOUBLES_EQUAL(2.0 * estimators::Square(1.0 / 2.0), dists[3],1e-3);
  DOUBLES_EQUAL(2.0 * estimators::Square(10. / 2.0), dists[4],1e-3);
  DOUBLES_EQUAL(2.0 * estimators::Square(10. / 2.0), dists[5],1e-3);
}


/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

