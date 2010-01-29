% return the minimal rounds needed for a given data set size and a given inlier number
function [needed] = ransac_rounds_needed(max_rounds, min_sample_num, l1mp, datum_num, inlier_num)

w = inlier_num / datum_num;  % inlier point probability
eps_log = log(1.0 - w ^ min_sample_num); % outlier sample probability
if inlier_num == 0 || eps_log == 0
    needed = max_rounds;
else
    needed = min(max_rounds, ceil(l1mp / eps_log));
end

end