#ifndef DV_SIMPLEBLOCK
#define DV_SIMPLEBLOCK

#include "../fileformat/datablock.h"

#include <string>
#include <fstream>

using namespace std;

class SimpleBlock : public DataBlock {
 public:
  SimpleBlock(string fname);

};

#endif
