#ifndef DV_FITTER_H

#define DV_FITTER_H

#include "../include/lmfit/lmmin.h"
#include "../include/lmfit/lm_eval.h"
#include <vector>
#include <math.h>

using namespace std;

class Fitter {

 public:
  Fitter(vector<float> x, vector<float> y);
  ~Fitter();

  void SetComponentCount(int count);

  bool Fit();

  vector<double> GetParameters();

  vector<float> GetFitted();
  vector<float> GetTime();

  double Chi();

 private:
  double * x;
  double * y;
  double * components;
  int size;
  int compCount;
};

double Function(double x, double * p);
  
#endif
