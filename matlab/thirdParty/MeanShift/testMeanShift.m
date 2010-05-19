%testMeanShift
%
% Try to find nCLust onto a dataset of points.
%

clear
profile on % If you use octave comment this line

nPtsPerClust = 250;
nClust  = 3;
totalNumPts = nPtsPerClust*nClust;
m = [1 -1 1; 1 -1 -1];
var = .6;
bandwidth = .75;
clustMed = [];


x = var*randn(2,nPtsPerClust*nClust);
%*** build the point set
for i = 1:nClust
    x(:,1+(i-1)*nPtsPerClust:(i)*nPtsPerClust)       = x(:,1+(i-1)*nPtsPerClust:(i)*nPtsPerClust) + repmat(m(:,i),1,nPtsPerClust);   
end

tic
[clustCent,point2cluster,clustMembsCell] = MeanShiftCluster(x,bandwidth);
toc

numClust = length(clustMembsCell);


figure(10),clf,hold on
cVec = 'bgrcmykbgrcmykbgrcmykbgrcmyk'; % color to display computed cluster
for k = 1:min(numClust,length(cVec))
    myMembers = clustMembsCell{k};
    myClustCen = clustCent(:,k);
    plot(x(1,myMembers),x(2,myMembers),[cVec(k) '.'])
    plot(myClustCen(1),myClustCen(2),'o','MarkerEdgeColor','k','MarkerFaceColor',cVec(k), 'MarkerSize',10)
end
title(['no shifting, numClust:' int2str(numClust)])
