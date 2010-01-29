%% return the handle of a function that gives candidates for RANSAC's sampling
%% always return the maximum size group that has not been sampled yet
function [fun_handle] = candidates_multiple_groups(min_sample_num, rounds_to_equal, vis_map, cfgs)
% cfgs : each row is a group configruation

global GR;

fun_handle = @select_candidates;

    function [candidates] = select_candidates(round)

		new_cfg = 0;
		% build the round budget for the 1st configuration
		if ~GR.initialized		
			GR.cur_grps = size(cfgs,2);
			GR.cur_cfg = 1;
			GR.grp_cfgs{GR.cur_grps} = cfgs;
			GR.cfg_rounds = 1;
			GR.rounds{GR.cur_grps}(GR.cur_cfg) = calc_cfg_cup_rounds(vis_map, min_sample_num, rounds_to_equal, GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg, :), 0);
			GR.initialized = 1;
			new_cfg = 1;
		else
			% decide whether to move to the next round
			if round > GR.rounds{GR.cur_grps}(GR.cur_cfg)
				GR.cur_cfg = GR.cur_cfg + 1;
				GR.cfg_rounds = 1;
				
				% compute the rounds for the current cfg during the 1st round
				GR.rounds{GR.cur_grps}(GR.cur_cfg) = calc_cfg_cup_rounds(vis_map, min_sample_num, rounds_to_equal, GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg, :), 0);
				if GR.cur_cfg > 1
					GR.rounds{GR.cur_grps}(GR.cur_cfg) = GR.rounds{GR.cur_grps}(GR.cur_cfg) + GR.rounds{GR.cur_grps}(GR.cur_cfg-1);
				end
				new_cfg = 1;
			else
				GR.cfg_rounds = GR.cfg_rounds + 1;
				new_cfg = 0;
			end
		end
		
		if new_cfg
			grps = GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg, :);    % use the current configuration to select candidates
			vis = sum(vis_map(:,grps),2);                      % visibility in the current groups
			GR.cur_candidates = find(vis);                     % the point indices that are in the desired groups
		end
		
        candidates = GR.cur_candidates;

        assert(length(candidates) >= min_sample_num);
		
    end
end
