#include "componentblock.h"

ComponentBlock::ComponentBlock(DataBlock * data, float sigma, int count, vector<float> & tau)
  : DataBlock(data->GetX(), data->GetY(), count),
    original(data), lifetimes(tau), sigma_t(sigma), components(count),
    IRF(NULL), D(NULL) {

  ConstructIRF();
}

ComponentBlock::~ComponentBlock() {
  if (IRF != NULL) {
    delete IRF;
  }

  if (D != NULL) {
    delete D;
  }
}

void ComponentBlock::ConstructIRF() {
  IRF = new Matrix(components, components);
  for (int i = 0; i < components; i++) {
    for (int j = 0; j < components; j++) {
      if (i == j) {
        IRF->element(i, j) = 0.5 + (1 + erf((float)i / sigma_t));
      } else {
        IRF->element(i, j) = 0.0;
      }
    }
  }
}

void ComponentBlock::LinearizeData() {
  D = new Matrix(original->GetZ(), original->GetX() * original->GetY());
  for (int z = 0; z < original->GetZ(); z++) {
    for (int y = 0; y < original->GetY(); y++) {
      for (int x = 0; x < original->GetX(); x++) {
        D->element(z,y*original->GetX() + x) = original->GetPoint(x, y, z);
      }
    }
  }
}
