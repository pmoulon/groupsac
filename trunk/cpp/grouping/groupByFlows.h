

#include <iostream>

#include "MeanShift/MeanShiftCluster.h"
#include "armadillo/include/armadillo"
using namespace arma;
// |
// | :: mat
// | :: vec

namespace groupsac  {
namespace grouping  {

/// use Optical Flow based segmentation to group the data points for GroupSAC
bool groupByFlows(const mat & xs1, const mat & xs2, double bandwidth, int & seg_num, mat & vis_map, mat & clustCent, bool bVerbose = false)
{
  using namespace std;
  //% output:
  //% seg_num -   the total number of segments
  //% vis_map -   the row is the point index, the column is the segment index
  //% clustCent - the cluster centers


  //%% generate the flow groups
  mat x_dists = xs1.row(0) - xs2.row(0);
  mat y_dists = xs1.row(1) - xs2.row(1);
  mat xs = xs1;
  xs = join_cols(xs, x_dists);
  xs = join_cols(xs, y_dists);

  mat cluster2dataCell;
  vector<int> data2cluster;
  MeanShiftCluster(xs, bandwidth, clustCent, data2cluster, cluster2dataCell);
  
  // TODO CUSTOMIZE THE SQ_DIST
  
  if (bVerbose)
  {
      cout << "clustering takes X seconds" << endl;
  }
  seg_num = clustCent.n_cols;

  // TODO implement the following :
  //-----------------------------
/*  //%% reorder the groups according to the number of the points they contain
  group_sizes = zeros(seg_num ,1);
  for (int gi=1; <i<length(group_sizes); ++gi)
  {
      group_sizes(gi) = length(clustMembsCell{gi});
  }
  [sorted idx] = sort(group_sizes, 'descend');

  //%% generate vis_map using the reordered 
  datum_num = size(xs1, 2);
  vis_map = zeros(datum_num, seg_num);
  for (int gi = 1; gi < seg_num ; ++gi)
  {
      vis_map(clustMembsCell{gi},idx==gi) = 1;
  }*/

/*      function [dists] = sqdist(x1s, x2)
          x1_num = size(x1s,2);
          weights = [1 1 10 10];
          dists = weights * ((repmat(x2,1,x1_num) - x1s).^2);    %dist squared from mean to all points still active
      end
  end*/
  //-----------------------------
  
  return true; //TODO make a better return
}
}; // namespace grouping
}; // namespace groupsac
