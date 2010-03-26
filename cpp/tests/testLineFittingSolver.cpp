/*
 * testLineFitting.cpp
 *
 *   Created on: Mar 25, 2010
 *       Author: nikai
 *  Description: unit tests for line fitting
 */

#include "CppUnitLite/TestHarness.h"
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

#include <memory>
using namespace std;

TEST ( LineFittingSolver, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}

TEST ( LineFittingSolver, solve )
{
  cout<< endl << "[LineFittingSolver::Solver]"  << endl << endl;
  // Estimate the line equation from a set of points :
  mat dataPoints = "0 0; 1 1; 2 2; 3 3";
  vector<vec> models;
  estimators::Solver<mat,vec> * ptrSolver = new estimators::lineFittingSolver<mat,vec>;
  ptrSolver->solve(dataPoints, models);
  // Compute inliers indices
  vector<int> inliersIndices = ((estimators::lineFittingSolver<mat,vec>*)ptrSolver)->defaultEvaluator(models, dataPoints, 2.0);
  delete ptrSolver;

  CHECK(models.size() == 1);
  // ax+b=y
  DOUBLES_EQUAL(models[0](0),1.0,1e-8);
  DOUBLES_EQUAL(models[0](1),0.0,1e-8);
  CHECK(inliersIndices.size()==4);
  for(unsigned int i=0;i<inliersIndices.size();++i)
    CHECK(inliersIndices[i]==i);
}

TEST ( LineFittingSolver, minimalSolution2pt )
{
  //Estimate the line equation from a set of points :
  mat dataPoints = "0 0; 1 0";
  vector<vec> models;
  estimators::Solver<mat,vec> * ptrSolver = new estimators::lineFittingSolver<mat,vec>;
  ptrSolver->solve(dataPoints, models);
  //((estimators::lineFittingSolver<mat,vec>*)ptrSolver)->defaultEvaluator(models, dataPoints, 2.0);
  delete ptrSolver;

  /// !!!! TO DEBUG !!!!!
  CHECK(models.size() == 1);
  // ax+b=y
  //DOUBLES_EQUAL(models[0](0),0.0,1e-8);
  //DOUBLES_EQUAL(models[0](1),1.0,1e-8);
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

