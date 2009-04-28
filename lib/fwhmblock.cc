#include "fwhmblock.h"

FWHMBlock::FWHMBlock(DataBlock * data)
  : DataBlock(data->GetX(), data->GetY(), 3) {
  original = data;
  for (int i = 0; i < size_x*size_y; i++) {
    for (int j = 0; j < 3; j++) {
      block[j][i] = 0;
    }
  }

  CalculateFWHM();
  CalculateIntensity();
}

void FWHMBlock::CalculateIntensity() {
  long * intensity = new long[size_x*size_y];
  long max = 0;
  for (int x = x_low; x < x_high; x++) {
    for (int y = y_low; y < y_high; y++) {
      int i = x + y*GetX();
      intensity[i] = 0;
      //each point
      for (int z = 0; z < original->GetZ(); z++) {
        intensity[i] += original->GetPoint(x, y, z);
      }
      if (intensity[i] > max) {
        max = intensity[i];
      }
    }
  }
  for (int i = 0; i < size_x*size_y; i++) {
    block[0][i] = intensity[i]; // (ushort)(100*((float)intensity[i] / max));
  }
}

void FWHMBlock::CalculateFWHM() {
  uushort * vector = new uushort[original->GetZ()];

  int max = 0;
  int max_index = 0;

  for (int x = x_low; x < x_high; x++) {
    for (int y = y_low; y < y_high; y++) {
      int i = x + y*GetX();      
      block[1][i] = 0;
      for (int z = 0; z < original->GetZ(); z++) {
        vector[z] = original->GetPoint(x, y, z);
        if (vector[z] > max) {
          max = vector[z];
          max_index = z;
        }
      }
    

      int j = 0;
      float left_ind;
      float right_ind;
      bool found_left = false;
      bool found_right = false;
    
      float half = (float)max / 2;

      while( ((max_index - j >= 0) || (max_index + j < original->GetZ())) &&
             !(found_left && found_right)) {
        //check left side
        int index = max_index - j;
        if ((index >= 0) && !found_left) {
          if (vector[index] < half) {
            left_ind = index - (half - vector[index]) / (vector[index + 1] - vector[index]);
            found_left = true;
          } else {
            left_ind = index;
          }
        }
      
        //check the right side
        index = max_index + j;
        if ((index < original->GetZ()) && !found_right) {
          if (vector[index] < half) {
            right_ind = index - (half - vector[index]) / (vector[index - 1] - vector[index]);
            found_right = true;
          } else {
            right_ind = index;
          }
        }
        j++;
      }
      block[1][i] = std::abs(lround(right_ind - left_ind));
    }
  }
}
          
        

    
