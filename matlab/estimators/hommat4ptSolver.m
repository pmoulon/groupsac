% return a function handle for computing the error between points given a 
% homography matrix
function [fun_handle] = hommat4ptSolver(xs1, xs2)

assert(size(xs1,2) == size(xs2,2));
assert(size(xs1,1) == 2);
assert(size(xs2,1) == 2);

fun_handle = @compute;

    function [H] = compute(sampled)
     H = vgg_H_from_x_lin(xs1(:, sampled), xs2(:, sampled));
    end
end