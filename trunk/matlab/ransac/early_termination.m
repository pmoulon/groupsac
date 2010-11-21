%% the early termination only checks whether the sampling contains only the inliers (given the ground truth inliers beforehand)
%% it is only used to evaluate how fast RANSAC finds the real inliers, not for the real experiment
function [fun_handle] = early_termination(is_inlier, prop)

fun_handle = @check_termination;

disp('****************** early termination mode!******************');

	function [terminate best_inliers] = check_termination(best_inliers, inliers, model, round)
		terminate = ~check_ground_truth(is_inlier, inliers, prop);

		if terminate || length(inliers) > length(best_inliers)
			best_inliers = inliers;
		end
	end
end
