#ifndef GROUPSAC_ESTIMATORS_LINEFITTINGSOLVER_H
#define GROUPSAC_ESTIMATORS_LINEFITTINGSOLVER_H

#include <iostream>
#include <vector>
#include "armadillo/include/armadillo"
#include "pointToLineDist.h"
#include "Solver.h"
using namespace std;
using namespace arma;

namespace groupsac  {
namespace estimators  {

// Fit a 2D line with to a set of points
// Specifically, find a and b in the model y = ax + b
template<typename T = mat, typename Model = vec>
class lineFittingSolver : public Solver<T,Model>
{
  /// At least two point are necessary to solve the line equation y = ax+b
  enum { MINIMUM_SAMPLES = 2 };
public :

  int get_MINIMUM_SAMPLES() const {return MINIMUM_SAMPLES;}
  /// See groupsac::estimators::Solver
  bool solve(const T & candidates, vector<Model> & model) const
  {
      cout << "Points used for the estimation:" << endl;
      cout << candidates << endl;

      // Build matrices to solve Ax = b problem:
      vec b(candidates.n_rows);
      mat A(candidates.n_rows, 2);
      b = candidates.col(1);
      A.col(0).fill(1.0);
      A.col(1) = candidates.col(0);

      // Compute least-squares solution:
      vec X;
      if ( ::solve(X, A, b) )
      {
        cout << "solution:" << endl << X << endl;
        std::swap(X(0), X(1));
        model.push_back(X);
        return true;
      }
      else
      {
        cout << "ERROR : cannot find a solution" << endl;
        return false;
      }
      return false;
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
  static vector<int> defaultEvaluator(vector<Model> & model, const T & candidates, double threshold)
  {
    vector<int> inliers;
    // For each model compute the number of inliers and the indices of the inliers.
    // Return the longest inliers vector.
    // must use the pointToLineDist.h file.
    for (size_t i=0; i < model.size(); ++i)
    {
      const Model & modelToTest = model[i];
      for (size_t j=0; j < candidates.n_rows; ++j)
      {
        double dist = pt2LineDist( modelToTest, trans(candidates.row(j)) );
        if (dist < threshold)
          inliers.push_back(i);
      }
    }
    return inliers;
  }
};

}; // namespace estimators
}; // namespace groupsac

#endif //GROUPSAC_ESTIMATORS_LINEFITTINGSOLVER_H
