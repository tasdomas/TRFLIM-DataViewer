#include "sdt.h"

SDT::SDT(string fname) {
  fstream in(fname.c_str(), ios::binary | ios::in);
  in.seekg(0);
  in >> header;

  file_info = (char*)calloc(1, header.info_length+1);
  in.seekg(header.info_offset, ios::beg);
  in.read(file_info, header.info_length);

  setup = (char*)calloc(1, header.setup_length);
  in.seekg(header.setup_offset, ios::beg);
  in.read(setup, header.setup_length);

  data_headers = NULL;
  data_headers = new DataBlockHeader[header.data_count];
  ulong offs = header.data_offset;
  for (int i = 0; i < header.data_count; i++) {
    in.seekg(offs, ios::beg);
    in >> data_headers[i];
    offs = data_headers[i].next_block_offset;
  }

  //load measurement description blocks
  meas_blocks = new MeasurementDescriptionBlock[header.meas_desc_count];
  for (int i = 0; i < header.meas_desc_count; i++) {
    in.seekg(header.meas_desc_offset + header.meas_desc_length * i, ios::beg);
    in >> meas_blocks[i];
  }

  cout << meas_blocks[0].adc_re << endl;
}

SDT::~SDT() {
  free(file_info);
  file_info = NULL;
 
  free(setup);
  setup = NULL;

  if (data_headers != NULL) {
    delete [] data_headers;
    data_headers = NULL;
  }
  
  if (meas_blocks != NULL) {
    delete [] meas_blocks;
    meas_blocks = NULL;
  }

}
