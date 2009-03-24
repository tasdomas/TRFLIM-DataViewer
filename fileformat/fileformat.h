#ifndef DV_FILEFORMAT
#define DV_FILEFORMAT

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include "typedef.h"
#include "../lib/exception.h"

using namespace std;

class FileHeader {
public:
  uushort revision;

  uulong info_offset;
  uushort info_length;

  uulong setup_offset;
  uushort setup_length;

  uulong data_offset; //offset to the first data block
  uushort data_count; //number of data blocks
  uulong data_block_length; //length of the longest data block
  
  uulong meas_desc_offset; //offset of the first measurement description block
  uushort meas_desc_count;
  uushort meas_desc_length; 
  
  uushort header_valid;
  uulong reserved1;
  uushort reserved2;
  uushort chksum;

  friend istream& operator >>(istream &is, FileHeader &obj);
};

class DataBlockHeader {
public:
  short block_no;
  long data_offset;
  long next_block_offset;
  uushort block_type;
  short meas_desc_no; //number of the measurement description block
  uulong lblock_no;
  uulong block_length;
        
  friend istream& operator >>(istream &is, DataBlockHeader &obj);
};

class MeasurementDescriptionBlock {
public:
  char time[9];
  char date[11];
  char mod_ser_no[16];
  short meas_mode;
  float cfd_ll;
  float cfd_lh;
  float cfd_zcl;
  float cfd_hf;
  float syn_zc;
  short syn_fd;
  float syn_hf;
  float tac_r;
  short tac_g;
  float tac_of;
  float tac_ll;
  float tac_lh;
  short adc_re;
  short eal_de;
  short ncx;
  short ncy;
  uushort page;
  float col_t;
  float rep_t;
  short stopt;
  char overfl;
  short use_motor;
  short steps;
  float offset;
  short dither;
  short incr;
  short mem_bank;
  char mod_type[16];
  float syn_th;
  short dead_time_comp;
  short polarity_l;
  short polarity_f;
  short polarity_p;
  short linediv;
  short accumulate;
  int flbck_y;
  int flbck_c;
  int bord_ul;
  int bord_l;
  float pix_time;
  short pix_clkl;
  short trigger;
  int scan_x;
  int scan_y;
  int scan_rx;
  int scan_ry;
  short fifo_typ;
  int epx_div;
  int mod_type_code;
  float overflow_corr_factor;
  int adc_zoom;
  int cycles;
  friend istream& operator >>(istream &is, MeasurementDescriptionBlock &obj);
};



#endif
