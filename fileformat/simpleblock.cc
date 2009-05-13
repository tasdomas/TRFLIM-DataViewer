#include "simpleblock.h"

SimpleBlock::SimpleBlock(string fname) {
  ifstream in(fname.c_str());

  in.seekg(0);

  in >> size_x >> size_y >> size_z;

  block = new uushort*[size_z];

  for (int z = 0; z < size_z; z++) {
    block[z] = new uushort[size_x*size_y];
  }

  int x, y, z;
  uushort val;
  while (! in.eof()) {
    in >> x >> y >> z >> val;
    block[z][x + y * size_x] = val;
  }

  x_low = y_low = z_low = 0;

  x_high = size_x;
  y_high = size_y;
  z_high = size_z;

  time_step = 1;

  in.close();
}
