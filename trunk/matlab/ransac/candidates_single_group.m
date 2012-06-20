%% return the handle of a function that gives candidates for RANSAC's sampling
function [fun_handle] = candidates_single_group(min_sample_num, rounds_to_equal, verbose)

global GR vis_map;

% assert we only have single-group points
assert(sum(abs(sum(vis_map,2) - 1)) == 0);

fun_handle = @select_candidates;

    function [candidates] = select_candidates(round)
        % update the book keeping
        new_cfg = 0;
        if ~GR.initialized                                                           % initialize
            build_grp_cfgs(min_sample_num, rounds_to_equal, GR.cur_grps, verbose);
			GR.initialized = 1;
            new_cfg = 1;
        elseif round > GR.rounds{GR.cur_grps}(GR.cur_cfg)                            % the current rounds have been used up
            if GR.cur_cfg == length(GR.rounds{GR.cur_grps})
                build_grp_cfgs(min_sample_num, rounds_to_equal, GR.cur_grps  + 1);   % to the next group level
            else
                GR.cur_cfg = GR.cur_cfg + 1;                                         % to the next configuration
            end
            new_cfg = 1;
        end
        
        % if we start a new group configuration
        if new_cfg
            GR.cfg_rounds = 1;                                 % the rounds for the current group configuration
            grps = GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg, :);    % use the current configuration to select candidates
            vis = sum(vis_map(:,grps),2);                      % visibility in the current groups
            GR.cur_candidates = find(vis);                     % the point indices that are in the desired groups
        else
            GR.cfg_rounds = GR.cfg_rounds + 1;
        end

        candidates = GR.cur_candidates;

        assert(length(candidates) >= min_sample_num);

    end
end
