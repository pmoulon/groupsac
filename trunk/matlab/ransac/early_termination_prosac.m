%% the early termination only checks whether the sampling contains only the inliers (given the ground truth inliers beforehand)
%% it is only used to evaluate how fast RANSAC finds the real inliers, not for the real experiment
function [fun_handle] = early_termination_prosac(is_inlier, prop, datum, fun_evaluate)

inlier_num = sum(is_inlier);

fun_handle = @check_termination;

disp('****************** early termination mode!******************');

	function [terminate best_inliers] = check_termination(best_inliers, inliers, model, ~)
		
		all_inliers = inliers;
		
		if length(inliers) >= length(best_inliers) * 0.9 || length(inliers) >= inlier_num * prop
			all_inliers = fun_evaluate(model, 1:datum);
			disp(sprintf('all_inliers:%d',length(all_inliers)));
		end
		
		
		terminate = ~check_ground_truth(is_inlier, all_inliers, prop);

		if length(inliers) > length(best_inliers)
			best_inliers = inliers;
		end
		
		if terminate
			best_inliers = all_inliers;
		end
	end
end
