#include <iostream>
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
  return vector<int>;
}

void main()
{
  //-- Create the input solver :
  estimators::Solver<mat,vec> * ptrSolver = new estimators::lineFittingSolver<mat,vec>();

  ransac::Ransac_RobustEstimator
  (
    3,  // the number of putatives
    *ptrSolver,  // compute the underlying model given a sample set
    estimators::lineFittingSolver<mat,vec>::defaultEvaluator,  // the function to evaluate a given model
    ransac::default_fun_candidates,  // the function to select candidates from all data points
    sampler<mat>, // the sampling function
    1000,  // the maximum rounds for RANSAC routine
    0.95 // the confidence want to achieve at the end
  );


  delete ptrSolver;
}