#ifndef DV_FILEFORMAT
#define DV_FILEFORMAT

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

class FileHeader {
public:
  ushort revision;

  ulong info_offset;
  ushort info_length;

  ulong setup_offset;
  ushort setup_length;

  ulong data_offset; //offset to the first data block
  ushort data_count; //number of data blocks
  ulong data_block_length; //length of the longest data block
  
  ulong meas_desc_offset; //offset of the first measurement description block
  ushort meas_desc_count;
  ushort meas_desc_length; 
  
  ushort header_valid;
  ulong reserved1;
  ushort reserved2;
  ushort chksum;

  friend istream& operator >>(istream &is, FileHeader &obj);
};

class DataBlockHeader {
public:
  short block_no;
  long data_offset;
  long next_block_offset;
  ushort block_type;
  short meas_desc_no; //number of the measurement description block
  ulong lblock_no;
  ulong block_length;
  friend istream& operator >>(istream &is, DataBlockHeader &obj);
};

#endif
