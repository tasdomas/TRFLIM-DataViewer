#ifndef DV_COMP_DIALOG

#define DV_COMP_DIALOG

#include "wx/wx.h"
#include <vector>
#include "wx/spinctrl.h"

#include "enums.h"

using namespace std;

class CompDialog : public wxDialog {
 public:
  CompDialog(wxWindow * parent, wxWindowID id);
  ~CompDialog();

  void OnYes(wxCommandEvent &);
  void OnNo(wxCommandEvent &);
  void OnSpin(wxSpinEvent& evt);


  int GetCount();
  float GetSigma();
  vector<float> GetLifetimes();

  DECLARE_EVENT_TABLE()
 private:
  wxBoxSizer * sizer;
  wxTextCtrl * sigma;
  vector<wxTextCtrl *> lifetimes;
  wxSpinCtrl * count;
};

#endif
