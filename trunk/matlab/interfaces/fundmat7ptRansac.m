% use RANSAC to determine the inliers in the points by fitting a fundamental matrix model
function [success, inliers, model] = fundmat7ptRansac(xs1, xs2, sigma)

assert(size(xs1,2) == size(xs2,2));
assert(size(xs1,1) == 2);
assert(size(xs2,1) == 2);

%% control parameters
datum_num = size(xs1, 2);
fun_compute = fundmat7ptSolver(xs1, xs2);
fun_evaluate = fundmat7ptEvaluator(xs1, xs2, sigma);
fun_candidates = -1;
fun_sample = -1;
fun_termination = -1;
fun_draw = -1;
min_sample_num = 7;
max_rounds = 1000;
confidence = 0.95;
gui = false; 
verbose = false;

%% call ransac function
[~, success, inliers, model, ~] = ...
    ransac(datum_num, fun_compute, fun_evaluate, fun_candidates, fun_sample, fun_termination, fun_draw, ...
        min_sample_num, max_rounds, confidence, gui, verbose);

end