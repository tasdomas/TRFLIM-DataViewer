#include "fileformat.h"

ushort rd_sh (istream &is) {
  ushort out;
  unsigned char t;
  is >> t;
  out = t << 8;
  is >> t;
  out = out | t;

  return out;
}

istream& operator >>(istream &is, FileHeader &obj) {
  obj.revision = rd_sh(is);

  return is;
}

