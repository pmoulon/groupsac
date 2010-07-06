#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <cmath>
using namespace std;

#include "CppUnitLite/TestHarness.h"
#include "ransac/ransac.h"

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
// - test function ransacRoundsNeeded
//------------------------------
TEST ( Ransac_Rounds_Needed, testSimple )
{
  cout<< endl<< "[Ransac_Rounds_Needed::testSimple]"<< endl<< endl;
  int max_rounds = 1e5;
  int min_sample_num = 7;
  double l1mp = log(1 - 0.99);
  int datum_num = 200;
  int inlier_num = 120;
  int rounds = ransac::ransac_rounds_needed(max_rounds, min_sample_num, l1mp, datum_num, inlier_num);
  CHECK(ceil(l1mp/ log(1.0-pow(120.0/200.0,7))) == rounds);
}

//------------------------------
// Test :
// - test function ransacRoundsNeeded with noisy data
//------------------------------
TEST ( Ransac_Rounds_Needed, testWithNoise )
{
  cout<< endl<< "[Ransac_Rounds_Needed::testWithNoise]"<< endl<< endl;
  int max_rounds = 1;
  int min_sample_num = 7;
  double l1mp = log(1 - 0.99);
  int datum_num = 200;
  int inlier_num = 120;
  int rounds = ransac::ransac_rounds_needed(max_rounds, min_sample_num, l1mp, datum_num, inlier_num);
  CHECK(1 == rounds);
}

/* ************************************************************************* */
int main() { TestResult tr; return TestRegistry::runAllTests(tr);}
/* ************************************************************************* */
