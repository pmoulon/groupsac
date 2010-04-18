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
    
assertEqual(fundmat7ptError(F, x0, y0), 0);
assertEqual(fundmat7ptError(F, x1, y1), 0);
assertEqual(fundmat7ptError(F, x2, y2), 2 * (0.1/2)^2);
assertEqual(fundmat7ptError(F, x3, y3), 2 * (1/2)^2);
assertEqual(fundmat7ptError(F, x4, y4), 2 * (10/2)^2);
assertEqual(fundmat7ptError(F, x5, y5), 2 * (10/2)^2);

function testVgg

i1 = 1;
i2 = 2;

[view, Xi, ~] = vgg_example_scene(4);
F = vgg_F_from_P(view(i1).P, view(i2).P);

for i = 1:size(Xi, 2)
    n1 = Xi(i1,i);
    n2 = Xi(i2,i);
    if n1~=0 && n2~=0
        assertTrue(fundmat7ptError(F, [view(i1).x(:,n1); 1], [view(i2).x(:,n2); 1]) < 3);
    end
end


%#ok<*STOUT> 
%#ok<*DEFNU>
