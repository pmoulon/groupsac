%% pick up {sample_num} samples from {candidates}
function [sampled] = draw_samples(candidates, sample_num)

idx_rand = randperm(length(candidates))';
idx_selected = idx_rand(1:sample_num);
sampled = candidates(idx_selected);

end
