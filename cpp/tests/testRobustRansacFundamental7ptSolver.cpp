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
#include "vgg/vgg_example_scene.h" // Importation of pre-computed data

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
// - Robust solver with Fundamental7ptSolver on 7 points.
// - Assert the validity of the computed models.
// - Assert inliers indexes are valid.
//------------------------------
TEST ( Fundamental7ptFittingRobustSolver, Fundamental7pt )
{
  cout<< endl<< "[Fundamental7ptFittingRobustSolver::Fundamental7pt]"
    << endl<< endl;
  //-- Create the input solver (use auto_ptr for automatic delete of the object):
  auto_ptr< estimators::Solver<mat,mat> > ptrSolver(
    new estimators::Fundamental7ptSolver<mat,mat>);

  //-- Create input data
  mat dataPoints =
    "723 887 1251 1243;\
    1091 699 1603 923;\
    1691 811 2067 1031;\
    447 635 787 484;\
    971  91 1355 363;\
    1903   447 2163  743;\
    1483 1555 1875 1715;\
    0 1 100 125"; // outlier

  dataPoints=trans(dataPoints);

  vector<int> inliers;
  vector<mat> models;

  CHECK(
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
    10,  // the maximum rounds for RANSAC routine
    inliers, // inliers to the final solution
    models, // models array that fit input data
    0.95 // the confidence want to achieve at the end
  ) == true);

  CHECK(inliers.size()  == 7);
  CHECK(models.size()   == 3);
}

//------------------------------
// Test : (With VGG oxford group precomputed data).
// - Robust solver with Fundamental7ptSolver on 7 points.
// - Assert the validity of the computed models.
// - Assert inliers indexes are valid.
//------------------------------
TEST ( Fundamental7ptFittingRobustSolver, Fundamental7pt_VGG )
{
  cout<< endl<< "[Fundamental7ptFittingRobustSolver::Fundamental7pt_VGG]"
    << endl<< endl;

  // Load data from pre-computed data from VGG oxford group
  // Use view1P view2P
  // Use view1x view2x
  // Use Xi
  mat F = vgg_F_from_P(view1P, view2P);

  //-- Count how many point correspondence we could add from input data
  int cpt = 0;
  for (int i = 0; i< Xi.n_cols; ++i)
  {
    if (Xi(0,i) != 0 && Xi(1,i) != 0)
      ++cpt;
  }
  //-- Parse point into Points coordinates container
  mat dataPoints = zeros(4,cpt+3); // + 3 outliers
  cpt = 0;
  for (int i = 0; i< Xi.n_cols; ++i)
  {
    int n1 = Xi(0,i),
        n2 = Xi(1,i);
    if (n1 != 0 && n2 != 0)
    {
      mat temp = zeros(4,1);
      temp.submat(0,0,1,0) = view1x.col(n1-1); // -1 => matlab index to c++
      temp.submat(2,0,3,0) = view2x.col(n2-1);
      dataPoints.col(cpt) = temp;
      ++cpt;
    }
  }
  int inlierExpectedNumber = cpt;
  //-- Add outliers
  dataPoints.col(cpt) = mat("1; 200; 100; 2");cpt++;
  dataPoints.col(cpt) = mat("30; 600; 10; 200");cpt++;
  dataPoints.col(cpt) = mat("200; 6; 123; 65");
  
  //-- Create the input solver (use auto_ptr for automatic delete of the object):
  auto_ptr< estimators::Solver<mat,mat> > ptrSolver(
    new estimators::Fundamental7ptSolver<mat,mat>);

  vector<int> inliers;
  vector<mat> models;

  CHECK(
  ransac::Ransac_RobustEstimator
  (
    dataPoints, // the input data
    estimators::Fundamental7ptSolver<mat,mat>::extractor, // How select sampled point from indices
    dataPoints.n_cols,  // the number of putatives data
    *(ptrSolver.get()),  // compute the underlying model given a sample set
    estimators::Fundamental7ptSolver<mat,mat>::defaultEvaluator,  // the function to evaluate a given model
    ransac::default_fun_candidates,  // the function to select candidates from all data points
    sampler< vector<int> >, // the sampling function
    ransac::default_fun_termination, // the termination function
    1000,     // the maximum rounds for RANSAC routine
    inliers,  // inliers to the final solution
    models,   // models array that fit input data
    0.95,     // the confidence want to achieve at the end
    1.0       // noise standard deviation
  ) == true);

  CHECK(inliers.size() == inlierExpectedNumber);
}


/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

