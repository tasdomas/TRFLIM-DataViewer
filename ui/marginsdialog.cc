#include "marginsdialog.h"

BEGIN_EVENT_TABLE(MarginsDialog, wxDialog)
EVT_BUTTON(ID_MD_Yes, MarginsDialog::OnYes)
EVT_BUTTON(ID_MD_No, MarginsDialog::OnNo)
EVT_BUTTON(ID_MD_Reset, MarginsDialog::OnReset)
END_EVENT_TABLE()


MarginsDialog::MarginsDialog(wxWindow * parent, wxWindowID id, DataBlock * block) 
: wxDialog(parent, id, _("Data margins"),
           wxDefaultPosition, wxDefaultSize,
           wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER) {

  data = block;

  wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);

  int lo, hi;

  block->GetMarginX(lo, hi);
  wxBoxSizer * row = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText * text = new wxStaticText(this, wxID_ANY, _("X min:"));
  row->Add(text);
  x_low = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                         wxDefaultPosition, wxDefaultSize,
                         wxSP_ARROW_KEYS, 0, block->GetX(), lo);
  row->Add(x_low);
  sizer->Add(row);

  row = new wxBoxSizer(wxHORIZONTAL);
  text = new wxStaticText(this, wxID_ANY, _("X max:"));
  row->Add(text);
  x_high = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                         wxDefaultPosition, wxDefaultSize,
                          wxSP_ARROW_KEYS, 0, block->GetX(), hi);
  row->Add(x_high);
  sizer->Add(row);

  block->GetMarginY(lo, hi);
  row = new wxBoxSizer(wxHORIZONTAL);
  text = new wxStaticText(this, wxID_ANY, _("Y min:"));
  row->Add(text);
  y_low = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                         wxDefaultPosition, wxDefaultSize,
                         wxSP_ARROW_KEYS, 0, block->GetY(), lo);
  row->Add(y_low);
  sizer->Add(row);

  row = new wxBoxSizer(wxHORIZONTAL);
  text = new wxStaticText(this, wxID_ANY, _("Y max:"));
  row->Add(text);
  y_high = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                         wxDefaultPosition, wxDefaultSize,
                          wxSP_ARROW_KEYS, 0, block->GetY(), hi);
  row->Add(y_high);
  sizer->Add(row);

  block->GetMarginZ(lo, hi);
  row = new wxBoxSizer(wxHORIZONTAL);
  text = new wxStaticText(this, wxID_ANY, _("T min:"));
  row->Add(text);
  z_low = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                         wxDefaultPosition, wxDefaultSize,
                         wxSP_ARROW_KEYS, 0, block->GetZ(), lo);
  row->Add(z_low);
  sizer->Add(row);

  row = new wxBoxSizer(wxHORIZONTAL);
  text = new wxStaticText(this, wxID_ANY, _("T max:"));
  row->Add(text);
  z_high = new wxSpinCtrl(this, wxID_ANY, wxEmptyString,
                         wxDefaultPosition, wxDefaultSize,
                          wxSP_ARROW_KEYS, 0, block->GetZ(), hi);
  row->Add(z_high);
  sizer->Add(row);

  wxButton * ok = new wxButton(this, ID_MD_Yes, _("Ok"));
  sizer->Add(ok);

  wxButton * no = new wxButton(this, ID_MD_No, _("Cancel"));
  sizer->Add(no);

  wxButton * reset = new wxButton(this, ID_MD_Reset, _("Reset"));
  sizer->Add(reset);
  
  SetSizer(sizer);
}

MarginsDialog::~MarginsDialog() {
}

void MarginsDialog::OnYes(wxCommandEvent &) {
  int lo, hi;

  lo = x_low->GetValue();
  hi = x_high->GetValue();
  data->SetMarginX(lo, hi);

  lo = y_low->GetValue();
  hi = y_high->GetValue();
  data->SetMarginY(lo, hi);

  lo = z_low->GetValue();
  hi = z_high->GetValue();
  data->SetMarginZ(lo, hi);
  
  EndModal(true);
}

void MarginsDialog::OnNo(wxCommandEvent &) {
  EndModal(false);
}

void MarginsDialog::OnReset(wxCommandEvent &) {
  data->ResetMargins();
  EndModal(true);
}
