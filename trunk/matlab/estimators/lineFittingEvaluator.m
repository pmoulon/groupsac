function [fun_handle] = lineFittingEvaluator(points, sigma)
% return an evaluate function handle to use in line fitting RANSAC

codimension = 1;
err_tol = ransacThreshold(codimension, sigma);

fun_handle = @evaluate;

%% find the inliers in {candidates} for the given line {ab}
    function [inliers model] = evaluate(ab, candidates)
        model = ab; % for line fitting, we only have a single model. But for fundamental matrix, we might have multiple models
        is_inliers = zeros(length(candidates), 1);
        for pi = 1:length(candidates)
            if lineFittingError(ab, points(pi, :)) <= err_tol
                is_inliers(pi) = 1;
            end
        end
        inliers = find(is_inliers);
    end
end