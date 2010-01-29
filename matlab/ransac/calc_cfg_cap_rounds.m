% compute the rounds for the given configuration
function [rounds] = calc_cfg_cap_rounds(vis_map, min_sample_num, rounds_to_equal, cfg, exhaust)

persistent total;

rounds = combs_of_cap2(cfg);

if ~exhaust

	if isempty(total)
		total = nchoosek(size(vis_map,1), min_sample_num);
	end
	
	rounds = ceil(rounds / total * rounds_to_equal);
end



%% return the number of combinations for \bigcap{G_i}
    function [combs] = combs_of_cap(cfg)
        grp_sizes = sum(vis_map(:,cfg), 1);
        grp_counts = comb_group_counts(length(cfg), min_sample_num);
        combs = 0;

		for cap_i1 = 1:size(grp_counts,1)
            new_combs = 1;
            for cap_i2 = 1:size(grp_counts,2)
                if grp_counts(cap_i1, cap_i2) > grp_sizes(cap_i2)
                    new_combs = 0;
                    break;
                else
                    new_combs = new_combs * nchoosek(grp_sizes(cap_i2), grp_counts(cap_i1, cap_i2));
                end
            end;
            combs = combs + new_combs;
		end
    end

%% return the number of combinations for \bigcap{G_i}
    function [combs] = combs_of_cap2(cfg)
        grp_num = length(cfg);
        sign = -1;
        combs = 0;
        for cap_grps_used = grp_num : -1 : 1
            sign = sign * (-1);
            cap_cfgs = nchoosek(cfg, cap_grps_used);
            for cap_ci = 1 : size(cap_cfgs,1)
                combs = combs + sign * combs_of_cup(cap_cfgs(cap_ci,:));
            end
        end
    end

%% return the number of combinations for \bigcup{G_i}
    function [combs] = combs_of_cup(cfg)
        pt_num = sum(sum(vis_map(:,cfg), 2) > 0);
        if pt_num < min_sample_num   % if not enough samples
            combs = 0;
        else                         % have enough samples
            combs = nchoosek(pt_num, min_sample_num);
        end
    end


end