% compute the threshold used in RANSAC
function [threshold] = ransac_threshold(codimension, sigma)

sigma2 = sigma * sigma;
switch codimension
    case 1
        threshold = 3.84 * sigma2;
    case 2
        threshold = 5.99 * sigma2;
    case 3
        threshold = 7.81 * sigma2;
    case 4
        threshold = 9.49 * sigma2;
    otherwise
        assert(codimension <= 4);
end

end