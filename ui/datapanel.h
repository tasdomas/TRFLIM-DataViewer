#ifndef DV_DATA_PANEL_H
#define DV_DATA_PANEL_H

#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "../fileformat/sdt.h"

#include "marginsdialog.h"

class DataPanel : public wxPanel {
public:
  DataPanel(wxWindow * parent, wxWindowID id = wxID_ANY);
  ~DataPanel();
  
  void UpdateData(string pFileName, int pBlockCount, string pSetupData);

  DECLARE_EVENT_TABLE()

private:
  wxStaticText * fileName;
  wxChoice * blockNo;
  wxTextCtrl * setupCtrl;

};


#endif
