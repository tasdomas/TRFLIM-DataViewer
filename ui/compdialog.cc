#include "compdialog.h"

BEGIN_EVENT_TABLE(CompDialog, wxDialog)
EVT_BUTTON(ID_CD_Yes, CompDialog::OnYes)
EVT_BUTTON(ID_CD_No, CompDialog::OnNo)
EVT_SPINCTRL(ID_CD_CompCount, CompDialog::OnSpin)
END_EVENT_TABLE()

CompDialog::CompDialog(wxWindow * parent, wxWindowID id)
: wxDialog(parent, id, _("Component analysis"),
           wxDefaultPosition, wxDefaultSize,
           wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

  sizer = new wxBoxSizer(wxVERTICAL);

  //sigma for the IRF
  wxStaticText * label = new wxStaticText(this, wxID_ANY,  _("IRF sigma:"));
  sizer->Add(label);
  sigma = new wxTextCtrl(this, wxID_ANY);
  sizer->Add(sigma);

  label = new wxStaticText(this, wxID_ANY,  _("Component count:"));
  sizer->Add(label);
  count = new wxSpinCtrl(this, ID_CD_CompCount, wxEmptyString, 
                         wxDefaultPosition, wxDefaultSize,
                         wxSP_ARROW_KEYS, 1, 6, 2);
  sizer->Add(count);
  
  label = new wxStaticText(this, wxID_ANY,  _("Component lifetimes:"));
  sizer->Add(label);

  for (int i = 0; i < 2; i++) {
    wxTextCtrl * text = new wxTextCtrl(this, wxID_ANY);
    lifetimes.push_back(text);
    sizer->Add(text);
  }

  wxButton * btnOk = new wxButton(this, ID_CD_Yes, _("Ok"));
  sizer->Add(btnOk);

  wxButton * btnCancel = new wxButton(this, ID_CD_No, _("Cancel"));
  sizer->Add(btnCancel);

  SetSizer(sizer);
  sizer->SetSizeHints(this);
  sizer->SetSizeHints(this);
  
}

CompDialog::~CompDialog() {
}

int CompDialog::GetCount() {
  return 0;
}

float CompDialog::GetSigma() {
  return 0.0;
}

vector<float> CompDialog::GetLifetimes() {

}

void CompDialog::OnYes(wxCommandEvent &) {
}

void CompDialog::OnNo(wxCommandEvent &) {
}

void CompDialog::OnSpin(wxSpinEvent& evt) {
  int count = lifetimes.size();
  int new_count = evt.GetPosition();

  if (count > new_count) {
    for (int i = count; i > new_count; i--) {
      wxTextCtrl * text = lifetimes[i - 1];
      lifetimes.pop_back();
      sizer->Remove(text);
      text->Destroy();
    }
  } else {
    for (int i = count; i < new_count; i++) {
      
      wxTextCtrl * text = new wxTextCtrl(this, wxID_ANY);
      lifetimes.push_back(text);
      sizer->Insert(4+i, text);
    }    
  }
  sizer->Layout();
  sizer->Fit(this);
}
                         
  


      

