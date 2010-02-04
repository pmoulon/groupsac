function [a b] = LineToPointFitting(points)

% Fit a 2D line with to a set of points
% Specifically, find a and b in the model y = ax + b
%
% Direct application of the example in:
% http://en.wikipedia.org/wiki/Linear_least_squares#Motivational_example

% Build matrices to solve Ax = b problem:
y = points(2,:)';
x = [ones(size(points,2),1) points(1,:)'];

%Compute least square solution
ab=x\y;
b=ab(1,1);
a=ab(2,1);