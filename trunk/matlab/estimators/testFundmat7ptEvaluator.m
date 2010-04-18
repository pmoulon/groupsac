function test_suite = testFundmat7ptEvaluator
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testVgg

% load data
i1 = 1; i2 = 1;
[view, Xi, ~] = vgg_example_scene(4);
F = vgg_F_from_P(view(i1).P, view(i2).P);

xs1 = [];
xs2 = [];
for i = 1:size(Xi, 2)
    n1 = Xi(i1,i);
    n2 = Xi(i2,i);
    if n1~=0 && n2~=0
        xs1 = [xs1 view(i1).x(:,n1)];
        xs2 = [xs2 view(i2).x(:,n2)];
    end
end

% sovle F
solver = fundmat7ptSolver(xs1, xs2);
F = solver(1:7);
for i=1:7
    residual = [xs1(:,i); 1]' * F * [xs2(:,i); 1];
    assert(residual < 1e-8);
end

% add an outlier
xs1 = [xs1 [1; 200]]; % add one outlier
xs2 = [xs2 [100; 2]]; % add one outlier
evaluator = fundmat7ptEvaluator(xs1, xs2, 1);
[inliers model] = evaluator(F, 1:size(xs1,2));

assertEqual(inliers, (1:(size(xs1,2)-1))');
   
%#ok<*STOUT> 
%#ok<*DEFNU>
