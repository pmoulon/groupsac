function test_suite = testRansacRoundsNeeded
initTestSuite;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testSimple
max_rounds = 1e5;
min_sample_num = 7;
l1mp = log(1 - 0.99);
datum_num = 200;
inlier_num = 120;
rounds = ransacRoundsNeeded(max_rounds, min_sample_num, l1mp, datum_num, inlier_num);
assertEqual(ceil(l1mp/log(1-(120/200)^7)), rounds);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function testWithNoise
max_rounds = 1;
min_sample_num = 7;
l1mp = log(1 - 0.99);
datum_num = 200;
inlier_num = 120;
rounds = ransacRoundsNeeded(max_rounds, min_sample_num, l1mp, datum_num, inlier_num);
assertEqual(1, rounds);

   
%#ok<*STOUT> 
%#ok<*DEFNU>
