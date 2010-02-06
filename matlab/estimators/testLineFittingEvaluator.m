function test_suite = testLineFittingEvaluator
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple
pts = [1 2; 2 4; 2 5; 3 6; 4 7];
sigma = 0;
fun = lineFittingEvaluator(pts, sigma);

ab = [2 0];
actual = fun(ab, 1:length(pts));
expected = [1; 2; 4];
assertEqual(expected, actual);

   
%#ok<*STOUT> 
%#ok<*DEFNU>
