#include <iostream>
#include <vector>
#include <set>
#include <memory>
using namespace std;

#include "CppUnitLite/TestHarness.h"
#include "ransac/ransac.h"
#include "estimators/Solver.h"
#include "estimators/lineFittingSolver.h"
#include "estimators/pointToLineDist.h"

using namespace groupsac;
// |
// | :: estimators
// | :: ransac

#include "armadillo/include/armadillo"
using namespace arma;
// |
// | :: mat
// | :: vec

//-------

//------------------------------
// Assert that test works
//------------------------------
TEST ( Ransac_LineFitting, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}

//------------------------------
// Test :
// - LineFIttingSolver in the ransac routine.
// - Assert the validity of the computed models
// - Assert inlier size
//------------------------------
TEST ( Ransac_LineFitting, RansacForLineEstimation )
{
  cout<< endl<< "[Ransac_LineFitting::RansacForLineEstimation]"<< endl<< endl;
  //-- Create the input solver (use auto_ptr for automatic delete of the object):
  auto_ptr< estimators::Solver<mat,vec> > ptrSolver(
    new estimators::lineFittingSolver<mat,vec>);

  //-- Create input data
  mat dataPoints = "0 0; 1 1; 2 2; 3 3";

  vector<int> inliers;
  vector<vec> models;

  ransac::Ransac_Handler ransac_fun_Handler;
  CHECK(
  ransac::Ransac_RobustEstimator
  (
    dataPoints, // the input data
    estimators::lineFittingSolver<mat,vec>::extractor, // How select sampled point from indices
    dataPoints.n_rows,  // the number of putatives data
    *(ptrSolver.get()),  // compute the underlying model given a sample set
    estimators::lineFittingSolver<mat,vec>::defaultEvaluator,  // the function to evaluate a given model
    //Ransac Object that contain function:
    // CandidatesSelector, Sampler and TerminationFunction
    ransac_fun_Handler, // the basic ransac object
    1000,  // the maximum rounds for RANSAC routine
    inliers, // inliers to the final solution
    models, // models array that fit input data
    0.95 // the confidence want to achieve at the end
  ) == true);

  CHECK(inliers.size()  == 4);
  CHECK(models.size()   == 1);
  DOUBLES_EQUAL(1.0, models[0](0), 1e-8);
  DOUBLES_EQUAL(0.0, models[0](1), 1e-8);
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */
