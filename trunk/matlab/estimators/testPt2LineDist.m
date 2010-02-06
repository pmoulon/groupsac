function test_suite = testPt2LineDist
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple1
ab = [1 0];
pt = [1 0];
actual = pt2LineDist(ab, pt);
expected = 1 / sqrt(2);
assertElementsAlmostEqual(expected, actual);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple2
ab = [0 2];
pt = [1.5 1];
actual = pt2LineDist(ab, pt);
expected = 1;
assertElementsAlmostEqual(expected, actual);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple3
ab = [0 2];
pt = [1.5 3];
actual = pt2LineDist(ab, pt);
expected = 1;
assertElementsAlmostEqual(expected, actual);

%#ok<*STOUT> 
%#ok<*DEFNU>
