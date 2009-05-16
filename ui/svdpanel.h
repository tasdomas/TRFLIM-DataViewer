#ifndef DV_SVD_PANEL

#define DV_SVD_PANEL

#include "wx/wx.h"
#include "../include/wxMathPlot/mathplot.h"
#include "../lib/svdblock.h"
#include "enums.h"

class SVDPanel : public wxPanel {
 public:
  SVDPanel(wxWindow * parent, wxWindowID id = wxID_ANY);
  ~SVDPanel();

  void SetImage(DataBlock * image);
  void Compute(wxCommandEvent &);
  DECLARE_EVENT_TABLE()
 protected:
  SVDBlock * block;

  wxButton * compute;
  
  mpWindow * plot;
  mpFXYVector * svs;
};

#endif
