#ifndef DV_COMP_DIALOG

#define DV_COMP_DIALOG

#include "wx/wx.h"

class CompDialog : public wxDialog {
 public:
  CompDialog();
  ~CompDialog();

  int GetCount();
  float GetSigma();
  vector<float> GetLifetimes();
}

#endif
