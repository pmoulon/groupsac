%% return the points from certain groups, for debugging purpose
function [fun_handle] = candidates_prosac(min_sample_num, rounds_to_equal, ordering)

global PR;

T_N = rounds_to_equal;
T_n_ratio = T_N / nchoosek(length(ordering),min_sample_num);

fun_handle = @select_candidates;

%% the function to return
    function [candidates] = select_candidates(round)

		% initialization
		if isempty(PR)
			PR.exceeded = 0;         
			PR.n = min_sample_num-1; % the index of the last element in the current subset
			PR.n_rounds = 0;         % the rounds used in the current subset
			PR.max_round = inf;
		    PR.T_n = 0;
		end
		
		% if the budget in the current subset is used up
		if PR.n_rounds >= PR.max_round
			PR.n_rounds = 0;
		end
		
		% start of a new subset
		if PR.n_rounds == 0
			if PR.n ~= length(ordering)
				PR.n = PR.n + 1;
				PR.T_n_1 = PR.T_n;
				PR.T_n = T_n_ratio * nchoosek(PR.n, min_sample_num);
				PR.max_round = ceil(PR.T_n - PR.T_n_1);
			else
				PR.max_round = inf; % always use the entire data set
				PR.exceeded = 1;    % when exceeeded, does not have sample from the last element
			end
		end
		
		PR.n_rounds = PR.n_rounds + 1;
		
		candidates = ordering(1:PR.n);
		
	end

end
