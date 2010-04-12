function [ab] = lineFittingSolver(points)

% Fit a 2D line with to a set of points.
% {points} are represented as two column vectors corresponding to X/Y
% Specifically, find a and b in the model y = ax + b
%
% Direct application of the example in:
% http://en.wikipedia.org/wiki/Linear_least_squares#Motivational_example

% Build matrices to solve Ax = b problem:
y = points(:,2);
x = [points(:,1) ones(size(points,1),1)];

%Compute least square solution
ab=x\y;
