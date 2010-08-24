
#pragma once

#include <limits>
#include <iterator>

#include "non_randomness.h"

namespace groupsac  {
namespace ransac  {
// namespace prosac

using namespace std;

class PROSAC_handler
{

  public:
  
  bool fun_prosac_termination
    (
      vector<int> & best_inliers,
      const vector<int> & inliers,
      int round,
      int max_rounds,
      double logConfidence,
      int iSolverMinimalSamples,
      int iPutativesNumber
    )
  {
    const int min_sample_num = iSolverMinimalSamples;
    const double l1mp = logConfidence;
    // first update the minimal inlier we need for non-randomness if we start a new group configration
    if (PR.n_rounds == 1)
    {
      min_inlier = non_randomness(min_sample_num, PR.n);
      rounds_needed = ransac_rounds_needed(std::numeric_limits<int>::max(), min_sample_num, l1mp, PR.n, best_inliers.size());
      cout << "n: "               << PR.n << endl
           << "round: "           << PR.n_rounds << endl
           << "inliers :"         << best_inliers.size() << endl
           << "non_randomness: "  << min_inlier << endl
           << "rounds needed: "   << rounds_needed << endl
           << "allowed: "         << PR.max_round << endl;
    }

    if (inliers.size() > best_inliers.size())
    {
      best_inliers = inliers;
      rounds_needed = ransac_rounds_needed(std::numeric_limits<int>::max(), min_sample_num, l1mp, PR.n, inliers.size());
      cout << "n: "               << PR.n << endl
           << "round: "           << PR.n_rounds << endl
           << "inliers :"         << best_inliers.size() << endl
           << "non_randomness: "  << min_inlier << endl
           << "rounds needed: "   << rounds_needed << endl
           << "allowed: "         << PR.max_round << endl;
    }

    bool bTerminate = (inliers.size() > min_inlier && round >= rounds_needed) || round > max_rounds;

    if (bTerminate)
    {
      cout << "ready to terminate when non_randomness: " << endl;
      copy(inliers.begin(), inliers.end(), ostream_iterator<int>(cout, " "));
      cout << endl
           << "rounds needed: " << rounds_needed << endl
           << "min_inlier: " << min_inlier << endl;
    }
    return bTerminate;
  }
  
  
  private:
  int min_inlier;
  int rounds_needed;
  
  struct
  {
    int n;
    int n_rounds;
    int max_round;
  } PR;
};

}; // namespace ransac
}; // namespace groupsac
