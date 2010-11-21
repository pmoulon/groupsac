function test_suite = testProsacFundmat
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple
clear PR;
global PR;

%% set up putatives
xs1 = [1251 1243; 1603 923; 2067 1031; 787 484; 1355 363; 2163  743; 1875 1715]';
xs2 = [723 887; 1091 699; 1691 811; 447 635; 971 91; 1903 447; 1483 1555]';
ordering = (1 : 7)';

%% control parameters
datum_num = size(xs1,2);
early = 0;
gui = false;
sigma = 1.0;
min_sample_num = 7;
max_rounds = 5000;
confidence = 0.99;
rounds_to_equal = 200000;
verbose = false;
fun_compute = fundmat7ptSolver(xs1,xs2);
fun_evaluate = fundmat7ptEvaluator(xs1,xs2,sigma);
fun_candidates = candidatesProsac(min_sample_num, rounds_to_equal, ordering);
fun_sample = prosacSample(ordering);
if early
	fun_termination = early_termination_prosac(S.is_inlier, 0.8, size(xs1,2), fun_evaluate);
else
	fun_termination = prosac_termination(min_sample_num, max_rounds, confidence);
end

% initialize PROSAC global variable
PR = {};

[round success best_inliers ~] = ransac(datum_num, fun_compute, fun_evaluate, fun_candidates, fun_sample, fun_termination, -1, ...
    min_sample_num, max_rounds, confidence, gui, verbose);

assertEqual(1, round);
assertTrue(success);
assertEqual((1:7)', best_inliers);

%#ok<*STOUT> 
%#ok<*DEFNU>
