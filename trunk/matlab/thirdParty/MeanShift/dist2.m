% dist2 - pointer ro function that measures distance square
%         the distance function should be able to take two d by N matrices
%         and return a vector of length N, where Ni is the distance^2
%         between the two i-th vectors.

function [dist] = dist2(x1, x2)

dist = zeros(1,size(x1,2));

dist0 = x1 - x2;

for i=1:length(dist)
    dist(i) = norm(dist0(:,i));
end

end
