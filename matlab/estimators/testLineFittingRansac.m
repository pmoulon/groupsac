function test_suite = testRansacLineFitting
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple
a = -5;
b = 2;
inlier_num = 20;
outlier_num = 10;
sigma = 0.1;

% generate points
pts = zeros(inlier_num + outlier_num, 2);
pts(:, 1) = (rand(inlier_num + outlier_num, 1) - 0.5) * 100;
pts(:, 2) = a * pts(:,1) + b;

% add noise to outlier points
noise = 1 + rand(outlier_num, 1) * 10;
noise(1:2:end) = noise(1:2:end) * -1;
pts(inlier_num+1:end, 2) = pts(inlier_num+1:end, 2) + noise ;

% run ransac
[success, inliers, model] = ransacLineFitting(pts, sigma);

assertEqual(true, success);
assertEqual((1:inlier_num)', inliers);
assertElementsAlmostEqual([a; b], model);

%#ok<*STOUT> 
%#ok<*DEFNU>
