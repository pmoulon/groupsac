function [ab] = lineFitting(points)

% Fit a 2D line with to a set of points.
% {points} are represented as two column vectors corresponding to X/Y
% Specifically, find a and b in the model y = ax + b
%
% Direct application of the example in:
% http://en.wikipedia.org/wiki/Linear_least_squares#Motivational_example

% Build matrices to solve Ax = b problem:
y = points(:,2);
x = [ones(size(points,1),1) points(:,1)];

%Compute least square solution
ba=x\y;
ab = ba(end:-1:1);