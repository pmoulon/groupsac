% return a function handle for computing the fundamental matrix from a set of points
function [fun_handle] = fundmat7ptSolver(xs1, xs2)

fun_handle = @compute;

    function [F] = compute(sampled)
        assert(length(sampled) == 7);
        x1 = [xs1(1:2, sampled); ones(1, 7)];
        x2 = [xs2(1:2, sampled); ones(1, 7)];
        F = vgg_F_from_7pts_2img(x1, x2);
    end
end