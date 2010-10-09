#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <cmath>
using namespace std;

#include "CppUnitLite/TestHarness.h"
#include "ransac/ransac.h"
#include "ransac/prosac_tools.h"

using namespace groupsac;
// |
// | :: ransac

//------------------------------
// Assert that test works
//------------------------------
TEST ( Ransac_Rounds_Needed, demo )
{
    LONGS_EQUAL(1, 1);
    CHECK(true);
}


//------------------------------
// Test :
// - test function testCandidatesProsac
//------------------------------
TEST ( Ransac_Candidates_Prosac, testSimple )
{
  cout<< endl<< "[Ransac_Candidates_Prosac::testSimple]"<< endl<< endl;
  
  const int min_sample_num = 7;
  const int rounds_to_equal = 200000;
  const int nbDataPoints = 200;
  vector<int> vec_ordering;
  for (int i=0; i < nbDataPoints; ++i)
  {
     vec_ordering.push_back(i);
  }

  ransac::prosac::PROSAC_handler prosac_handler(min_sample_num, rounds_to_equal, vec_ordering);
  vector<int> vec_candidates = prosac_handler.fun_candidates(min_sample_num, 0);

  std::vector<int> vec_expected;
  for(int i=0; i < 7; ++i)
    vec_expected.push_back(i);

  CHECK(vec_candidates.size() == vec_expected.size());
  
  for(int i =0; i < vec_expected.size(); ++i)
  {
    CHECK( vec_candidates[i] == vec_expected[i] );
  }
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */

