%% the default termination check for RANSAC, which only depends on the rounds needed
function [fun_handle] = prosac_termination(min_sample_num, max_rounds, confidence)

global PR;

l1mp = log(1.0 - confidence);

persistent min_inlier rounds_needed;

fun_handle = @check_termination;

    function [terminate best_inliers] = check_termination(best_inliers, inliers, model, round)
        % first update the minimal inlier we need for non-randomness if we start a new group configration
        if PR.n_rounds == 1
            min_inlier = non_randomness(min_sample_num, PR.n);
            rounds_needed = ransacRoundsNeeded(inf, min_sample_num, l1mp, PR.n, length(best_inliers));
			fprintf(1, 'n: %d round: %d, %d inliers, non_randomness:%d, rounds needed:%d, allowed:%d\n', ...
                    PR.n, PR.n_rounds, length(best_inliers), min_inlier, rounds_needed, PR.max_round);
        end
        
        
        if length(inliers) > length(best_inliers)
            best_inliers = inliers;
            rounds_needed = ransacRoundsNeeded(inf, min_sample_num, l1mp, PR.n, length(inliers));
            fprintf(1, 'n: %d round: %d, %d inliers, non_randomness:%d, rounds needed:%d, allowed:%d\n', ...
                    PR.n, PR.n_rounds, length(best_inliers), min_inlier, rounds_needed, PR.max_round);
        end

%         if length(best_inliers) < 250 
%             rounds_needed = inf;
%         end
%         
        terminate = (length(inliers) > min_inlier && round >= rounds_needed) || round > max_rounds;
        
        if terminate
            fprintf(1, 'ready to terminate when non_randomness:%d inliers, rounds needed:%d\n', min_inlier, rounds_needed);
        end
        
    end
end
