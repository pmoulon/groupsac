function test_suite = testFundmat7ptSolver
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testNoNoise
xs1 = [723 887; 1091 699; 1691 811; 447 635; 971 91; 1903 447; 1483 1555]';
xs2 = [1251 1243; 1603 923; 2067 1031; 787 484; 1355 363; 2163  743; 1875 1715]';
func = fundmat7ptSolver(xs1, xs2);
F = func(1:7);
for i=1:7
    residual = [xs2(:,i); 1]' * F * [xs1(:,i); 1];
    assertTrue(abs(residual) < 1e-8);
end

    
%#ok<*STOUT> 
%#ok<*DEFNU>
