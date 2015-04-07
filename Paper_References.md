# Ransac #
**Random sample consensus: a paradigm for model fitting with applications to image analysis and automated cartography.**
[Wikipedia RANSAC article](http://en.wikipedia.org/wiki/RANSAC)

A line fitting example : 'Find the best line model that fit the most of the point."

![http://upload.wikimedia.org/wikipedia/commons/thumb/b/b9/Line_with_outliers.svg/255px-Line_with_outliers.svg.png](http://upload.wikimedia.org/wikipedia/commons/thumb/b/b9/Line_with_outliers.svg/255px-Line_with_outliers.svg.png)
![http://upload.wikimedia.org/wikipedia/commons/thumb/d/de/Fitted_line.svg/255px-Fitted_line.svg.png](http://upload.wikimedia.org/wikipedia/commons/thumb/d/de/Fitted_line.svg/255px-Fitted_line.svg.png)

# GroupsSAC #
**GroupSAC: Efficient Consensus in the Presence of Groupings, Kai Ni, Hailin Jin, and Frank Dellaert, IEEE Interational Conference on Computer Vision, 2009**

http://www.cc.gatech.edu/~nikai/assets/Ni09iccv.pdf

GroupSAC algorithm:
  * Group the putatives (application dependent).
  * Select a small set of groups.
  * Sample points from those groups.
  * Stop until we meet the termination criteria.

An example that show optical flow clustering inside putatives correspondence matches.

![http://web.me.com/dellaert/FrankDellaert/Publications/Entries/2009/7/16_GroupSAC_(ICCV_09)_files/shapeimage_2.png](http://web.me.com/dellaert/FrankDellaert/Publications/Entries/2009/7/16_GroupSAC_(ICCV_09)_files/shapeimage_2.png)