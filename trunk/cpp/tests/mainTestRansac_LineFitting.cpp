#include <iostream>
#include <vector>
using namespace std;

#include "ransac/ransac.h"
#include "estimators/Solver.h"
#include "estimators/lineFittingSolver.h"
#include "estimators/pointToLineDist.h"

using namespace groupsac;
// |
// | :: estimators
// | :: ransac

//-- Temporary function (Must be defined more generally).
//---- Deterministic sampler
//---- Random sampler
template <typename T>
vector<int> sampler(const T & candidates, int MININUM_SAMPLES)
{
  return vector<int>();
}
class mat
{
};
class vec
{
};
template<typename T>
T extractor(const T & data, const vector<int> & sampled)
{
  return data;
}

//-- END -- Must now be defined
//-------


int main()
{
  //-- Create the input solver :
  estimators::Solver<mat,vec> * ptrSolver = new estimators::lineFittingSolver<mat,vec>;

  //-- Create input data
  mat dataPoints;
  // Todo(pmoulon) Initialize dataPoints

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
