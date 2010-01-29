%%  check whether the inliers are compatible with ground truth
function [fail] = check_ground_truth(is_inlier, inliers, prop)

	if ~exist('prop', 'var')
		prop = 0.8;
	end
	
	%fail = sum(is_inlier(inliers)) < sum(is_inlier) * prop;
	fail = length(inliers) < sum(is_inlier) * prop;
	
end