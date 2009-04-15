#include "componentblock.h"

ComponentBlock::ComponentBlock(DataBlock * data)
  : DataBlock(data->GetX(), data->GetY(), 1),
    original(data), IRF(NULL), D(NULL) {


}

void ComponentBlock::Compute(float sigma, int count, vector<float> & tau) {
  lifetimes = tau;
  sigma_t = sigma;
  components = count;

  ConstructIRF();
  LinearizeData();
  RemoveIRF();
}


ComponentBlock::~ComponentBlock() {
  if (IRF != NULL) {
    delete IRF;
  }

  if (D != NULL) {
    delete D;
  }

  if (E != NULL) {
    delete E;
  }
}

void ComponentBlock::ConstructIRF() {
  int time = original->GetZ();
  IRF = new Matrix(time, time);
  for (int i = 0; i < time; i++) {
    for (int j = 0; j < time; j++) {
      if (i == j) {
        float value = 0.5 + (1 + erf((float)i / sigma_t));
        IRF->element(i, j) = 1/value;
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

void ComponentBlock::RemoveIRF() {
  if ((IRF != NULL) && (D != NULL)) {
    *D = *IRF * *D;
  }
}

void ComponentBlock::CreateExponential() {
  if (E != NULL) {
    delete E;
  }
  E = new Matrix(original->GetZ(), components);

  for (int time = 0; time < original->GetZ(); time++) {
    for (int comp = 0; comp < components; comp++) {
      E->element(time, comp) = exp(- (float) time / lifetimes[comp]);
    }
  }
  *E = E->i();
}
