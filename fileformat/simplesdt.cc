#include "simplesdt.h"

SimpleSDT::SimpleSDT(string fname) {
  setup = NULL;
  file_info = NULL;
  meas_blocks = NULL;
  data_headers = NULL;

  SimpleBlock img(fname);

  data.push_back(img);
}
