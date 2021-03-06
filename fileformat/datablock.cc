#include "datablock.h"

DataBlock::DataBlock(uushort * data, int size, int scan_x, int scan_y, int adc_res, float time) {
 
  if (size != scan_x * scan_y * adc_res) {
    //throw exception
  }
  block = new uushort*[adc_res];

  for (int j = 0; j < adc_res; j++) {
    //going through all the adc points
    uushort * at_z = new uushort[scan_x*scan_y];
    
    for (int i = 0; i < scan_x * scan_y; i++) {
      //all the image points
      at_z[i] = data[j + i*adc_res];
    }
    block[j] = at_z;
  }

  size_x = scan_x;
  size_y = scan_y;
  size_z = adc_res;

  x_low = y_low = z_low = 0;
  x_high = size_x;
  y_high = size_y;
  z_high = size_z;

  max = 0;

  time_step = time;
}

DataBlock::DataBlock(int scan_x, int scan_y, int adc_res) {
  block = new uushort*[adc_res];
  for (int i = 0; i < adc_res; i++) {
    block[i] = new uushort[scan_x*scan_y];
  }

  size_x = scan_x;
  size_y = scan_y;
  size_z = adc_res;

  x_low = y_low = z_low = 0;
  x_high = size_x;
  y_high = size_y;
  z_high = size_z;

  max = 0;
  
}

DataBlock::DataBlock() {
  block = NULL;
  size_x = size_y = size_z = 0;
  x_low = y_low = z_low = 0;
  x_high = y_high = z_high = 0;

  max = 0;

  time_step = 0;
}  

DataBlock::DataBlock(const DataBlock & origin) {
  block = new uushort*[origin.size_z];
  size_x = origin.size_x;
  size_y = origin.size_y;
  size_z = origin.size_z;
  time_step = origin.time_step;
  max = origin.max;

  for (int i = 0; i < origin.size_z; i++) {
    uushort * at_z = new uushort[origin.size_x * origin.size_y];
    for (int j = 0; j < size_x*size_y; j++) {
      at_z[j] = origin.block[i][j];
    }
    block[i] = at_z;
  }

  x_low = origin.x_low;
  y_low = origin.y_low;
  z_low = origin.z_low;  
  x_high = origin.x_high;  
  y_high = origin.y_high;  
  z_high = origin.z_high;  
}
  
DataBlock & DataBlock::operator=(const DataBlock & origin) {
  if (block != NULL) {
    delete [] block;
  }
  block = new uushort*[origin.size_z];
  size_x = origin.size_x;
  size_y = origin.size_y;
  size_z = origin.size_z;
  time_step = origin.time_step;
  max = origin.max;

  for (int i = 0; i < origin.size_z; i++) {
    uushort * at_z = new uushort[origin.size_x * origin.size_y];
    for (int j = 0; j < size_x*size_y; j++) {
      at_z[j] = origin.block[i][j];
    }
    block[i] = at_z;
  }
  x_low = origin.x_low;
  y_low = origin.y_low;
  z_low = origin.z_low;  
  x_high = origin.x_high;  
  y_high = origin.y_high;  
  z_high = origin.z_high;  

  return *this;
}

DataBlock::~DataBlock() {
  if (block != NULL) {
    delete [] block;
  }
}

uushort * DataBlock::GetImage(int z) {
  if ((z >= 0) && (z < size_z)) {
    return block[z];
  } else {
    return NULL;
    //throw an exception
  }
}

int DataBlock::GetX() {
  return x_high - x_low;
}

int DataBlock::GetY() {
  return y_high - y_low;
}

int DataBlock::GetZ() {
  return z_high - z_low;
}

int DataBlock::GetTrueX() {
  return size_x;
}

int DataBlock::GetTrueY() {
  return size_y;
}

int DataBlock::GetTrueZ() {
  return size_z;
}

void DataBlock::SetData(uushort * data, int size) {
  if (size_x * size_y * size_z == size) {
    for (int j = 0; j < size_z; j++) {
      //going through all the adc points
      for (int i = 0; i < size_x * size_y; i++) {
        //all the image points
        block[j][i] = data[j + i*size_z];
      }
    }
  }
  max = 0;
}

uushort DataBlock::GetPoint(int x, int y, int z) {
  if ((z >= 0) && (z < GetZ()) &&
      (x >= 0) && (x < GetX()) &&
      (y >= 0) && (y < GetY())) {
    x += x_low;
    y += y_low;
    
    return block[z_low + z][x + y*size_x];
  } else {
    return -1;
    //throw exception!!!
  }
}

float DataBlock::GetTimeScale() {
  return time_step;
}

vector<float> DataBlock::GetPoint(int x, int y) {
  if ((x >= 0) && (x < GetX()) &&
      (y >= 0) && (y < GetY())) {
    vector<float> pts;
    for (int z = 0; z < GetZ(); z++) {
      pts.push_back(GetPoint(x, y, z));
    }
    return pts;
  }
}

vector<float> DataBlock::GetTime(bool offset) {
  //remove offset if necessary
  double mult = 1.0;
  if (time_step < 1.0e-8) {
    mult = 1.e9;
  }
  double off = 0.0;
  if (offset) {
    off = 1.0;
  }
  if (GetZ() > 0) {
    vector<float> time;
    for (int z = 0; z < z_high - z_low; z++) {
      double t = z + off*z_low;
      time.push_back(t*time_step*mult);
    }
    return time;
  }
}

void DataBlock::ResetMargins() {
  x_low = y_low = z_low = 0;
  x_high = size_x;
  y_high = size_y;
  z_high = size_z;
  max = 0;
}

void DataBlock::SetMarginX(int low, int high) {
  if (high < 0) {
    high = size_x;
  }
  if ((low >= 0) && (high <= size_x)) {
    x_low = low;
    x_high = high;
    max = 0;
  }
}

void DataBlock::SetMarginY(int low, int high) {
  if (high < 0) {
    high = size_y;
  }
  if ((low >= 0) && (high <= size_y)) {
    y_low = low;
    y_high = high;
    max = 0;
  }
}
                                    
void DataBlock::SetMarginZ(int low, int high) {
  if (high < 0) {
    high = size_z;
  }
  if ((low >= 0) && (high <= size_z)) {
    z_low = low;
    z_high = high;
    max = 0;
  }
}
                                    
void DataBlock::GetMarginX(int & low, int & high) {
  low = x_low;
  high = x_high;
}

void DataBlock::GetMarginY(int & low, int & high) {
  low = y_low;
  high = y_high;
}

void DataBlock::GetMarginZ(int & low, int & high) {
  low = z_low;
  high = z_high;
}

void DataBlock::Export(const char * filename) {
  ofstream out;
  out.open(filename);
  out << "#x\ty\tt\tvalue" << endl;

  for (int x = 0; x < GetX(); x++) {
    for (int y = 0; y < GetY(); y++) {
      for (int z = 0; z < GetZ(); z++) {
        out <<  x << "\t" << y << "\t" << z << "\t" << GetPoint(x, y, z) << endl;
      }
    }
  }
  out.close();
}

uushort DataBlock::GetMax() {
  if (max == 0) {
    for (int x = 0; x < GetX(); x++) {
      for (int y = 0; y < GetY(); y++) {
        for (int z = 0; z < GetZ(); z++) {
          if (GetPoint(x, y, z) > max) {
            max = GetPoint(x, y, z);
          }
        }
      }
    }
  }
  return max;
}
