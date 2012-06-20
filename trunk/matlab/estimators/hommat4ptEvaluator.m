% return an evaluate function handle to use in homography matrix fitting RANSAC
function [fun_handle] = homat4ptEvaluator(xs1, xs2, sigma)

%% compute error threshold
codimension = 1;
err_tol = ransacThreshold(codimension, sigma);

%% convert to homogeneous coordinates
xs1 = [xs1; ones(1, size(xs1, 2))];
xs2 = [xs2; ones(1, size(xs2, 2))];

fun_handle = @evaluate;

%% find the inliers in {candidates} for the given line {ab}
    function [best_inliers best_model] = evaluate(H, candidates)
        best_inliers = [];
        best_model = H;
        
            % check all the putatives
            is_inliers = zeros(length(candidates), 1);
            for pi = 1:length(candidates)
                if hommat4ptError(H, xs1(:, candidates(pi)), xs2(:, candidates(pi))) <= err_tol
                    is_inliers(candidates(pi)) = 1;
                end
            end
            
            % check whether the current inliers beat previous trails
            inliers = find(is_inliers);
            best_inliers = inliers;
    end
end