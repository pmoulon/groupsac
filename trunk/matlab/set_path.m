%% set path for GroupRANSAC project

current = which('set_path');
current = current(1:strfind(current,'set_path.m')-1);
path([current 'estimators'], path);
path([current 'ransac'], path);
path([current 'thirdParty/vgg/vgg_multiview'], path);
path([current 'thirdParty/vgg/vgg_numerics'], path);

