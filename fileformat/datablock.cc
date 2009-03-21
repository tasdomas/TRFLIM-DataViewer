#include "datablock.h"

DataBlock::DataBlock(ushort * data, int size, int scan_x, int scan_y, int adc_res) {
 
  if (size != scan_x * scan_y * adc_res) {
    //throw exception
  }
  block = new ushort*[adc_res];

  for (int j = 0; j < adc_res; j++) {
    //going through all the adc points
    ushort * at_z = new ushort[scan_x*scan_y];
    
    for (int i = 0; i < scan_x * scan_y; i++) {
      //all the image points
      at_z[i] = data[j + i*adc_res];
    }
    block[j] = at_z;
  }

  size_x = scan_x;
  size_y = scan_y;
  size_z = adc_res;
}

DataBlock::DataBlock(int scan_x, int scan_y, int adc_res) {
  block = new ushort*[adc_res];
  for (int i = 0; i < adc_res; i++) {
    block[i] = new ushort[scan_x*scan_y];
  }

  size_x = scan_x;
  size_y = scan_y;
  size_z = adc_res;
}

DataBlock::DataBlock(const DataBlock & origin) {
  block = new ushort*[origin.size_z];
  size_x = origin.size_x;
  size_y = origin.size_y;
  size_z = origin.size_z;

  for (int i = 0; i < origin.size_z; i++) {
    ushort * at_z = new ushort[origin.size_x * origin.size_y];
    for (int j = 0; j < size_x*size_y; j++) {
      at_z[j] = origin.block[i][j];
    }
    block[i] = at_z;
  }
}
  
DataBlock & DataBlock::operator=(const DataBlock & origin) {
  if (block != NULL) {
    delete [] block;
  }
  block = new ushort*[origin.size_z];
  size_x = origin.size_x;
  size_y = origin.size_y;
  size_z = origin.size_z;

  for (int i = 0; i < origin.size_z; i++) {
    ushort * at_z = new ushort[origin.size_x * origin.size_y];
    for (int j = 0; j < size_x*size_y; j++) {
      at_z[j] = origin.block[i][j];
    }
    block[i] = at_z;
  }
  return *this;
}

DataBlock::~DataBlock() {
  if (block != NULL) {
    delete [] block;
  }
}

ushort * DataBlock::GetImage(int z) {
  if ((z >= 0) && (z < size_z)) {
    return block[z];
  } else {
    return NULL;
    //throw an exception
  }
}

int DataBlock::GetX() {
  return size_x;
}

int DataBlock::GetY() {
  return size_y;
}

int DataBlock::GetZ() {
  return size_z;
}

void DataBlock::SetData(ushort * data, int size) {
  if (size_x * size_y * size_z == size) {
    for (int j = 0; j < size_z; j++) {
      //going through all the adc points
      for (int i = 0; i < size_x * size_y; i++) {
        //all the image points
        block[j][i] = data[j + i*size_z];
      }
    }
  }
}
