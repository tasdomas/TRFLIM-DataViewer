#ifndef DV_MARGIN_DIALOG
#define DV_MARGIN_DIALOG

#include "wx/wx.h"
#include "wx/spinctrl.h"

#include "../fileformat/datablock.h"
#include "enums.h"

class MarginsDialog : public wxDialog {
 public:
  MarginsDialog(wxWindow * parent, wxWindowID id, DataBlock * block);
  ~MarginsDialog();

  void OnYes(wxCommandEvent &);
  void OnNo(wxCommandEvent &);
  void OnReset(wxCommandEvent &);
  DECLARE_EVENT_TABLE()

 private:
  wxSpinCtrl * x_low;
  wxSpinCtrl * x_high;
  wxSpinCtrl * y_low;
  wxSpinCtrl * y_high;
  wxSpinCtrl * z_low;
  wxSpinCtrl * z_high;

  DataBlock * data;

};

  


#endif
