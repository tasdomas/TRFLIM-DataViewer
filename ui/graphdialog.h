#ifndef DV_GRAPH_DIALOG
#define DV_GRAPH_DIALOG

#include "wx/wx.h"
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

};
#endif
