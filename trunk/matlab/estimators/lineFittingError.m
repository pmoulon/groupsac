%% the distance between the given point and the line y=ax+b, i.e. ax-y+b=0
% http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
function [dist] = lineFittingError(ab, pt)
dist = abs(ab(1)*pt(1) - pt(2) + ab(2)) / sqrt(ab(1) * ab(1) + 1);
end