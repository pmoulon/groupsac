function test_suite = testFundmat7ptRansac
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple

% load data
i1 = 1; i2 = 2;
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
inlier_num = size(xs1,2);


xs1 = [xs1 [1; 200]]; % add one outlier
xs2 = [xs2 [100; 2]]; % add one outlier

% run ransac
sigma = 1;
[success, inliers, model] = fundmat7ptRansac(xs1, xs2, sigma);

assertEqual(true, success);
assertEqual((1:inlier_num)', inliers);

%#ok<*STOUT> 
%#ok<*DEFNU>
