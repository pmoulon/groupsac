
#include <vector>
#include <iostream>
using namespace std;

// The default termination check for RANSAC,
//  which only depends on the rounds needed
bool
template<Model>
  default_termination
  (
    vector<int> & best_inliers,
    const vector<int> & inliers,
    const Model &  model,
    int round
  )
    int rounds_needed; //??? PM what is persistent keyword use in the matlab code : equivalent to static keyword ???
    if ( inliers.size() > best_inliers.size() ) {
        best_inliers = inliers;
        rounds_needed = ransac_rounds_needed(max_rounds, min_sample_num, l1mp, datum_num, inliers.size()); //Todo : to define
        cout<<"global round=" <<round<<"\tbest="<<best_inliers.size()<<"\trounds_needed="<<rounds_needed<<endl;
    }
    return round >= rounds_needed;
}

// default fun_candidates returns all the point indices as candidates
vector<int> default_fun_candidates(vector<int> & candidates)
{
    return candidates;
}

// ransac: the common routine for RANSAC
void
template<Solver, Evaluator, CandidatesSelector, Sampler>
  Ransac_RobustEstimator<Solver, Evaluator, CandidatesSelector, Sampler>
  (
    int iPutativesNumber,  // the number of putatives
    const Solver & solver,  // compute the underlying model given a sample set
    const Evaluator & evaluator,  // the function to evaluate a given model
    const CandidatesSelector & candidatesSelector,  // the function to select candidates from all data points
    const Sampler & sampler, // the sampling function
    // PM -> I purpose to encapsulate this term in the solver. solver::MINIMUM_SAMPLES
    // //   min_sample_num // the size of a minimum sample
    int imax_rounds,  // the maximum rounds for RANSAC routine
    double confidence // the confidence want to achieve at the end
  ) 
{

  // parameters
  int veri_num = 0;  // the total number of verifications made
  //round_per_draw = 1;
  double l1mp = log(1.0 - confidence);

  // the main ransac routine
  bool success = false; // whether RANSAC is successful at last
  int round = 0;  // current round
  vector<int> best_inliers; // the best inliers so far
  while(1) // PM : I prefer to put something here like while(!end)
  {    
      ++round;
      if ( (round%100) == 0 ) {
          cout<<"global round=" << round << "\tbest=" << best_inliers.size() << endl;
      }
      
      vector<int> candidates = candidatesSelector(round);       // get the candidates for sampling
      vector<int> sampled = sampler(candidates, Solver::MININUM_SAMPLES);// get sample indices from candidates
      
      // For GroupSAC, return inlier in the current group configuration
      vector<Solver:Model> model = solver(sampled); // compute the new model
      //??????????? // PM : What the program do if many models are computed ???????
      //PM : For each computed Model:
      {
        vector<int> inliers = evaluator(model, candidates); // compute the inliers for the new model.
        //...
      }
      veri_num += candidates.size();
      
      /*if gui && mod(round,round_per_draw) == 0
          fun_draw(sampled);
      end*/
      
      if( fun_termination(best_inliers, inliers, model, round) )  // check the termination condition
      {
        //if gui fun_draw(sampled);  end                  // always draw the best sample at the end
        success = true;
          
        // finalize the model and inliers
        vector<Solver:Model> model = solver(sampled);
        //PM : For each computed Model:
        {
          vector<int> inliers = evaluator(model, candidates); // compute the inliers for the new model.
          //...
        }
        veri_num += veri_num + candidates.size();
        cout<< "quiting ransac...found : " << best_inliers.size() 
            << " inliers after : " << round << " rounds" << endl;
        break;
    }
  }
}



