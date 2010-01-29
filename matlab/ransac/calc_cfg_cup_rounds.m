% compute the rounds for the given configuration
function [rounds] = calc_cfg_cup_rounds(vis_map, min_sample_num, rounds_to_equal, cfg, exhaust)

persistent total;

pt_num = sum(find(sum(vis_map(:,cfg),2)));
rounds = nchoosek(pt_num, min_sample_num);

if ~exhaust

	if isempty(total)
		total = nchoosek(size(vis_map,1), min_sample_num);
	end
	
	rounds = ceil(rounds / total * rounds_to_equal);
end

end