#ifndef DV_GRAPH_DIALOG
#define DV_GRAPH_DIALOG

#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "../lib/fitter.h"
#include "../include/wxMathPlot/mathplot.h"

#include <vector>
#include <iostream>
#include <fstream>

#include "enums.h"

using namespace std;

class GraphDialog : public wxDialog {
 public:
  GraphDialog(wxWindow * parent, wxWindowID id);
  ~GraphDialog();

  void OnFit(wxCommandEvent &);
  void OnSave(wxCommandEvent &);
  void OnExport(wxCommandEvent &);

  void SetGraph(vector<float> x, vector<float> y);

  DECLARE_EVENT_TABLE()
 private:

  mpWindow * plot;
  mpFXYVector * data;
  mpFXYVector * fit;
  wxTextCtrl * output;
  wxButton * btnFit;
  wxButton * btnSave;
  wxButton * btnExport;
  wxSpinCtrl * compCount;
  Fitter * fitter;

  vector<float> data_x;
  vector<float> data_y;
};
#endif
