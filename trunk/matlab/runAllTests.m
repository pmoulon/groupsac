disp('**************** Unit tests for estimators **************** ');
cd estimators; runtests; cd ..;

disp('**************** Unit tests for grouping ****************');
cd grouping; runtests; cd ..;

disp('**************** Unit tests for ransac ****************');
cd ransac; runtests; cd ..;

disp('**************** Unit tests for interfaces ****************');
runtests;
