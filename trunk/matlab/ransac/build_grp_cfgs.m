%% build a list of group configs and their corresponding rounds
function [] = build_grp_cfgs(min_sample_num, rounds_to_equal, grps_used)

global GR vis_map;

% if exhause, we are going to compute the exact combination number
exhaust = isa(rounds_to_equal, 'char');

% generate unsorted group configurations
grp_cfgs = nchoosek(1:size(vis_map,2), grps_used);


% sort the group configurations w.r.t the number of points
cfg_sizes = zeros(size(grp_cfgs,1),1);
rounds = zeros(size(grp_cfgs,1),1);
for ci = 1 : size(grp_cfgs,1)

    cfg_sizes(ci) = sum (sum(vis_map(:,grp_cfgs(ci,:)), 2) > 0);
    %cfg_sizes(ci) = prod(sum(vis_map(:,grp_cfgs(ci,:)), 1));
    
	rounds(ci) = calc_cfg_cap_rounds(vis_map, min_sample_num, rounds_to_equal, grp_cfgs(ci,:), exhaust);
end

% filter the cfgs that do not have enough samples
remained = find(cfg_sizes >= min_sample_num);
grp_cfgs = grp_cfgs(remained, :);
cfg_sizes = cfg_sizes(remained);
rounds = rounds(remained);

[cfg_sizes_sorted, gi_sorted] = sort(cfg_sizes,'descend');

% compute the minimal inlier number for each group configuration
min_inliers = zeros(length(cfg_sizes_sorted), 1);
for ci = 1 : length(cfg_sizes_sorted)
    min_inliers = non_randomness(min_sample_num, cfg_sizes_sorted(ci));
end

% find the base rounds from the last group configuration
if GR.initialized
    base_rounds = GR.rounds{grps_used - 1}(end);
else
    base_rounds = 0;
end

% fill the global information
GR.grp_cfgs{grps_used} = grp_cfgs(gi_sorted, :);                  % new group configurations
GR.rounds  {grps_used} = base_rounds + cumsum(rounds(gi_sorted)); % new rounds
GR.min_inliers{grps_used} = min_inliers;                          % the minimal number of inliers to prove non-randomness
GR.cur_grps = grps_used;                                          % move to the next level
GR.cur_cfg  = 1;                                                  % start from the 1st cfg
disp(sprintf('built cfgs with %d groups, %d rounds needed', grps_used, GR.rounds{grps_used}(end)));


end