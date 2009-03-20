#ifndef DV_DATA_PANEL_H
#define DV_DATA_PANEL_H

#include "wx/wx.h"
#include "wx/spinctrl.h"
#include "../fileformat/sdt.h"

class DataPanel : public wxPanel {
public:
  DataPanel(wxWindow * parent, wxWindowID id = wxID_ANY);
  ~DataPanel();
private:
  wxStaticText * fileName;
  wxSpinCtrl * blockNo;
  wxButton * setupBtn;

};


#endif
