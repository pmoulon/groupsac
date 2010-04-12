%% sampson error for fundamental matrix
function [error] = fundmat7ptError(F, x1, x2)
xfx = x2' * F * x1;
error = xfx ^ 2 / (jjt(F,x1) + jjt(F',x2));
    function [ret] = jjt(f,v)
        fv = f * v;
        ret = fv(1) ^ 2 + fv(2) ^ 2;
    end
end