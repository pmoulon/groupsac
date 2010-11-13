% return a function handle for computing the fundamental matrix from a set of points
function [fun_handle] = fundmat7ptSolver(xs1, xs2)

assert(size(xs1,2) == size(xs2,2));
assert(size(xs1,1) == 2);
assert(size(xs2,1) == 2);

xs1 = [xs1; ones(1, size(xs1, 2))];
xs2 = [xs2; ones(1, size(xs2, 2))];
        
fun_handle = @compute;

    function [F] = compute(sampled)
        if length(sampled) == 7
            F = vgg_F_from_7pts_2img(xs2(:, sampled), xs1(:, sampled)); % F(:,:,n) is the n-th solution
        else
            F = fundmatrix(xs1(:, sampled), xs2(:, sampled)); % call Peter's function
        end
    end
end