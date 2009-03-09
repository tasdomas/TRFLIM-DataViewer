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

  protected:
    FileHeader header;
    char * file_info;
    char * setup;

    DataBlockHeader * data_headers;
};
#endif
