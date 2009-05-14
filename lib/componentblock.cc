#include "componentblock.h"

ComponentBlock::ComponentBlock(DataBlock * data)
  : DataBlock(data->GetX(), data->GetY(), 1),
    original(data), IRF(NULL), D(NULL), E(NULL), C(NULL) {

  time_step = data->GetTimeScale();


}

void ComponentBlock::Compute(float sigma, int count, vector<float> & tau) {
  lifetimes = tau;
  sigma_t = sigma;
  components = count;
  size_z = components;
  ResetMargins();

  LinearizeData();
  if (sigma != 0.0) {
    ConstructIRF();
    RemoveIRF();
  }
  //cout << setw(10) << setprecision(3) << *D << endl;

  CreateExponential();

  //cout << setw(10) << setprecision(3) << *E << endl;

  InvertExponential();
  GetComponents();
  NoNegativeValues();
  //cout << setw(10) << setprecision(3) << *C << endl;
  DelinearizeData();
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

  if (C != NULL) {
    delete C;
  }
}

void ComponentBlock::ConstructIRF() {
  int time = original->GetZ();
  vector<float> t = original->GetTime(false);

  IRF = new Matrix(time, time);
  for (int i = 0; i < time; i++) {
    for (int j = 0; j < time; j++) {
      if (i == j) {
        float value = 0.5 + (1 + erf((t[i]) / sigma_t));
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
  vector<float> t = original->GetTime(false);
  E = new Matrix(original->GetZ(), components);

  for (int time = 0; time < original->GetZ(); time++) {
    for (int comp = 0; comp < components; comp++) {
      E->element(time, comp) = exp(- (t[time]) / lifetimes[comp]);
    }
  }

  
  //*E = E->i();
}


void ComponentBlock::InvertExponential() {
  if (E != NULL) {
    Matrix U, V;
    DiagonalMatrix S;
    SVD(*E, S, U, V, false);
    for (int i = 0; i < S.nrows(); i++) {
      if (S.element(i,i) != 0) {
        S.element(i,i) = 1 / S.element(i,i);
      }
    }
    *E = V * S * U.t();
  }
}

void ComponentBlock::GetComponents() {
  if ((E != NULL) && (D != NULL)) {
    C = new Matrix();
    *C = *E * *D;

  }
}

void ComponentBlock::NoNegativeValues() {
  if (C != NULL) {
    double neg = 0.0;
    double max = 0.0;
    for (int i = 0; i < components; i++) {
      for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
          double t = C->element(i, x + y * size_x);
          if (C->element(i, x + y * size_x) < neg) {
            neg = C->element(i, x + y * size_x);
            C->element(i, x + y * size_x) = 0;
          }
          if (C->element(i, x + y * size_x) > max) {
            max = C->element(i, x + y * size_x);
          }

        }
      }
    }

    if (max == 0.0) {
      max = 1.0;
    }
    //max = max - neg;

    if (neg != 0.0) {
      for (int i = 0; i < components; i++) {
        for (int y = 0; y < size_y; y++) {
          for (int x = 0; x < size_x; x++) {
            double val = C->element(i, x + y * size_x);
            val = ((val) / max) * 60000;
            C->element(i, x + y * size_x) = val;
          }
        }
      }
    }
  }
}
    
  
void ComponentBlock::DelinearizeData() {

  if (C != NULL) {
    delete [] block;
    block = new uushort*[components];
    /*
    double max = 0.0;
    for (int i = 0; i < components; i++) {
      for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
          double t = C->element(i, x + y * size_x);
          if (C->element(i, x + y * size_x) > max) {
            max = C->element(i, x + y * size_x);
          }

        }
      }
    }
    */
    size_x = original->GetX();
    size_y = original->GetY();
    size_z = components;
    for (int i = 0; i < components; i++) {
      block[i] = new uushort[size_x*size_y];
      for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
          double val = C->element(i, x + y * size_x);
          block[i][x + y * size_x] = (unsigned short)floor(val);
          //cout << i << " " << (unsigned short)floor(val) << "\n";
        }
      }
    }
  }
}
      
