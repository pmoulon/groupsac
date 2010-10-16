/*
 * ProsacFundmat.cpp
 *
 *   Created on: Oct 10, 2010
 *       Author: pmoulon
 *  Description: unit tests for fundamental 7point fitting inside Robust Prosac Algorithm
 */

#include "CppUnitLite/TestHarness.h"
#include "estimators/Solver.h"
#include "estimators/Fundamental7ptSolver.h"
#include "ransac/ransac.h"
#include "ransac/prosac_tools.h"

#include <vector>
#include <set>

using namespace groupsac;
// |
// | :: estimators
// | :: ransac
// | :: prosac

#include "armadillo/include/armadillo"
using namespace arma;
// |
// | :: mat
// | :: vec

#include <memory>
// |
// | :: auto_ptr<T>
using namespace std;

//-- END -- Must now be defined
//-------

//------------------------------
// Assert that test works
//------------------------------
TEST ( ProsacFundamentalMatrix, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}

typedef  bool (ransac::prosac::PROSAC_handler::*fun_prosac_terminationFn) 
    (
      vector<int> & best_inliers,
      const vector<int> & inliers,
      int round,
      int max_rounds,
      double logConfidence,
      int iSolverMinimalSamples,
      int iPutativesNumber
    );

//------------------------------
// Test :
// - Robust solver with Fundamental7ptSolver on 7 points.
// - Assert the validity of the computed models.
// - Assert inliers indexes are valid.
//------------------------------
TEST ( ProsacFundamentalMatrix, testProsacFundmat )
{
  cout<< endl<< "[ProsacFundamentalMatrix::testProsacFundmat]"
    << endl<< endl;
  //-- Create the input solver (use auto_ptr for automatic delete of the object):
  auto_ptr< estimators::Solver<mat,mat> > ptrSolver(
    new estimators::Fundamental7ptSolver<mat,mat>);

  //-- Create input data

  // set up putatives
//scores = [1 1 1 1 1 1 1];
//is_inlier = 1 : 7;

  mat dataPoints =
    "723 887 1251 1243;\
    1091 699 1603 923;\
    1691 811 2067 1031;\
    447 635 787 484;\
    971  91 1355 363;\
    1903   447 2163  743;\
    1483 1555 1875 1715";

  dataPoints = trans(dataPoints);

  vector<int> inliers;
  vector<mat> models;

  int rounds_to_equal = 200000;
  const int nbDataPoints = 7;
  vector<int> vec_ordering;
  for (int i=0; i < nbDataPoints; ++i)
  {
     vec_ordering.push_back(i);
  }
  ransac::prosac::PROSAC_handler prosac_fun_handler(7, rounds_to_equal, vec_ordering);

  CHECK(
  ransac::Ransac_RobustEstimator
  (
    dataPoints, // the input data
    estimators::Fundamental7ptSolver<mat,mat>::extractor, // How select sampled point from indices
    dataPoints.n_cols,  // the number of putatives data ( ideally dataPoints.cols() )
    *(ptrSolver.get()),  // compute the underlying model given a sample set
    estimators::Fundamental7ptSolver<mat,mat>::defaultEvaluator,  // the function to evaluate a given model
    //Ransac Object that contain function:
    // CandidatesSelector, Sampler and TerminationFunction
    prosac_fun_handler,
    5000,  // the maximum rounds for RANSAC routine
    inliers, // inliers to the final solution
    models, // models array that fit input data
    0.99 // the confidence want to achieve at the end
  ) == true);

  CHECK(inliers.size()  == 7);
  CHECK(models.size()   == 3);
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

