#include "datapanel.h"
#include "enums.h"
BEGIN_EVENT_TABLE(DataPanel, wxPanel)

END_EVENT_TABLE()

DataPanel::DataPanel(wxWindow * parent, wxWindowID id)
  : wxPanel(parent, id) {
  
  wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
  
  wxStaticText * text = new wxStaticText(this, wxID_ANY, _("File"));
  sizer->Add(text, 0, wxEXPAND);
  
  fileName = new wxStaticText(this, wxID_ANY, _(""));
  sizer->Add(fileName, 0, wxEXPAND);
  
  text = new wxStaticText(this, wxID_ANY, _("Block:"));
  sizer->Add(text, 0, wxEXPAND);

  blockNo = new wxSpinCtrl(this, ID_BlockNo, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                           wxSP_VERTICAL | wxSP_WRAP, 0, 0);
  sizer->Add(blockNo, 0, wxEXPAND);

  setupCtrl = new wxTextCtrl(this, ID_SetupBtn, _(""), 
                             wxDefaultPosition, wxDefaultSize,
                             wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL | wxTE_DONTWRAP);
  sizer->Add(setupCtrl, 1, wxEXPAND);

  SetSizer(sizer);
}

DataPanel::~DataPanel() {
}

void DataPanel::UpdateData(string pFileName, int pBlockCount, string pSetupData) {
  // get only the filename
  unsigned int pos = pFileName.find_last_of("/\\");
  string name = pFileName;
  if (pos != string::npos) {
    name = pFileName.substr(pos+1);
  }

  fileName->SetLabel(wxString(name.c_str(), wxConvUTF8));
  blockNo->SetRange(0, pBlockCount);
  setupCtrl->SetValue(wxString(pSetupData.c_str(), wxConvUTF8));
}
