function [A] = LineToPointFitting(points)

% Fit a 2D line with to a set of points
% Specifically, find a and b in the model y = ax + b
%
% Direct application of the example in:
% http://en.wikipedia.org/wiki/Linear_least_squares#Motivational_example

% Build matrices to solve Ax = b problem:
b = zeros(size(points,2));
C = zeros(size(points,2), 2);

for i=1:size(points,2)
  b(i)= points(2,i);

  C(i,1) = 1;
  C(i,2) = points(1,i);
end

%Compute least square solution
A=C\b;
A=A(:,1);

