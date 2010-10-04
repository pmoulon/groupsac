%% prosac for fundamental matrix matching
function [] = testProsacFundmat()

clear PR;
global PR;


%% set up putatives
xs1 = [723 887; 1091 699; 1691 811; 447 635; 971 91; 1903 447; 1483 1555]';
xs2 = [1251 1243; 1603 923; 2067 1031; 787 484; 1355 363; 2163  743; 1875 1715]';
scores = [1 1 1 1 1 1 1];
is_inlier = 1 : 7;

%% control parameters
early = 0;
test_num = 10;                             % how many tests to repeat
gui = false;
sigma = 1.0;
min_sample_num = 7;
max_rounds = 5000;
confidence = 0.99;
rounds_to_equal = 200000;
fun_compute = fundmat7ptSolver(xs1,xs2);
fun_evaluate = fundmat7ptEvaluator(xs1,xs2,sigma);
fun_candidates = candidates_prosac(min_sample_num, rounds_to_equal, ordering);
fun_sample = prosac_sample(ordering);
if early
	fun_termination = early_termination_prosac(S.is_inlier, 0.8, size(xs1,2), fun_evaluate);
else
	fun_termination = prosac_termination(min_sample_num, max_rounds, confidence);
end

%% display simulation data statistics
datum_num = size(xs1,2);
combo_total = nchoosek(datum_num, min_sample_num);
disp('********************************************');
disp(sprintf('%d putatives', datum_num));
disp(sprintf('inlier num:%d',sum(is_inlier)));
disp(sprintf('total combinations:%d', combo_total));

%% run group ransac
rounds = zeros(test_num,1);
timings = zeros(test_num,1);
inliers = zeros(test_num,1);
verifications = zeros(test_num, 1);

failures = 0;
ti = 1;
while ti <= test_num
    % initialize PROSAC global variable
	PR = {};
	
	disp(sprintf('test %d:', ti));
	tic;
	[round success best_inliers best_model veri_num] = ransac(datum_num, fun_compute, fun_evaluate, fun_candidates, fun_sample, fun_termination, -1, ...
                                                     min_sample_num, max_rounds, confidence, gui);
    timings(ti) = toc;
    rounds(ti) = round;
    inliers(ti) = length(best_inliers);
    verifications(ti) = veri_num / round;
	
	if early && check_ground_truth(S.is_inlier, best_inliers, 0.9)
		disp('bad early termination!');
		ti = ti - 1;
	end
	
	if ~early && exist('S','var') && isfield(S, 'is_inlier')
		failures = failures + check_ground_truth(S.is_inlier, best_inliers, 0.9);
	end
	
	ti = ti + 1;

end;
fprintf(1, '%d tests: ave %g secs, ave %g rounds, min %d, max %d, failures %d\n', test_num, mean(timings), mean(rounds), min(rounds), max(rounds), failures);
fprintf(1, 'ave. inlier:%g, no. of verificaition:%g\n', mean(inliers), mean(verifications));

logfile = sprintf('logs/%s-prosac-fundmat.mat',datestr(now,'yy-mm-dd-HH-MM'));
save(logfile);

%% draw the matching result
if test_num == 1 && exist('S','var')
	best_model
	is_inlier = zeros(size(xs1,2), 1);
	is_inlier(best_inliers) = 1;
	output_matching_result(S.img1_name, S.img2_name, xs1(:,is_inlier==1), xs2(:,is_inlier==1));
end

end