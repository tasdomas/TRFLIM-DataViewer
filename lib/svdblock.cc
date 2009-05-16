#include "svdblock.h"

SVDBlock::SVDBlock(DataBlock & data) 
  : DataBlock(data) {
}

void SVDBlock::CalcSVD() {
  int sx = GetX();
  int sy = GetY();
  int sz = GetZ();
  Matrix D( sx * sy, sz);
  for (int z = 0; z < sz; z++) {
    for (int y = 0; y < sy; y++) {
      for (int x = 0; x < sx; x++) {
        D.element(y*sx + x, z) = GetPoint(x, y, z);
      }
    }
  }
  
  Matrix U, V;
  DiagonalMatrix S;
  SVD(D, S, U, V, false);
  
  for (int i = 0; i < S.nrows(); i++) {
    svs.push_back(S.element(i, i));
  }  
}

vector<float> SVDBlock::GetSV() {
  if (svs.size() == 0) {
    CalcSVD();
  }
  return svs;
}

vector<float> SVDBlock::GetXs() {
  if (svs.size() == 0) {
    CalcSVD();
  }
  vector<float> x;
  for (unsigned int i = 1; i <= svs.size(); i++) {
    x.push_back((float)i);
  }
  return x;
}
           
