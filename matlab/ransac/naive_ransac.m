% test for naive ransac
function [] = naive_ransac ()

global vis_map % global gui variables

%% load simulation data
S = load('data/group_ransac/resection/08-09-27/simulation-sjsu-08-09-27.mat');
%S = load('fundmat-08-10-04.mat');
is_inlier = S.is_inlier;
vis_map = S.vis_map;

%% control parameters
test_num = 20;              % how many tests to repeat
gui = false;                % show gui or not
min_sample_num = 6;            % the minimum sample size
fun_draw = update_vis_map(is_inlier);

%% display simulation data statistics
[datum_num, group_num] = size(vis_map);
disp('********************************************');
disp(sprintf('%d putatives in %d groups', datum_num, group_num));
disp(sprintf('inlier num:%d',sum(is_inlier)));

%% draw the orignial visibility map as background
if gui
    figure('Position',[100 100 1000 1000]); 
    map_color = [0.8 0.8 0.8];
    draw_vis_map(vis_map, map_color); drawnow;
    fun_draw(1:size(xs1,2));
    while waitforbuttonpress == 0
    end
end

%% ranac rounds
rounds = zeros(test_num,1);
for test=1:test_num
    round = ransac(size(vis_map,1), @evaluate_samples, -1, fun_draw, min_sample_num, inf, gui);
    rounds(test) = round;
end

if test_num > 1 figure; hist(rounds); end
disp(sprintf('the average round=%g', mean(rounds)));

%% evaluate a minimum sample
    function [inliers] = evaluate_samples(sampled)
        if sum(is_inlier(sampled)) == min_sample_num
            inliers = 1:size(vis_map,1);
        else
            inliers = [];
        end
    end
end