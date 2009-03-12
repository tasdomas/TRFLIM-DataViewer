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

  data_blocks = new ushort*[header.data_count];
  data_headers = new DataBlockHeader[header.data_count];
  ulong offs = header.data_offset;
  for (int i = 0; i < header.data_count; i++) {
    in.seekg(offs, ios::beg);
    in >> data_headers[i];
    offs = data_headers[i].next_block_offset;

    data_blocks[i] = new ushort[data_headers[i].block_length / 2];
    in.seekg(data_headers[i].data_offset, ios::beg);
    for (int j = 0; j < data_headers[i].block_length / 2; j++) {
      data_blocks[i][j] = rd_sh(in);
    }
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

  if (data_blocks != NULL) {
    /*
    for (int i = 0; i < header.data_count; i++) {
      delete [] data_blocks[i];
    }
    */
    delete [] data_blocks;
    data_blocks = NULL;
  }

}

ushort * SDT::GetDataBlock(int i) {
  if (i < header.data_count) {
    return data_blocks[i];
  }

}
