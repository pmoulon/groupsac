function [fun_handle] = prosac_sample(ordering)

global PR;

fun_handle = @func_to_return;

	function [sampled] = func_to_return(candidates, min_sample_num)
		
		if ~PR.exceeded 
			% draw samples from 1 to n-1
			sampled = draw_samples(candidates(1:end-1), min_sample_num-1);
			
			% the n-th point is mandatory
			assert(ordering(PR.n) == candidates(end));
			sampled = [sampled; candidates(end)];
		else
			sampled = draw_samples(candidates, min_sample_num);
		end
	end

end