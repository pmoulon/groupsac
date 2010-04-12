function test_suite = testLineFittingSolver
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testNoNoise
y = 5:3:50;
x = 1:length(y);
points = [x' y'];
[ab] = lineFittingSolver(points);
assertElementsAlmostEqual(3, ab(1));
assertElementsAlmostEqual(2, ab(2));

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testWithNoise
y = [5:3:50];
x = 1:length(y);

   
%#ok<*STOUT> 
%#ok<*DEFNU>
