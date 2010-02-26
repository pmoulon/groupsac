#ifndef GROUPSAC_ESTIMATORS_POINTTOLINEDIST_H
#define GROUPSAC_ESTIMATORS_POINTTOLINEDIST_H

class vec;

namespace groupsac  {
namespace estimators  {

/**
* The distance between the given point and the line y=ax+b, i.e. ax-y+b=0
*
* \param[in] ab (ax+b line equation).
* \param[in] pt (The point on which distance will be computed).  
*
* \return The distance from the point to the line.
* http://mathworld.wolfram.com/Point-LineDistance2-Dimensional.html
*/
double pt2LineDist(const vec & ab,const vec & pt)  {
  //dist = abs(ab(1)*pt(1) - pt(2) + ab(2)) / sqrt(ab(1) * ab(1) + 1);
  return -1.0f; ///Todo(pmoulon) wait the matrix framework
}

}; // namespace estimators
}; // namespace groupsac

#endif //GROUPSAC_ESTIMATORS_POINTTOLINEDIST_H
