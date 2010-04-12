function test_suite = testFundmat7ptError
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testError
F = [0 0 0; 0 0 -1; 0 1 0];
x0 = [0; 0; 1];  y0 = [0;   0;   1];
x1 = [0; 0; 1];  y1 = [100; 0;   1];
x2 = [0; 0; 1];  y2 = [0;   0.1; 1];
x3 = [0; 0; 1];  y3 = [0;   1;   1];
x4 = [0; 0; 1];  y4 = [0;   10;  1];
x5 = [0; 0; 1];  y5 = [100; 10;  1];
    
assert(fundmat7ptError(F, x0, y0) == 0);
assert(fundmat7ptError(F, x1, y1) == 0);
assert(fundmat7ptError(F, x2, y2) == 2 * (0.1/2)^2);
assert(fundmat7ptError(F, x3, y3) == 2 * (1/2)^2);
assert(fundmat7ptError(F, x4, y4) == 2 * (10/2)^2);
assert(fundmat7ptError(F, x5, y5) == 2 * (10/2)^2);

%#ok<*STOUT> 
%#ok<*DEFNU>
