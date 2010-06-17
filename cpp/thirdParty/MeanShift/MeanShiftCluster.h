
#include "armadillo/include/armadillo"
using namespace arma;
#include <vector>
using namespace std;

/// L2 Distance between two matrices
mat sqdist(const mat & x1s, const mat & x2)
{
  int x1_num = x1s.n_cols;
  return sum( pow( (repmat(x2,1,x1_num) - x1s),2 ) );    //dist squared
}
    
bool MeanShiftCluster(const mat & dataPts, double bandWidth, mat & clustCent, vector<int> & data2cluster, mat & cluster2dataCell)
{
  /*perform MeanShift Clustering of data using a flat kernel
  %
  % ---INPUT---
  % dataPts           - input data, (numDim x numPts)
  % bandWidth         - is bandwidth parameter (scalar)
  % plotFlag          - display output if 2 or 3 D    (logical)
  % ---OUTPUT---
  % clustCent         - is locations of cluster centers (numDim x numClust)
  % data2cluster      - for every data point which cluster it belongs to (numPts)
  % cluster2dataCell  - for every cluster which points are in it (numClust)
  %
  % Bryan Feldman 02/24/06
  % MeanShift first appears in
  % K. Funkunaga and L.D. Hosteler, "The Estimation of the Gradient of a
  % Density Function, with Applications in Pattern Recognition" */

  bool plotFlag = false;

  //%**** Initialize stuff ***
  int numDim    = dataPts.n_rows;
  int numPts    = dataPts.n_cols;
  int numClust  = 0;
  double bandSq = bandWidth*bandWidth;

  vector<int> initPtInds(numPts,0);

  for (int i=0; i <numPts; ++i) initPtInds[i] = i;

  double stopThresh = (1e-3*bandWidth) *(1e-3*bandWidth);   //when mean has converged
  vector<int> beenVisitedFlag(numPts,0);                    //track if a points been seen already
  int numInitPts = numPts;                                  //number of points to posibaly use as initilization points
  mat clusterVotes(numPts,1);                               //used to resolve conflicts on cluster membership


  while (numInitPts!=0)
  {    
    int tempInd     = ceil( (numInitPts-1)%int(rand()));// pick a random seed point
    int stInd = initPtInds[tempInd];          // use this point as start of mean
    mat myMean = dataPts.col(stInd);          // intialize mean to this points location
    vector<int> myMembers;                    // points that will get added to this cluster
    mat thisClusterVotes(numPts,1);           // used to resolve conflicts on cluster membership

    while (1)     //loop until convergence
    {        
      mat sqDistToAll = sqdist(dataPts, myMean); // dist squared from mean to all points still active

      mat toMean;
      //select point within bandwidth
      vector<int> inInds;
      for(int i=0; i < numPts; ++i) // (MATLAB => ) inInds      = find(sqDistToAll < bandSq);
      {
        if (sqDistToAll(i) < bandSq)
        {
          inInds.push_back(i);
          thisClusterVotes(i) += 1;// add a vote for all the in points belonging to this cluster

          if(toMean.n_rows == 0) 
          toMean = dataPts.col(i);
          else
          toMean  = join_rows(toMean,dataPts.col(i)); // to compute the newMean

          myMembers.push_back(i); // add any point within bandWidth to the cluster
          beenVisitedFlag[i] = 1; // mark that these points have been visited
          // it could be cool if we have dynamic_bitset (with indInds)
        }
      }

      mat myOldMean = myMean;               // save the old mean
      myMean        = mean(toMean,1);       // compute the new mean

      //%**** if mean doesn't move much stop this cluster ***
      double meanDist = as_scalar(sqdist(myMean, myOldMean));
      if ( meanDist < stopThresh )
      {       
        //check for merge posibilities
        int mergeWith = 0;
        for (int cN = 0; cN < numClust; ++cN)
        {
          double sqdistToOther = as_scalar( sqdist(myMean, clustCent.col(cN)) );//distance from posible new clust max to old clust max
          if (sqdistToOther < bandSq / 4.0)                   //if its within bandwidth/2 merge new and old
          {
            mergeWith = cN;
            break;
          }
        }

        if (mergeWith > 0)    // something to merge
        {
          clustCent.col(mergeWith)       = 0.5*(myMean+clustCent.col(mergeWith));             //record the max as the mean of the two merged (I know biased twoards new ones)
          clusterVotes.col(mergeWith)    = clusterVotes.col(mergeWith) + thisClusterVotes;    //add these votes to the merged cluster
        }
        else    //its a new cluster
        {
          numClust = numClust+1;                   //increment clusters

          //record the mean
          if(clustCent.n_rows == 0) 
            clustCent = myMean;
          else
            clustCent  = join_rows(clustCent, myMean); // to compute the newMean

          clusterVotes = join_rows(clusterVotes, thisClusterVotes);
        }
        break;
      }
    }

    // count number of active points in set
    numInitPts = 0;
    initPtInds.clear();
    for (int i=0; i < beenVisitedFlag.size(); ++i)
    {
      if (beenVisitedFlag[i]==0)
      {
        initPtInds.push_back(i);
        ++numInitPts;
      }
    }
  }

  //[val,data2cluster] = max(clusterVotes,[],1);                // a point belongs to the cluster with the most votes


  // %*** If they want the cluster2data cell find it for them
  /*if nargout > 2
  cluster2dataCell = cell(numClust,1);
  for cN = 1:numClust
  myMembers = find(data2cluster == cN);
  cluster2dataCell{cN} = myMembers;
  end
  end*/

  // %% the squared distance function
  /*    function [dists] = default_sqdist(x1s, x2)
  x1_num = size(x1s,2);
  dists = sum((repmat(x2,1,x1_num) - x1s).^2);    // %dist squared from mean to all points still active
  end
  end*/

}

