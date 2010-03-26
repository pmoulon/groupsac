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
// |
// | :: auto_ptr<T>
using namespace std;

//------------------------------
// Assert that test works
//------------------------------
TEST ( LineFittingSolver, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}

//------------------------------
// Test :
// - LineFittingSolver on N points.
// - Assert the validity of the computed model
// - Assert that all point that have been use for estimation are inliers 
//    to the computed solution.
//------------------------------
TEST ( LineFittingSolver, solveNpt )
{
  cout<< endl << "[LineFittingSolver::solveNpt]"  << endl << endl;
  // Estimate the line equation from a set of points :
  mat dataPoints = "0 0; 1 1; 2 2; 3 3";
  vector<vec> models;
  auto_ptr< estimators::Solver<mat,vec> > ptrSolver
    ( new estimators::lineFittingSolver<mat,vec> );

  ptrSolver->solve(dataPoints, models);

  //-- CHeck Model
  CHECK(models.size() == 1);
  // ax+b=y
  DOUBLES_EQUAL(models[0](0),1.0,1e-8);
  DOUBLES_EQUAL(models[0](1),0.0,1e-8);

  //-- Inliers  
  // Compute inliers indices
  vector<int> inliersIndices = 
    ((estimators::lineFittingSolver<mat,vec>*)
      ptrSolver.get())->defaultEvaluator(models, dataPoints, 2.0);
  CHECK(inliersIndices.size()==4);
  for(unsigned int i=0;i<inliersIndices.size();++i)
    CHECK(inliersIndices[i]==i);
}

//------------------------------
// Test :
// - LineFittingSolver on 2 points (minimal solution).
// - Assert the validity of the computed model
//------------------------------
TEST ( LineFittingSolver, minimalSolution2pt )
{
  cout<< endl << "[LineFittingSolver::minimalSolution2pt]"  << endl << endl;
  //Estimate the line equation from a set of points :
  mat dataPoints = "0 0; 1 1";
  vector<vec> models;
  auto_ptr< estimators::Solver<mat,vec> > ptrSolver
    (new estimators::lineFittingSolver<mat,vec>);

  ptrSolver->solve(dataPoints, models);

  CHECK(models.size() == 1);
  // ax+b=y
  DOUBLES_EQUAL(models[0](0),1.0,1e-8);
  DOUBLES_EQUAL(models[0](1),0.0,1e-8);
}

//------------------------------
// Test :
// - LineFittingSolver on 2 points (minimal solution) (HORIZONTAL LINE).
// - Assert the validity of the computed model
//------------------------------
TEST ( LineFittingSolver, minimalSolution2ptHorizontal )
{
  cout<< endl << "[LineFittingSolver::minimalSolution2ptHorizontal]"
      << endl << endl;
  //Estimate the line equation from a set of points :
  mat dataPoints = "0 1; 1 1";
  vector<vec> models;
  auto_ptr< estimators::Solver<mat,vec> > ptrSolver
    (new estimators::lineFittingSolver<mat,vec>);

  ptrSolver->solve(dataPoints, models);

  CHECK(models.size() == 1);
  // ax+b=y
  DOUBLES_EQUAL(models[0](0),0.0,1e-8);
  DOUBLES_EQUAL(models[0](1),1.0,1e-8);
}

//------------------------------
// Test :
// - pt2LineDist function.
// - Assert the validity of the computed distance
//------------------------------
TEST ( LineFittingSolver, pt2LineDist1 )
{
  cout<< endl << "[LineFittingSolver::pt2LineDist1]"  << endl << endl;
  vec ab = "1 0";
  vec pt = "1 0";
  DOUBLES_EQUAL( estimators::pt2LineDist(ab,pt),
                 1.0/sqrt(2.0),
                 1e-8);  
}

//------------------------------
// Test :
// - pt2LineDist function.
// - Assert the validity of the computed distance
//------------------------------
TEST ( LineFittingSolver, pt2LineDist2 )
{
  cout<< endl << "[LineFittingSolver::pt2LineDist2]"  << endl << endl;
  vec ab = "0 2";
  vec pt = "1.5 1";
  DOUBLES_EQUAL( estimators::pt2LineDist(ab,pt),
                 1.0,
                 1e-8);  
}

//------------------------------
// Test :
// - pt2LineDist function.
// - Assert the validity of the computed distance
//------------------------------
TEST ( LineFittingSolver, pt2LineDist3 )
{
  cout<< endl << "[LineFittingSolver::pt2LineDist3]"  << endl << endl;
  vec ab = "0 2";
  vec pt = "1.5 3";
  DOUBLES_EQUAL( estimators::pt2LineDist(ab,pt),
                 1.0,
                 1e-8);  
}


/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

