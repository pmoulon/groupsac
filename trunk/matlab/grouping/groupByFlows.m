% use image segmentation to group the data points for GroupSAC
function [seg_num vis_map clustCent] = groupByFlows(xs1, xs2, bandwidth, verbose)
% output:
% seg_num -   the total number of segments
% vis_map -   the row is the point index, the column is the segment index
% clustCent - the cluster centers

if ~exist('verbose', 'var')
    verbose = false;
end

%% generate the flow groups
x_dists = xs1(1,:) - xs2(1,:);
y_dists = xs1(2,:) - xs2(2,:);
xs = [xs1(1:2, :); x_dists; y_dists];
tic
[clustCent,point2cluster,clustMembsCell] = MeanShiftCluster(xs, bandwidth, @sqdist);
if verbose 
    fprintf(1,'clustering takes %g seconds\n',toc);
end
seg_num = length(clustMembsCell);

%% reorder the groups according to the number of the points they contain
group_sizes = zeros(seg_num ,1);
for gi=1:length(group_sizes)
    group_sizes(gi) = length(clustMembsCell{gi});
end
[sorted idx] = sort(group_sizes, 'descend');

%% generate vis_map using the reordered 
datum_num = size(xs1, 2);
vis_map = zeros(datum_num, seg_num);
for gi = 1:seg_num 
    vis_map(clustMembsCell{gi},idx==gi) = 1;
end

    function [dists] = sqdist(x1s, x2)
        x1_num = size(x1s,2);
        weights = [1 1 10 10];
        dists = weights * ((repmat(x2,1,x1_num) - x1s).^2);    %dist squared from mean to all points still active
    end
end