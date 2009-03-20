#ifndef DV_SDT
#define DV_SDT

#include "fileformat.h"
#include "datablock.h"

#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class SDT {
  public:
    SDT(string fname);
    ~SDT();
    int GetSetupParam(string param);
    DataBlock * GetDataBlock(int i = 0);
    int GetBlockCount();
    string GetSetupData();

  protected:
    FileHeader header;
    char * file_info;
    char * setup;

    vector<DataBlock> data;

    DataBlockHeader * data_headers;
    MeasurementDescriptionBlock * meas_blocks;
};
#endif
