#include "sdt.h"

SDT::SDT(string fname) {
  fstream in(fname.c_str(), ios::binary | ios::in);

  in >> header;

  file_info = (char*)calloc(1, header.info_length+1);
  in.seekg(header.info_offset, ios::beg);
  in.read(file_info, header.info_length);

  cout << file_info;
}

SDT::~SDT() {
}
