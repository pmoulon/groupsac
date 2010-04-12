function test_suite = testLineFittingError
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple1
ab = [1 0];
pt = [1 0];
actual = lineFittingError(ab, pt);
expected = 1 / sqrt(2);
assertElementsAlmostEqual(expected, actual);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple2
ab = [0 2];
pt = [1.5 1];
actual = lineFittingError(ab, pt);
expected = 1;
assertElementsAlmostEqual(expected, actual);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple3
ab = [0 2];
pt = [1.5 3];
actual = lineFittingError(ab, pt);
expected = 1;
assertElementsAlmostEqual(expected, actual);

%#ok<*STOUT> 
%#ok<*DEFNU>
