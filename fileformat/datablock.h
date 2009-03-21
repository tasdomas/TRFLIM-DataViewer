#ifndef DV_DATABLOCK
#define DV_DATABLOCK

#include <stdlib.h>
using namespace std;

class DataBlock {
public:
  DataBlock(ushort * data, int size, int scan_x, int scan_y, int adc_res);
  DataBlock(int scan_x, int scan_y, int scan_z = 1);
  DataBlock(const DataBlock & origin);
  DataBlock & operator=(const DataBlock & origin);
  ~DataBlock();
  
  ushort * GetImage(int z);

  void SetData(ushort * data, int size);

  int GetX();
  int GetY();
  int GetZ();

private:
  ushort ** block;
  int size_x;
  int size_y;
  int size_z;

};

#endif
