#ifndef GROUPSAC_ESTIMATORS_LINEFITTINGSOLVER_H
#define GROUPSAC_ESTIMATORS_LINEFITTINGSOLVER_H

#include <iostream>
#include <vector>
#include "Solver.h"
//#include "armadillo"
using namespace std;
//using namespace arma;

class mat;
class vec;

namespace groupsac  {
namespace estimators  {

// Fit a 2D line with to a set of points
// Specifically, find a and b in the model y = ax + b
template<typename T = mat, typename Model = vec>
class lineFittingSolver : public Solver<T,Model>
{
public :
  /// At least two point are necessary to solve the line equation y = ax+b
  enum { MINIMUM_SAMPLES = 2 };
  
  /// See groupsac::estimators::Solver
  bool solve(const T & candidates, vector<Model> & model)
  {
      cout << "Points used for the estimation:" << endl;
      cout << candidates << endl;

      // Build matrices to solve Ax = b problem:
      vec b(candidates.n_rows);
      mat A(candidates.n_rows, 2);
      for(u32 i=0; i<candidates.n_rows; ++i)
      {
        b(i)   = candidates(i,1);

        A(i,0) = 1;
        A(i,1) = candidates(i,0);
      }
      // Compute least-squares solution:
      vec solution = solve(A,b);
  
      cout << "solution:" << endl;
      cout << solution << endl;
  }

  /**
  * Return the candidates that are estmated as inliers to the best model
  *
  * \param[in] model (The model(s) that fit the data).
  * \param[in] candidates (The input data).  
  *
  * \return The list of point that are considered as inliers
  * \ /!\ Note we don't have a criteria or threshold to consider inlier/outlier spaces
  */
  static vector<int> defaultEvaluator(vector<Model> & model, const T & candidates)
  {
    // For each model compute the number of inliers and the indices of the inliers.
    // Return the longest inliers vector.
    // must use the pointToLineDist.h file.
    return vector<int>;
  }
};

}; // namespace estimators
}; // namespace groupsac

#endif //GROUPSAC_ESTIMATORS_LINEFITTINGSOLVER_H
