%% sampson error for homography matrix
function [error] = hommat4ptError(H, x1, x2)
Hx = H * x1;
Hx = Hx/Hx(3,:);
error = sqrt(sum((x2-Hx).*(x2-Hx)));
end