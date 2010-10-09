
#pragma once

#include <limits>
#include <iterator>

namespace groupsac  {
namespace ransac  {
namespace prosac {

using namespace std;


//http://www.uni-koeln.de/rrzk/software/mathematik/matlab_help/techdoc/ref/nchoosek.html
//http://en.wikipedia.org/wiki/Binomial_coefficient
//Naive implementations of the factorial formula, such as the following snippet in C:
//int nchoosek(int n, int k)  {
//  return factorial(n) / (factorial(k) * factorial(n - k));
//}
//A direct implementation of the multiplicative formula works well:
unsigned long long nchoosek(unsigned n, unsigned k)
{
  if (k > n)
      return 0;

  if (k > n/2)
      k = n-k; // Take advantage of symmetry

  long double accum = 1;
  unsigned i;
  for (i = 1; i <= k; i++)
       accum = accum * (n-k+i) / i;

  return (unsigned long long) (accum + 0.5); // avoid rounding error
}

class PROSAC_handler
{
public:
  PROSAC_handler(int min_sample_num, int rounds_to_equal, const std::vector<int> & ordering)
  {
    // initialization
  	PR.exceeded = false;         
	  PR.n = min_sample_num-1; // the index of the last element in the current subset
	  PR.n_rounds = 0;         // the rounds used in the current subset
    PR.max_round = std::numeric_limits<int>::max();
		PR.T_n = 0;

    int T_N = rounds_to_equal;
    PR.T_n_ratio = T_N / (double)nchoosek(ordering.size(),min_sample_num);

    m_vec_ordering = ordering;
  }

  vector<int> fun_candidates(int nbCandidates, int round)
  {
    // if the budget in the current subset is used up
		if (PR.n_rounds >= PR.max_round)
    {
			PR.n_rounds = 0;
    }
		
		// start of a new subset
		if (PR.n_rounds == 0)
    {
			if (PR.n != m_vec_ordering.size())
      {
				PR.n = PR.n + 1;
				int T_n_1 = PR.T_n;
				PR.T_n = PR.T_n_ratio * nchoosek(PR.n, nbCandidates);
				PR.max_round = ceil((double)(PR.T_n - T_n_1));
      }
			else
      {
				PR.max_round = std::numeric_limits<int>::max(); // always use the entire data set
				PR.exceeded = true;    // when exceeeded, does not have sample from the last element
      }
    }
		
		++PR.n_rounds; // One more iteration done.
		
    std::vector<int> vec_candidates;
    for (int i=0; i < PR.n; ++i) //		candidates = ordering(1:PR.n);
    {
      vec_candidates.push_back( m_vec_ordering[i] );
    }
    return vec_candidates;
  }

private:
 struct
  {
    bool exceeded;
    int n;
    int n_rounds;
    int max_round;
    int T_n;
    double T_n_ratio;
  } PR;
 std::vector<int> m_vec_ordering;
};

}; // namespace prosac
}; // namespace ransac
}; // namespace groupsac
