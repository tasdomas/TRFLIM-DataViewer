#ifndef DV_COMPONENT_BLOCK_H
#define DV_COMPONENT_BLOCK_H

#include "../fileformat/datablock.h"
#include "../include/newmat/newmat.h"
#include "../include/newmat/newmatap.h"

#include <math.h>
#include <vector>

#define WANT_MATH
using namespace std;

class ComponentBlock : public DataBlock {

 public:
  ComponentBlock(DataBlock * data);
  ~ComponentBlock();

  void Compute(float sigma, int count, vector<float> & tau);


 private:
  DataBlock * original;

  vector<float> lifetimes;
  float sigma_t;
  int components;
  
  void ConstructIRF(); //construct the IRF matrix
  void LinearizeData(); //linearize datablock, reducing a set of matrices to a single matrix
  void RemoveIRF();
  void CreateExponential();
  void InvertExponential();
  void GetComponents();
  void DelinearizeData();

  Matrix * IRF;
  Matrix * D;
  Matrix * E;
  Matrix * C;
};
#endif
