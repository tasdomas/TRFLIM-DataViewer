#ifndef DV_GRAPH_DIALOG
#define DV_GRAPH_DIALOG

#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "../include/wxMathPlot/mathplot.h"

#include <vector>

#include "enums.h"

using namespace std;

class GraphDialog : public wxDialog {
 public:
  GraphDialog(wxWindow * parent, wxWindowID id);
  ~GraphDialog();

  void SetGraph(vector<float> x, vector<float> y);
 private:
  mpWindow * plot;
  mpFXYVector * data;
  wxTextCtrl * output;
  wxButton * btnFit;
  wxButton * btnSave;
  wxButton * btnExport;
  wxSpinCtrl * compCount;

};
#endif
