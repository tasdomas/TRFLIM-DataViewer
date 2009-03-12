#ifndef DV_SDT
#define DV_SDT

#include "fileformat.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class SDT {
  public:
    SDT(string fname);
    ~SDT();

    ushort * GetDataBlock(int i = 0);

  protected:
    FileHeader header;
    char * file_info;
    char * setup;

    ushort ** data_blocks;

    DataBlockHeader * data_headers;
    MeasurementDescriptionBlock * meas_blocks;
};
#endif
