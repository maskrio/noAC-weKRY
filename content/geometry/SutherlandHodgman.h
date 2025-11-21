/**
 * Author: Kevin
 * Date: 2019-10-29
 * License: Unknown
 * Source: https://codeforces.com/gym/101673/submission/50481926
 * Description: Ada 2 poligon, cari poligon intersectionnya
 * poly point hasilnya, clipper pemotongnya
 * Time: $O(N)$
 * Status: -
 */
void clip(vector <point>& poly_points, point point1, point point2) {
  vector <point> new_points;
  new_points.clear();
  for(int i = 0; i < poly_points.size(); i++) {
    int k = (i + 1) % poly_points.size();
    double i_pos = ccw(point1, point2, poly_points[i]);
    double k_pos = ccw(point1, point2, poly_points[k]);
    //in in
    if(i_pos <= 0  && k_pos <= 0)
      new_points.push_back(poly_points[k]);
    //out in
    else if(i_pos > 0  && k_pos <= 0) {
      new_points.push_back(intersect(point1, point2, poly_points[i],
                                     poly_points[k]));
      new_points.push_back(poly_points[k]);
    }
    // in out
    else if(i_pos <= 0  && k_pos > 0) {
      new_points.push_back(intersect(point1, point2, poly_points[i],
                                     poly_points[k]));
    }
    //out out
    else {
    }
  }
  poly_points.clear();
  for(int i = 0; i < new_points.size(); i++)
    poly_points.push_back(new_points[i]);
}
double area(const vector <point>& P) {
  double result = 0.0;
  double x1, y1, x2, y2;
  for(int i = 0; i < P.size() - 1; i++) {
    x1 = P[i].x;
    y1 = P[i].y;
    x2 = P[i + 1].x;
    y2 = P[i + 1].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2;
}
void suthHodgClip(vector <point>& poly_points, vector <point> clipper_points) {
  for(int i = 0; i < clipper_points.size(); i++) {
    int k = (i + 1) % clipper_points.size();
    clip(poly_points, clipper_points[i], clipper_points[k]);
  }
}
vector<point> sortku(vector<point> P) {
  int P0 = 0;
  int i;
  for(i = 1; i < 3; i++) {
    if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;
  }
  point temp = P[0];
  P[0] = P[P0];
  P[P0] = temp;
  pivot = P[0];
  sort(++P.begin(), P.end(), anglecmp);
  reverse(++P.begin(), P.end());
  return P;
}
int main {
  clipper_points = sortku(clipper_points);
  suthHodgClip(poly_points, clipper_points);
}