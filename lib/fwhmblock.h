#ifndef DV_FWHM_BLOCK_H
#define DV_FWHM_BLOCK_H

#include "../fileformat/datablock.h"
#include <math.h>

class FWHMBlock : public DataBlock {
 public:
  FWHMBlock(DataBlock * data);

 private:
  DataBlock * original;

  void CalculateFWHM();
  void CalculateIntensity();
};

#endif
