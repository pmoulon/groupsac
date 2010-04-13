/*
 * testR.cppobustFundamental7ptSolver.cpp
 *
 *   Created on: Apr 10, 2010
 *       Author: pmoulon
 *  Description: unit tests for fundamental 7point fitting inside Robust Ransac Algorithm
 */

#include "CppUnitLite/TestHarness.h"
#include "estimators/Solver.h"
#include "estimators/Fundamental7ptSolver.h"
#include "ransac/ransac.h"

#include <vector>
#include <set>

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


//-- Temporary function (Must be defined more generally).
//---- (not yet done) Deterministic sampler
//---- x Random sampler
template <typename T>
vector<int> sampler(const T & candidates, int MININUM_SAMPLES)
{
  vector<int> array;
  int i = 0;
  std::set<int> sample_set;
  while (i < MININUM_SAMPLES)
  {
    int random_value_in_range = rand() % candidates.size();
    if (sample_set.insert(random_value_in_range).second)
    {
      array.push_back(random_value_in_range);
      ++i;
    }
  }
  return array;
}


//-- END -- Must now be defined
//-------

//------------------------------
// Assert that test works
//------------------------------
TEST ( Fundamental7ptFittingRobustSolver, demo )
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
TEST ( Fundamental7ptFittingRobustSolver, Fundamental7pt )
{
  //-- Create the input solver (use auto_ptr for automatic delete of the object):
  auto_ptr< estimators::Solver<mat,mat> > ptrSolver(new estimators::Fundamental7ptSolver<mat,mat>);

  //-- Create input data
  mat dataPoints = 
    "723 887 1251 1243;\
    1091 699 1603 923;\
    1691 811 2067 1031;\
    447 635 787 484;\
    971  91 1355 363;\
    1903   447 2163  743;\
    1483 1555 1875 1715;";

  dataPoints=trans(dataPoints);

  ransac::Ransac_RobustEstimator
  (
    dataPoints, // the input data
    estimators::Fundamental7ptSolver<mat,mat>::extractor, // How select sampled point from indices
    dataPoints.n_cols,  // the number of putatives data ( ideally dataPoints.cols() )
    *(ptrSolver.get()),  // compute the underlying model given a sample set
    estimators::Fundamental7ptSolver<mat,mat>::defaultEvaluator,  // the function to evaluate a given model
    ransac::default_fun_candidates,  // the function to select candidates from all data points
    sampler< vector<int> >, // the sampling function
    ransac::default_fun_termination, // the termination function
    100,  // the maximum rounds for RANSAC routine
    0.95 // the confidence want to achieve at the end
  );
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

