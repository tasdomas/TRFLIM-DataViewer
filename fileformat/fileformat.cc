#include "fileformat.h"


ushort rd_b (istream &is) {
  ushort out = 0;
  unsigned char t;
  for (int i = 0; i < 1; i++) {
    is.read((char*)&t, 1);
    //cout << hex << is.tellg() << " -> " << (unsigned int)t << endl;
    out = out | t << 8*i;
  }

  return out;
}

ushort rd_sh (istream &is) {
  ushort out = 0;
  unsigned char t;
  for (int i = 0; i < 2; i++) {
    is.read((char*)&t, 1);
    //cout << hex << is.tellg() << " -> " << (unsigned int)t << endl;
    out = out | t << 8*i;
  }

  return out;
}

ulong rd_l (istream &is) {
  ulong out = 0;
  unsigned char t;
  for (int i = 0; i < 4; i++) {
    is.read((char*)&t, 1);
    //cout << hex << is.tellg() << " -> " << (unsigned int)t << endl;
    //cout << hex << (unsigned int)t << endl;
    out = out | (ulong)(t << 8*i);
  }
  return out;
}

istream& operator >>(istream &is, FileHeader &obj) {
  obj.revision = rd_sh(is);
  obj.info_offset = rd_l(is);
  obj.info_length = rd_sh(is);
  obj.setup_offset = rd_l(is);
  obj.setup_length = rd_sh(is);
  obj.data_offset = rd_l(is);
  obj.data_count = rd_sh(is);
  obj.data_block_length = rd_l(is);
  obj.meas_desc_offset = rd_l(is);
  obj.meas_desc_count = rd_sh(is);
  obj.meas_desc_length = rd_sh(is);
  obj.header_valid = rd_sh(is);
  obj.reserved1 = rd_l(is);
  obj.reserved2 = rd_sh(is);
  obj.chksum = rd_sh(is);
  return is;
}

istream& operator >>(istream &is, DataBlockHeader &obj) {
  obj.block_no = rd_sh(is); 
  obj.data_offset = rd_l(is);
  obj.next_block_offset = rd_l(is);
  obj.block_type = rd_sh(is);
  obj.meas_desc_no = rd_sh(is);
  obj.lblock_no = rd_l(is);
  obj.block_length = rd_l(is);
  return is;
}
