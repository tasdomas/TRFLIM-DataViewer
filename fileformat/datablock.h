#ifndef DV_DATABLOCK
#define DV_DATABLOCK

#include "typedef.h"

#include <stdlib.h>

using namespace std;

class FWHMBlock;

class DataBlock {
  friend class FWHMBlock;

public:
  DataBlock(uushort * data, int size, int scan_x, int scan_y, int adc_res, float time);
  DataBlock(int scan_x, int scan_y, int scan_z = 1);
  DataBlock(const DataBlock & origin);
  DataBlock & operator=(const DataBlock & origin);
  ~DataBlock();
  
  uushort * GetImage(int z);
  uushort GetPoint(int x, int y, int z);

  void SetData(uushort * data, int size);
  float GetTimeScale();

  int GetX();
  int GetY();
  int GetZ();

protected:
  uushort ** block;
  int size_x;
  int size_y;
  int size_z;
  float time_step;

};

#endif
