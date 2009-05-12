#ifndef DV_DATABLOCK
#define DV_DATABLOCK

#include "typedef.h"

#include <stdlib.h>
#include <vector>

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

  vector<float> GetPoint(int x, int y);
  vector<float> GetTime();

  //dimensions of the block
  int GetX();
  int GetY();
  int GetZ();

  //true dimensions (unmargined)
  int GetTrueX();
  int GetTrueY();
  int GetTrueZ();

  //block data margins
  void SetMarginX(int low=0, int high=-1);
  void SetMarginY(int low=0, int high=-1);
  void SetMarginZ(int low=0, int high=-1);

  void ResetMargins();

  void GetMarginX(int & low, int & high);
  void GetMarginY(int & low, int & high);
  void GetMarginZ(int & low, int & high);

protected:
  uushort ** block;
  int size_x;
  int size_y;
  int size_z;

  int x_low, x_high;
  int y_low, y_high;
  int z_low, z_high;

  float time_step;

};

#endif
