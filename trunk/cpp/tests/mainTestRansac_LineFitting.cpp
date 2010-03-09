#include <iostream>
#include <vector>
#include <set>
using namespace std;

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

//-- Temporary function (Must be defined more generally).
//---- Deterministic sampler
//---- Random sampler
template <typename T>
vector<int> sampler(const T & candidates, int MININUM_SAMPLES)
{
  /*vector<int> array;
  array.push_back(0);
  array.push_back(1);
  return array;*/

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

template<typename T>
T extractor(const T & data, const vector<int> & sampled)
{
  mat test;
  test.zeros(sampled.size(), data.n_cols);
  for(size_t i=0; i < sampled.size(); ++i)
    test.row(i) = data.row( sampled[i] );
  return test;
}

//-- END -- Must now be defined
//-------


int main()
{
  //-- Create the input solver :
  estimators::Solver<mat,vec> * ptrSolver = new estimators::lineFittingSolver<mat,vec>;

  //-- Create input data
  //mat dataPoints = "1 2; 2 4; 2 5; 3 6; 4 7";//"1 6; 2 5; 3 7; 4 10";
  mat dataPoints = "0 0; 1 1; 2 2; 3 3";
  /*vector<vec> models;
  ptrSolver->solve(dataPoints, models);
  ((estimators::lineFittingSolver<mat,vec>*)ptrSolver)->defaultEvaluator(models, dataPoints, 2.0);
  */

  ransac::Ransac_RobustEstimator
  (
    dataPoints, // the input data
    extractor<mat>, // How select sampled point from indices
    3,  // the number of putatives data ( ideally dataPoints.cols() )
    *ptrSolver,  // compute the underlying model given a sample set
    estimators::lineFittingSolver<mat,vec>::defaultEvaluator,  // the function to evaluate a given model
    ransac::default_fun_candidates,  // the function to select candidates from all data points
    sampler< vector<int> >, // the sampling function
    ransac::default_fun_termination, // the termination function
    1000,  // the maximum rounds for RANSAC routine
    0.95 // the confidence want to achieve at the end
  );


  delete ptrSolver;

  return 0;
}
