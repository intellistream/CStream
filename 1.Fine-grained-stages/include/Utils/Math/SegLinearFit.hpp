#ifndef ADB_INCLUDE_UTILS_MATH_SegLinearFit_H_
#define ADB_INCLUDE_UTILS_MATH_SegLinearFit_H_
#include <Utils/Math/LeastSquare.hpp>
using namespace std;
using namespace MATH_FUNC;
namespace MATH_FUNC {

/*class:SegLinearFit
description: The class of a segment linear fit

date:202101115
*/
class SegLinearFit {
 private:

  /*coeff is the a,b for each seg,
  letting y=a*x+n, then
  coeff[2*i] is the a for [i]th segmentation
  coeff[2*i+1] s the b for [i]th segmentation,
  i starts from 0 in C++
  */
  vector<double> coeff;
  /*size(seg)=segmentaions+1,
  each segmentation is seg[i]<x<=seg[i+1], so the seg must be sorted
  */
  vector<double> seg;

  double inlineCalculate(double x) {
    //first, deciding the seg
    size_t i = 0;
    for (i = 0; i < seg.size() - 1; i++) {
      if (x > seg[i] && x <= seg[i + 1]) {
        double a = coeff[2 * i];
        double b = coeff[2 * i + 1];
        return a * x + b;
      }
    }
    return 0;
  }
 public:
// train set with segment
  SegLinearFit(vector<double> x, vector<double> y, vector<double> _seg) {
    setSegment(_seg);
    train(x, y);
  }
  // train set without sement
  SegLinearFit(vector<double> x, vector<double> y, double ratio) {

    trainWithoutSeg(x, y, ratio);
  }
  // already trainned coeff and segment
  SegLinearFit(vector<double> _coeff, vector<double> _seg) {
    setSegment(_seg);
    setCoeff(_coeff);
  }
  void setSegment(vector<double> _seg) {
    seg = _seg;
  }
  void setCoeff(vector<double> _coeff) {
    coeff = _coeff;
  }
  void train(vector<double> x, vector<double> y);
  /*train data without segmentation input, and auto do the segmentation according to ratio
  generally, ratio ranges in 0 to 1*/
  void trainWithoutSeg(vector<double> x, vector<double> y, double ratio);
  ~SegLinearFit() {

  }
  string getEquation() {
    size_t i;
    string ru = "";
    for (i = 0; i < seg.size() - 1; i++) {

      double a = coeff[2 * i];
      double b = coeff[2 * i + 1];
      ru += "seg" + to_string(i) + ": y=" + to_string(a) + "*x+(" + to_string(b) + "),";
      ru += "for " + to_string(seg[i]) + "<x<=" + to_string(seg[i + 1]) + ";\r\n";

    }
    return ru;
  }
  vector<double> getCoeff() {
    return coeff;
  }
  vector<double> getSeg() {
    return seg;
  }
  //calculate for only one value
  double forward(double x) {
    return inlineCalculate(x);
  }
  //cacu;ate for vector
  vector<double> forward(vector<double> x) {
    size_t n = x.size();
    vector<double> y(n);
    for (size_t i = 0; i < n; i++) {
      y[i] = inlineCalculate(x[i]);
    }
    return y;
  }
};

}

#endif