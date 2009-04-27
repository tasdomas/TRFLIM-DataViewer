#include "compdialog.h"

BEGIN_EVENT_TABLE(CompDialog, wxDialog)
EVT_BUTTON(ID_CD_Yes, CompDialog::OnYes)
EVT_BUTTON(ID_CD_No, CompDialog::OnNo)
EVT_SPINCTRL(ID_CD_CompCount, CompDialog::OnSpin)
END_EVENT_TABLE()

CompDialog::CompDialog(wxWindow * parent, wxWindowID id)
: wxDialog(parent, id, _("Component analysis"),
           wxDefaultPosition, wxDefaultSize,
           wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
  status(false) {

  sizer = new wxBoxSizer(wxVERTICAL);

  //sigma for the IRF
  wxStaticText * label = new wxStaticText(this, wxID_ANY,  _("IRF sigma (ns):"));
  sizer->Add(label);
  sigma = new wxTextCtrl(this, wxID_ANY);
  sizer->Add(sigma);

  label = new wxStaticText(this, wxID_ANY,  _("Component count:"));
  sizer->Add(label);
  count = new wxSpinCtrl(this, ID_CD_CompCount, wxEmptyString, 
                         wxDefaultPosition, wxDefaultSize,
                         wxSP_ARROW_KEYS, 1, 6, 2);
  sizer->Add(count);
  
  label = new wxStaticText(this, wxID_ANY,  _("Component lifetimes (ns):"));
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

  msg = new wxStaticText(this, wxID_ANY, wxEmptyString);
  msg->SetForegroundColour(*wxRED);
  sizer->Add(msg);

  SetSizer(sizer);
  sizer->SetSizeHints(this);
  sizer->SetSizeHints(this);
  
}

CompDialog::~CompDialog() {
}

int CompDialog::GetCount() {
  return lifetimes.size();
}

float CompDialog::GetSigma() {
  double val;
  if ((sigma->GetValue()).ToDouble(&val)) {
    return val;
  } else {
    return 0.0;
  }
}

vector<float> CompDialog::GetLifetimes() {
  vector<float> ret;
  for (int i = 0; i < lifetimes.size(); i++) {
    double val;
    if ((lifetimes[i]->GetValue()).ToDouble(&val)) {
      ret.push_back(val);
    } else {
      ret.push_back(0.0);
    }
  }
  return ret;
}

void CompDialog::OnYes(wxCommandEvent &) {
  bool ok = true;
  wxString message = wxEmptyString;
  double temp;
  if (! (sigma->GetValue()).ToDouble(&temp)) {
    message += _("Sigma must be a valid number.\n");
    ok = false;
  }
  for (int i = 0; i < lifetimes.size(); i++) {
    if (! ((lifetimes[i])->GetValue()).ToDouble(&temp)) {
      message +=  wxString::Format(_("Lifetime %d must be a valid number.\n"), i+1);
      ok = false;
    }
  }
  msg->SetLabel(message);
  sizer->Layout();
  sizer->Fit(this);
  if (ok) {
    EndModal(true);
  }
}

void CompDialog::OnNo(wxCommandEvent &) {
  EndModal(false);
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
                         
  


      

