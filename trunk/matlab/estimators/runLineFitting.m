% Least Squares Estimate visual test
%--------------------------------------
% Define a set of point along a line
% Add some noise on Y coords
% Fit a line on point cloud
% Visualize the result
%--------------------------------------

% the Y observations
y = [5:3:50];
% Add noise
y = y + 5*rand(size(y));
% The x coordinates 
x = 1:length(y);

points = [x;y];
%Estimate the slope and constant ax + b
[a b] = lineFitting(points);

% constructing the straight line using the estimated slope and constant
yEst = a*x + b; 

close all
figure
hold on
% Plot point cloud
plot(x,y,'r+')
% Plot estimated line
plot(x,yEst,'b')
legend('observations', 'estimated line')
ylabel('y axis'); xlabel('x axis')
title('least squares straight line fit')
