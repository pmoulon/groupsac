%% unit tests for testCandidatesProsac
function test_suite = testCandidatesProsac
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple

global PR;
PR = {};

min_sample_num = 7;
rounds_to_equal = 200000;
ordering = 1:200; % 200 data points
func = candidatesProsac(min_sample_num, rounds_to_equal, ordering);

candidates = func(1);
expected = 1:7;
assertEqual(expected, candidates);


%#ok<*STOUT> 
%#ok<*DEFNU>
