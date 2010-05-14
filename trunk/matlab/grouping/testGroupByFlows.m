function test_suite = testGroupByFlows
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testOneCluster
xs1 = [1 2 3 4 5
       0 0 0 0 0];
xs2 = [2 3 4 5 6
       0 0 0 0 0];
bandwidth = 10;
[seg_num vis_map clustCent] = groupByFlows(xs1, xs2, bandwidth);
assertEqual(seg_num, 1);
assertEqual(vis_map, [1 1 1 1 1]');
assertEqual(clustCent, [3 0 -1 0]'); % x, y, delta_x, delta_y

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testTwoClusters
xs1 = [1  2  3  4  5  6  7  8  9 10
       0  0  0  0  0  0  0  0  0  0];
xs2 = [11 12 13 14 15 -4 -3 -2 -1 0
       0  0  0  0  0  0  0  0  0  0];
bandwidth = 10;
[seg_num vis_map clustCent] = groupByFlows(xs1, xs2, bandwidth);
assertEqual(seg_num, 2);
vis_map_expected = [1 1 1 1 1 0 0 0 0 0
                    0 0 0 0 0 1 1 1 1 1]';
assertTrue(isequal(vis_map, vis_map_expected) || isequal(vis_map, vis_map_expected(:, [2 1])));
clustCent_expected = [3 0 -10 0; 8 0 10 0]';
assertTrue(isequal(clustCent, clustCent_expected) || isequal(clustCent, clustCent_expected(:, [2 1]))); % x, y, delta_x, delta_y

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testTwoClusters2
xs1 = [1  2  3  4  5  6    7    8    9   10
       0  0  0  0  0  0    0    0    0   0];
xs2 = [2  3  4  5  6  106  107  108  109 110
       0  0  0  0  0  0    0    0    0   0];
bandwidth = 10;
[seg_num vis_map clustCent] = groupByFlows(xs1, xs2, bandwidth);
assertEqual(seg_num, 2);
vis_map_expected = [1 1 1 1 1 0 0 0 0 0
                    0 0 0 0 0 1 1 1 1 1]';
assertTrue(isequal(vis_map, vis_map_expected) || isequal(vis_map, vis_map_expected(:, [2 1])));
clustCent_expected = [8 0 -100 0; 3 0 -1 0]';
assertTrue(isequal(clustCent, clustCent_expected) || isequal(clustCent, clustCent_expected(:, [2 1]))); % x, y, delta_x, delta_y

%#ok<*STOUT> 
%#ok<*DEFNU>
