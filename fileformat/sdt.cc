#include "sdt.h"

SDT::SDT(string fname) {
  fstream in(fname.c_str(), ios::binary | ios::in);

  in >> header;

  file_info = (char*)calloc(1, header.info_length+1);
  in.seekg(header.info_offset, ios::beg);
  in.read(file_info, header.info_length);

  setup = (char*)calloc(1, header.setup_length);
  in.seekg(header.setup_offset, ios::beg);
  in.read(setup, header.setup_length);

  cout << setup;
}

SDT::~SDT() {
}
