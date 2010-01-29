%% draw a group ransac 
function [] = group_ransac()

global vis_map % global gui variables



%% calculate different group combinations and show the pie charts
% combo_sums = zeros(sample_num,1);
% for group_used = 1 : 4
%     grps = nchoosek(1:group_num, group_used);                              % the group combinations for the current {group_used}
%     for gi = 1:size(grps,1)
%         datum_ok = sum(vis_map(:,grps(gi)),2) > 0;
%         combos = nchoosek(length(datum_ok), sample_num);
%         combo_sums(group_used) = combo_sums(group_used) + combos;
%     end
% end
% 
% combo_sums = combo_sums(combo_sums ~= 0);
% others = combo_total - sum(combo_sums(:));
% combo_sums = [combo_sums; others];
% pie(combo_sums); color jet;
% legend('1 group','2 groups','3 groups','4 groups', 'others');


%% increase the involved group number gradually
global_rounds = zeros(test_num,1);
for test = 1 : test_num
    found = false;
    global_round = 0;
    for group_used = 1 : sample_num
        grps = nchoosek(1:group_num, group_used);

        % compute and sort w.r.t the group sizes
        sizes = zeros(size(grps,1),1);
        for gi = 1 : size(grps,1)
            sizes(gi) = sum(group_sizes(grps(gi,:)));
        end
        [sorted, gi_sorted] = sort(sizes,'descend');
        grps_sorted = grps(gi_sorted, :);

        % try the sorted group combination
        for gi = 1 : size(grps_sorted, 1)

            % only keep the data from the desired groups
            datum_ok = find(sum(vis_map(:,grps_sorted(gi,:)),2)); % the point indices that are in the desired groups
            if length(datum_ok) < sample_num
                continue;
            end;

            % how many rounds to spend for the desired group configuration
            max_round_here = ceil(nchoosek(length(datum_ok), sample_num) / combo_total * rounds_to_equal);

            [round found] = ransac(length(datum_ok), @evaluate_samples, sample_num, max_round_here, gui);
            global_round = global_round + round;

            if found break; end
        end

        if found break; end
    end
    
    global_rounds(test) = global_round;
end

if test_num > 1 figure; hist(global_rounds); end
disp(sprintf('the average round=%g', mean(global_rounds)));

%% evaluate a minimum sample
    function [inliers] = evaluate_samples(sampled)
        if sum(is_inlier(datum_ok(sampled))) == sample_num
            inliers = 1:length(datum_ok);
        else
            inliers = [];
        end
    end

%% how many combinations if each of the given groups has at least one sample
    function [combo_num] = combo_num_for_groups(sizes_in)
        combo_num = nchoosek(sum(sizes_in(:)), sample_num);
    end

end