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
  for (int i = 0; i < size_x*size_y; i++) {
    intensity[i] = 0;
    //each point
    for (int k = 0; k < original->GetZ(); k++) {
      intensity[i] += original->block[k][i];
    }
    if (intensity[i] > max) {
      max = intensity[i];
    }
  }
  for (int i = 0; i < size_x*size_y; i++) {
    block[0][i] = intensity[i]; // (ushort)(100*((float)intensity[i] / max));
  }
}

void FWHMBlock::CalculateFWHM() {
  ushort * vector = new ushort[original->GetZ()];

  int max = 0;
  int max_index = 0;

  for (int i = 0; i < size_x*size_y; i++) {
    block[1][i] = 0;
    for (int j = 0; j < original->GetZ(); j++) {
      vector[j] = original->block[j][i];
      if (vector[j] > max) {
        max = vector[j];
        max_index = j;
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
    block[1][i] = abs(round(right_ind - left_ind));
  }
}
          
        

    
