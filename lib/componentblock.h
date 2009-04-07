#ifndef DV_COMPONENT_BLOCK_H
#define DV_COMPONENT_BLOCK_H

#include "../fileformat/datablock.h"
#include "../include/newmat/newmat.h"

#include <math.h>
#include <vector>
using namespace std;

class ComponentBlock : public DataBlock {

 public:
  ComponentBlock(DataBlock * data, float sigma, int count, vector<float> & tau);
  ~ComponentBlock();

 private:
  DataBlock * original;

  vector<float> lifetimes;
  float sigma_t;
  int components;
  
  void ConstructIRF();

  Matrix * IRF;
};
#endif
