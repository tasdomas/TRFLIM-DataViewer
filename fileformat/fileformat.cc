#include "fileformat.h"


float rd_fl (istream &is) {
  long out = 0;
  unsigned char t;
  for (int i = 0; i < 4; i++) {
    is.read((char*)&t, 1);
    //cout << hex << is.tellg() << " -> " << (unsigned int)t << endl;
    out = out | t << 8*i;
  }
  float * ret = (float*)&out;
  return *ret;
}

uushort rd_sh (istream &is) {
  uushort out = 0;
  unsigned char t;
  for (int i = 0; i < 2; i++) {
    is.read((char*)&t, 1);
    //cout << hex << is.tellg() << " -> " << (unsigned int)t << endl;
    out = out | t << 8*i;
  }

  return out;
}

uulong rd_l (istream &is) {
  uulong out = 0;
  unsigned char t;
  for (int i = 0; i < 4; i++) {
    is.read((char*)&t, 1);
    //cout << hex << is.tellg() << " -> " << (unsigned int)t << endl;
    //cout << hex << (unsigned int)t << endl;
    out = out | (uulong)(t << 8*i);
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
  
istream& operator >>(istream &is, MeasurementDescriptionBlock &obj) {
  is.read(obj.time, 9);
  is.read(obj.date, 11);
  is.read(obj.mod_ser_no, 16);
  obj.meas_mode = rd_sh(is);
  obj.cfd_ll = rd_fl(is);
  obj.cfd_lh = rd_fl(is);
  obj.cfd_zcl = rd_fl(is);
  obj.cfd_hf = rd_fl(is);
  obj.syn_zc = rd_fl(is);
  obj.syn_fd = rd_sh(is);
  obj.syn_hf = rd_fl(is);
  obj.tac_r = rd_fl(is);
  obj.tac_g = rd_sh(is);
  obj.tac_of = rd_fl(is);
  obj.tac_ll = rd_fl(is);
  obj.tac_lh = rd_fl(is);
  obj.adc_re = rd_sh(is);
  obj.eal_de = rd_sh(is);
  obj.ncx = rd_sh(is);
  obj.ncy = rd_sh(is);
  obj.page = rd_sh(is);
  obj.col_t = rd_fl(is);
  obj.rep_t = rd_fl(is);
  obj.stopt = rd_sh(is);
  is >> obj.overfl;
  obj.use_motor = rd_sh(is);
  obj.steps = rd_sh(is);
  obj.offset = rd_fl(is);
  obj.dither = rd_sh(is);
  obj.incr = rd_sh(is);
  obj.mem_bank = rd_sh(is);
  is.read(obj.mod_type, 16);
  obj.syn_th = rd_fl(is);
  obj.dead_time_comp = rd_sh(is);
  obj.polarity_l = rd_sh(is);
  obj.polarity_f = rd_sh(is);
  obj.polarity_p = rd_sh(is);
  obj.accumulate = rd_sh(is);
  obj.flbck_y = rd_l(is);
  obj.flbck_c = rd_l(is);
  obj.bord_ul = rd_l(is);
  obj.bord_l = rd_l(is);
  obj.pix_time = rd_fl(is);
  obj.pix_clkl = rd_sh(is);
  obj.trigger = rd_sh(is);
  obj.scan_x = rd_l(is);
  obj.scan_y = rd_l(is);
  obj.scan_rx = rd_l(is);
  obj.scan_ry = rd_l(is);
  obj.fifo_typ = rd_sh(is);
  obj.epx_div = rd_l(is);
  obj.mod_type_code = rd_l(is);
  obj.overflow_corr_factor = rd_fl(is);
  obj.adc_zoom = rd_l(is);
  obj.cycles = rd_l(is);
  
  return is;
}
