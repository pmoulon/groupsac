% the function returns all the combinations such that 
% each group's count is not zero and the sum of the counts is sample_num
% e.g. one combination for grp_num = 4, sample_num = 6 is [1 1 1 3]
function [combs] = comb_group_counts(grp_num, sample_num)

assert(grp_num <= sample_num);

if grp_num == 1
    combs = sample_num; 
else
    combs = extend_combs([1 : sample_num - grp_num + 1]');
end


%% assign samples to the next group given old combinations for the finished groups
    function [ret] = extend_combs(combs0)
        new_grp_num = grp_num - size(combs0,2);
        if new_grp_num == 0           % all groups have been assigned, we are done
            ret = combs0;
        elseif new_grp_num == 1       % the last group always takes all the remained samples
            ret = [combs0 zeros(size(combs0,1),1)];
            for ci = 1 : size(combs0,1)
                ret(ci, end) = sample_num - sum(combs0(ci,:));
            end
        else                          % the new group can take one ore more samples
            combs1 = [];
            for ci = 1 : size(combs0,1)
                sum0 = sum(combs0(ci,:)); % the sum of all selected samples
                new_sample = 1 : sample_num - sum0 - new_grp_num + 1;
                combs1 = [combs1; repmat(combs0(ci,:), length(new_sample), 1) new_sample'];
            end
            ret = extend_combs(combs1);
        end
    end
end
