function [round, success, best_inliers, best_model, veri_num] = ransac(datum_num, fun_compute, fun_evaluate, fun_candidates, fun_sample, fun_termination, fun_draw, ...
    min_sample_num, max_rounds, confidence, gui, verbose)
% ranasc: the common routine for RANSAC
%   datum_num           : the number of putatives
%   fun_compute         : compute the underlying model given a sample set
%   fun_evaluate        : the function to evaluate a given model
%   fun_candidates      : the function to select candidates from all data points
%   fun_sample          : the sampling function
%   min_sample_num      : the size of a minimum sample
%   max_rounds          : the maximum rounds for RANSAC routine
%   confidence          : the confidence want to achieve at the end
%   gui                 : whether show gui or not

%% parameters
veri_num = 0;  % the total number of verifications made
round_per_draw = 1;
l1mp = log(1.0 - confidence);

if ~isa(fun_candidates, 'function_handle')
    fun_candidates = @default_fun_candidates;
end

if ~isa(fun_termination, 'function_handle')
    fun_termination = @default_termination;
end

if ~isa(fun_sample, 'function_handle')
    fun_sample = @draw_samples;
end

%% the main ransac routine
success = false;              % whether RANSAC is successful at last
round = 0;                    % current round
best_inliers = [];            % the best inliers so far
while 1
    
    round = round + 1;
    if mod(round,100) == 0 && verbose > 0
        fprintf(1, 'global round=%d   \tbest=%d\n', round, length(best_inliers));
    end
    
    candidates = fun_candidates(round);                 % get the candidates for sampling
    sampled = fun_sample(candidates, min_sample_num);   % get sample indices from candidates
    
    % For GroupSAC, return inlier in the current group configuration
    model = fun_compute(sampled);                     % compute the new model
    if isempty(model) == 0 % Handle posible degenerate model
        [inliers ~] = fun_evaluate(model, candidates);        % compute the inliers for the new model.
    else
        inliers = [];
    end
    veri_num = veri_num + length(candidates);
    
    if gui && mod(round,round_per_draw) == 0
        fun_draw(sampled);
    end
    
    if isempty(inliers)
        terminate = false;
    else
        [terminate best_inliers] = fun_termination(best_inliers, inliers, model, round, verbose);  % check the termination condition
    end
    if terminate
        if gui fun_draw(sampled);  end                  % always draw the best sample at the end
        success = true;
        
        %% finalize the model and inliers
        model = fun_compute(best_inliers);
        [best_inliers best_model] = fun_evaluate(model, 1:datum_num);
        veri_num = veri_num + length(candidates);
        if verbose > 0
            fprintf(1, 'quiting ransac...found %d inliers after %d rounds\n', length(best_inliers), round);
        end
        break;
    end
end

%% the default termination check for RANSAC, which only depends on the rounds needed
    function [terminate best_inliers] = default_termination(best_inliers, inliers, model, round, verbose)
        persistent rounds_needed;
        if length(inliers) > length(best_inliers)
            best_inliers = inliers;
            rounds_needed = ransacRoundsNeeded(max_rounds, min_sample_num, l1mp, datum_num, length(inliers));
            if verbose > 0
                fprintf(1,'global round=%d   \tbest=%d \trounds_needed=%d\n', round, length(best_inliers), rounds_needed);
            end
        end
        terminate = round >= rounds_needed;
    end

%% default fun_candidates returns all the point indices as candidates
    function [candidates] = default_fun_candidates(~)
        candidates = 1 : datum_num;
    end
end