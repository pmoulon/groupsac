%% unit tests for testCandidatesProsac
function test_suite = testProsacSample
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testNotExceeded

global PR;
PR = {};
PR.exceeded = false;
PR.n = 30;

ordering = 1:100;
func = prosacSample(ordering);

candidates = (1:30)';
min_sample_num = 7;
sampled = func(candidates, min_sample_num);
assertEqual(1, sum(sampled==PR.n)); % the last point is sampled
assertEqual(0, sum(sampled>PR.n));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testExceeded

global PR;
PR = {};
PR.exceeded = true;
PR.n = 30;

ordering = 1:100;
func = prosacSample(ordering);
candidates = (1:30)';
min_sample_num = 7;

% the last point is not necessary sampled
sampledLastPoint = true;
for i = 0:100 % sample 100 times
    sampled = func(candidates, min_sample_num);
    sampledLastPoint = sampledLastPoint & sum(sampled==PR.n) > 0;
end
assertEqual(false, sampledLastPoint);

%#ok<*STOUT> 
%#ok<*DEFNU>
