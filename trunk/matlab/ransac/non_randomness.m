function [inlier_num] =  non_randomness(m, n)
% evaluate the probability that a model is randomly supported by points, as describe in Eqn. 7 and 8 of Chum05cvpr 

phi = 0.05;   % we want to make sure that randomness < \phi
beta = 0.05;   % the probability of an accidential support

p = 0;
inlier_num = n;
while p < phi
    p = p + randomness_i(inlier_num);
    inlier_num = inlier_num - 1;
end

if inlier_num == n % any inlier number will be too random
    inlier_num = inf;
else
    inlier_num = inlier_num + 1;          % the minimum solution for i
end;

    function [p_i] = randomness_i(inlier_num)
        p_i = beta^(inlier_num-m) * (1-beta)^(n-inlier_num+m) * nchoosek(n-m,inlier_num-m);
    end

end