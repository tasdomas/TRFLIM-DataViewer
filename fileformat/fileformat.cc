#include "fileformat.h"

ushort rd_sh (istream &is) {
  ushort out = 0;
  unsigned char t;
  for (int i = 0; i < 2; i++) {
    is >> t;
    out = out | t << 8*i;
  }

  return out;
}

ulong rd_l (istream &is) {
   ulong out = 0;
   unsigned char t;
   for (int i = 0; i < 4; i++) {
     is >> t;
     out = out | (ulong)(t << 8*i);
   }
   return out;
}

istream& operator >>(istream &is, FileHeader &obj) {
  obj.revision = rd_sh(is);
  obj.info_offset = rd_l(is);
  obj.info_length = rd_sh(is);
  obj.setup_offs = rd_l(is);
  obj.setup_length = rd_sh(is);
  obj.data_offset = rd_l(is);
  obj.data_count = rd_sh(is);
  return is;
}

