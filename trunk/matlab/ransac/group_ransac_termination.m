%% the default termination check for RANSAC, which only depends on the rounds needed
function [fun_handle] = group_ransac_termination(min_sample_num, max_rounds, confidence)

global vis_map GR;

persistent min_inlier rounds_needed rounds_allowed;

l1mp = log(1.0 - confidence);

fun_handle = @check_termination;

    function [terminate best_inliers] = check_termination(best_inliers, inliers, model, round)
        % first update the minimal inlier we need for non-randomness if we start a new group configration
        if GR.cfg_rounds == 1
            cfg = GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg,:);
            cfg_size = sum(sum(vis_map(:,GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg,:)), 2) > 0);
            min_inlier = non_randomness(min_sample_num, cfg_size);
            best_inliers = []; % each group configuration's best inliers are not comparable due to different group sizes
            rounds_needed = max_rounds;
			
			% compute how many rounds for the new group cfg
			if GR.cur_cfg == 1
				if GR.cur_grps == 1 || isempty(GR.rounds{GR.cur_grps-1})
					rounds_allowed = GR.rounds{GR.cur_grps}(1);
				else
					rounds_allowed = GR.rounds{GR.cur_grps}(1) - GR.rounds{GR.cur_grps-1}(end);
				end
			else
				rounds_allowed = GR.rounds{GR.cur_grps}(GR.cur_cfg) - GR.rounds{GR.cur_grps}(GR.cur_cfg-1);
			end
        end
        
        
        if length(inliers) > length(best_inliers)
            best_inliers = inliers;
            cfg = GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg,:);
            cfg_size = sum(sum(vis_map(:,cfg), 2) > 0);
            rounds_needed = ransac_rounds_needed(inf, min_sample_num, l1mp, cfg_size, length(inliers));
            %GR.grp_cfgs{GR.cur_grps}(GR.cur_cfg,:)
			fprintf('cfg %s, round %d, %d inliers out of %d, non_randomness %d, rounds needed %d, allowed:%d\n', ...
                          mat2str(cfg), GR.cfg_rounds, length(inliers), cfg_size, min_inlier, rounds_needed, rounds_allowed);
        end

        terminate = (length(inliers) > min_inlier && GR.cfg_rounds >= rounds_needed) || round > max_rounds;
        
        if terminate
            disp(sprintf('ready to terminate when non_randomness:%d inliers, rounds needed:%d', min_inlier, rounds_needed));
        end
        
    end
end
