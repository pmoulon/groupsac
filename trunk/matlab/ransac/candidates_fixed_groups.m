%% return the points from certain groups, for debugging purpose
function [fun_handle] = candidates_fixed_groups(vis_map, groups)

disp('*********************running in fixed groups mode!***************');

pt_idx = find(sum(vis_map(:,groups), 2)); 

fun_handle = @select_candidates;

    function [candidates] = select_candidates(round)
		candidates = pt_idx;
    end
end
