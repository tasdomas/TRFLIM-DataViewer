#include "componentblock.h"

ComponentBlock::ComponentBlock(DataBlock * data, float sigma, int count, vector<float> & tau)
  : DataBlock(data->GetX(), data->GetY(), count),
    original(data), lifetimes(tau), sigma_t(sigma), components(count),
    IRF(NULL) {

  ConstructIRF();
}

ComponentBlock::~ComponentBlock() {
  if (IRF != NULL) {
    delete IRF;
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
