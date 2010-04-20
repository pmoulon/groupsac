
#include <vector>
#include <iostream>
#include <cmath>
#include "ransacTools.h"
using namespace std;

namespace groupsac  {
namespace ransac  {

// return the minimal rounds needed for a given data set size and a given inlier
//  number
int ransac_rounds_needed
  (
    int max_rounds,
    int min_sample_num,
    double l1mp,
    int datum_num,
    int inlier_num
   )
{
  // inlier point probability
  double w = inlier_num / datum_num;
  // outlier sample probability
  double eps_log = log(1.0 - pow(w,min_sample_num));
  if(inlier_num == 0 || eps_log == 0)
    return max_rounds;
  else
    return std::min(max_rounds, int(ceil(l1mp / eps_log)) );
}

// The default termination check for RANSAC,
//  which only depends on the rounds needed
bool  default_fun_termination
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
    static int rounds_needed; //Todo replace it by a function variable
    // (to be sure it works in multithread context)
    if ( inliers.size() > best_inliers.size() ) {
        best_inliers = inliers;
        rounds_needed = ransac_rounds_needed(max_rounds,
                                            iSolverMinimalSamples,
                                            logConfidence,
                                            iPutativesNumber,
                                            inliers.size());
        cout<<"global round="<<round
            <<"\tbest="<<best_inliers.size()
            <<"\trounds_needed="<<rounds_needed<<endl;
    }
    return round >= rounds_needed;
}

// default fun_candidates returns all the point indices (0-based) as candidates
vector<int> default_fun_candidates(int nbCandidates, int round)
{
    vector<int> indices;
    for (unsigned int i=0; i<nbCandidates; ++i)
        indices.push_back(i);
    return indices;
}

// ransac: the common routine for RANSAC
template< typename Data,
          typename DataExtractor,
          typename Solver,
          typename Evaluator,
          typename CandidatesSelector,
          typename Sampler,
          typename Termination >
bool Ransac_RobustEstimator
  (
    const Data & data,      // the input data
    const DataExtractor & extractor, // How extract indexed data from inputData
    int iPutativesNumber,   // the number of putatives
    const Solver & solver,  // compute the underlying model given a sample set
    const Evaluator & evaluator,  // the function to evaluate a given model
    //func to select candidates from data pts
    const CandidatesSelector & candidatesSelector,
    const Sampler & sampler,  // the sampling function
    const Termination & fun_termination,  // the termination function
    int imax_rounds,          // the maximum rounds for RANSAC routine
    // Output parameters :
    vector<int> & vec_inliers,  // Inlier to the final solution
    vector<typename Solver::ModelType> & vec_models, // Model(s) that fit the inlier array
    // Statistical parameter
    double confidence = 0.95, // the confidence want to achieve at the end
    double sigma = 1.0        // noise standard deviation
  )
{
  // parameters
  int veri_num = 0;  // the total number of verifications made
  double l1mp = log(1.0 - confidence);

  // the main ransac routine
  bool bSuccess = false;     // whether RANSAC is successful at last
  int round = 0;            // current round
  vector<int> best_inliers; // the best inliers so far
  while(!bSuccess)
  {
    ++round;
    if ( (round%100) == 0 ) {
        cout<<"global round=" << round
            << "\tbest=" << best_inliers.size() << endl;
    }

    // get the candidates for sampling
    vector<int> candidates = candidatesSelector(iPutativesNumber, round);
    // get sample indices from candidates
    vector<int> sampled = sampler(candidates, solver.get_MINIMUM_SAMPLES());

    // For GroupSAC, return inlier in the current group configuration
    vector<typename Solver::ModelType> vec_model;
    // compute the new model
    solver.solve( extractor(data,sampled) , vec_model);
    // compute the inliers for the array of models.
    vector<int> inliers = evaluator(vec_model, extractor(data,candidates),
                                    ransac_threshold(1,sigma));
    veri_num += candidates.size();

    if( fun_termination(best_inliers, inliers,
                          round, imax_rounds,
                          l1mp, solver.get_MINIMUM_SAMPLES(),
                          iPutativesNumber)
      )  // check the termination condition
    {
      bSuccess = true;

      // finalize the model and inliers
      vector<typename Solver::ModelType> vec_model_finalize;
      solver.solve( extractor(data,best_inliers), vec_model_finalize);
      // compute the inliers for the array of model.
      vec_inliers = evaluator(vec_model_finalize,
                                extractor(data,candidates),
                                ransac_threshold(1,sigma));
      vec_models = vec_model_finalize;
      //Handle the best model at most inliers size... But not better quality (minus residuals)
      veri_num += candidates.size();
      cout<< "quiting ransac...found : " << best_inliers.size()
          << " inliers after : " << round << " rounds" << endl;
    }
  }
  return bSuccess;
}
}; // namespace ransac
}; // namespace groupsac
