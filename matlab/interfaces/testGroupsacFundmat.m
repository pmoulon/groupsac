function test_suite = testGroupsacFundmat
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple
clear GR vis_map;
global GR vis_map;

%% set up putatives, the first putative is an outliner
xs1 = [1 1; 1251 1243; 1603 923; 2067 1031; 787 484; 1355 363; 2163 743; 1875 1715;]';
xs2 = [1 1; 723 887;   1091 699; 1691 811;  447 635; 971 91;   1903 447; 1483 1555;]';

vis_map = zeros(8, 2); % (i,j)!=0 means a map from point i to group j
vis_map(1,1) = 1;      % the first putative is in group 1
vis_map(2:end,2) = 1;  % the other putatives are in group 2

%% control parameters
datum_num = size(xs1,2);
gui = false;
min_sample_num = 7;
rounds_to_equal = 200000;
max_rounds = 1000;
confidence = 0.99;
sigma = 1.0;
verbose = false;

fun_compute = fundmat7ptSolver(xs1,xs2);
fun_evaluate = fundmat7ptEvaluator(xs1,xs2,sigma);
fun_candidates = candidates_single_group(min_sample_num, rounds_to_equal, verbose);
fun_termination = group_ransac_termination(min_sample_num, max_rounds, confidence, verbose);
fun_draw = 0;

% initialize GroupSAC global variable
GR = {};
GR.cur_grps = 1;
GR.cur_cfg  = 0;
GR.initialized = 0;

[round success best_inliers ~] = ransac(datum_num, fun_compute, fun_evaluate, fun_candidates, -1, fun_termination, fun_draw, ...
    min_sample_num, max_rounds, confidence, gui, verbose);
assertTrue(success);
assertEqual((2:8)', best_inliers);

%#ok<*STOUT> 
%#ok<*DEFNU>
