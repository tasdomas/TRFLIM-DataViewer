#ifndef DV_SVD_BLOCK_H
#define DV_SVD_BLOCK_H

#include "../fileformat/datablock.h"
#include "../include/newmat/newmat.h"
#include "../include/newmat/newmatap.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include "../include/newmat/newmatio.h"

#define WANT_MATH
using namespace std;

class SVDBlock : public DataBlock {
 public:
  SVDBlock(DataBlock & data);

  vector<float> GetSV();
  vector<float> GetXs();

 private:
  void CalcSVD();
  vector<float> svs;
};

#endif
