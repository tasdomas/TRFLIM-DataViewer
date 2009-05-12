#include "fitter.h"

Fitter::Fitter(vector<float> dx, vector<float> dy) {
  if (dx.size() == dy.size()) {
    size = dx.size();
    x = new double[size];
    y = new double[size];

    for (int i = 0; i < size; i++) {
      x[i] = dx[i];
      y[i] = dy[i];
    }
  }
}

Fitter::~Fitter() {
  delete [] x;
  delete [] y;
}

void Fitter::SetComponentCount(int count) {
  compCount = count;

  components = new double[2*count];
  for (int i = 0; i < 2*count; i++) {
    components[i] = 1.0;
  }
}

bool Fitter::Fit() {
  lm_control_type control;
  lm_data_type data;

  Function((double)compCount, NULL);

  lm_initialize_control(&control);

  data.user_func = Function;
  data.user_t = this->x;
  data.user_y = this->y;

  lm_minimize(this->size, 2*this->compCount, this->components, 
              lm_evaluate_default, lm_print_default,
              &data, &control);

  return true;
}

vector<double> Fitter::GetParameters() {
  vector<double> param;
  for (int i = 0; i < 2*compCount; i++) {
    param.push_back(components[i]);
  }
  return param;
}

vector<float> Fitter::GetFitted() {
  vector<float> plot;
  for (int i = 0; i < size; i++) {
    plot.push_back((float)Function(x[i], this->components));
  }
  return plot;
}

vector<float> Fitter::GetTime() {
  vector<float> time;
  for (int i = 0; i < size; i++) {
    time.push_back((float)x[i]);
  }
  return time;
}

double Fitter::Chi() {
  double chi = 0.0;
  for (int i = 0; i < size; i++) {
    double diff = (y[i] - Function(x[i], components));
    diff *= diff;
    chi += diff;
  }
  return chi;
}

double Function(double x, double * p) {
  static int count = 0;
  if (p == NULL) {
    count = round(x);
    return 0.0;
  } else {
    
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
      sum += p[2*i] * exp(x / -p[2*i + 1]);
    }
    return sum;
  }
}
    
