#include "datapanel.h"

enum {
  ID_BlockNo = 1,
  ID_SetupBtn,
};

DataPanel::DataPanel(wxWindow * parent, wxWindowID id)
  : wxPanel(parent, id),
    setupData("") {
  
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

  setupBtn = new wxButton(this, ID_SetupBtn, _("SetupData"));
  sizer->Add(setupBtn, 0, wxEXPAND);

  SetSizer(sizer);
}

DataPanel::~DataPanel() {
}

void DataPanel::UpdateData(string pFileName, int pBlockCount, string pSetupData) {
  // get only the filename
  int pos = pFileName.find_last_of("/\\");
  string name = pFileName;
  if (pos != string::npos) {
    name = pFileName.substr(pos+1);
  }

  fileName->SetLabel(wxString(name.c_str(), wxConvUTF8));
  blockNo->SetRange(0, pBlockCount);
  setupData = pSetupData;
}
