% return an evaluate function handle to use in fundamental matrix fitting RANSAC
function [fun_handle] = fundmat7ptEvaluator(xs1, xs2, sigma)

%% compute error threshold
codimension = 1;
err_tol = ransacThreshold(codimension, sigma);

%% convert to homogeneous coordinates
xs1 = [xs1; ones(1, size(xs1, 2))];
xs2 = [xs2; ones(1, size(xs2, 2))];

fun_handle = @evaluate;

%% find the inliers in {candidates} for the given line {ab}
    function [best_inliers best_model] = evaluate(Fs, candidates)
        best_inliers = [];
        best_model = Fs(:,:,1);
        for i = 1:size(Fs,3)
            
            % check all the putatives
            is_inliers = zeros(length(candidates), 1);
            for pi = 1:length(candidates)
                if fundmat7ptError(Fs(:,:,i), xs1(:, candidates(pi)), xs2(:, candidates(pi))) <= err_tol
                    is_inliers(candidates(pi)) = 1;
                end
            end
            
            % check whether the current inliers beat previous trails
            inliers = find(is_inliers);
            if length(inliers) > length(best_inliers)
                best_inliers = inliers;
                best_model = Fs(:,:,i);
            end
            
        end
    end
end