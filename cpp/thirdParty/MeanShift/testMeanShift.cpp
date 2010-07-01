//%testMeanShift
//%
//% Try to find nCLust onto a dataset of points.
//%

#include "armadillo/include/armadillo"
#include "MeanShiftCluster.h"
#include <iterator>

int main()
{
  using namespace arma;

  int nPtsPerClust = 250;
  int nClust  = 3;
  int totalNumPts = nPtsPerClust*nClust;
  mat m = "1 -1 1; 1 -1 -1";
  double var = .6;
  double bandwidth = .75;
  mat clustMed;

  //*** build the point set
  mat testRand = randn<mat>(2,totalNumPts);
  //testRand.load("test.mat",raw_ascii);
  mat x = var*testRand;//randn<mat>(2,totalNumPts);
  for (int i = 1; i <= nClust; ++i)
  {
    x.cols(1+(i-1)*nPtsPerClust-1,(i)*nPtsPerClust-1) = 
      x.cols(1+(i-1)*nPtsPerClust-1,(i)*nPtsPerClust-1) +
        repmat(m.col(i-1),1,nPtsPerClust);
  }
  
  //cout << endl << " x " << endl << x << endl;
  mat clustCent;
  map< int,vector<int> > cluster2dataCell;
  vector<int> data2cluster;
  MeanShiftCluster(x, bandwidth, clustCent, data2cluster, cluster2dataCell);
  
  //cout << endl;   cout << endl;
  //copy(  data2cluster.begin(),   data2cluster.end(), ostream_iterator<int>(cout, " "));
  //cout << endl;   cout << endl;


  int numClust = clustCent.n_cols;
  cout << endl << "Found " << numClust << " clusters" << endl;

  // Output matrix in a format readable for octave and matlab in order to check visually the output.
  
  /*figure(10),clf,hold on
  cVec = 'bgrcmykbgrcmykbgrcmykbgrcmyk'; % color to display computed cluster
  for k = 1:min(numClust,length(cVec))
      myMembers = clustMembsCell{k};
      myClustCen = clustCent(:,k);
      plot(x(1,myMembers),x(2,myMembers),[cVec(k) '.'])
      plot(myClustCen(1),myClustCen(2),'o','MarkerEdgeColor','k','MarkerFaceColor',cVec(k), 'MarkerSize',10)
  end
  title(['no shifting, numClust:' int2str(numClust)])*/

  return 0;
}
