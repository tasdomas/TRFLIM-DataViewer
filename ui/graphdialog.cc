#include "graphdialog.h"

BEGIN_EVENT_TABLE(GraphDialog, wxDialog)
EVT_BUTTON(ID_GD_Fit, GraphDialog::OnFit)
END_EVENT_TABLE()



GraphDialog::GraphDialog(wxWindow * parent, wxWindowID id) 
  : wxDialog(parent, id, _("Point plot"),
             wxDefaultPosition, wxSize(400, 200),
             wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    data(NULL), fitter(NULL) {

  wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);

  plot = new mpWindow(this, -1);
  plot->SetMargins(0,0,100,100);

  plot->LockAspect(false);

  sizer->Add(plot, 2.0, wxEXPAND);
  mpScaleX * scaleX = new mpScaleX(_("time (ns)"), mpALIGN_BORDER_BOTTOM, true);
  mpScaleY * scaleY = new mpScaleY(_("photon count"), mpALIGN_BORDER_LEFT, true);
  plot->AddLayer(scaleX);
  plot->AddLayer(scaleY);

  data = new mpFXYVector();
  data->SetDrawOutsideMargins(false);
  plot->AddLayer(data);

  wxBoxSizer * right = new wxBoxSizer(wxVERTICAL);
  btnSave = new wxButton(this, ID_GD_Save, _("Save"));
  right->Add(btnSave, 0, wxEXPAND);

  btnExport = new wxButton(this, ID_GD_Export, _("Export"));
  right->Add(btnExport, 0, wxEXPAND);


  compCount = new wxSpinCtrl(this, ID_GD_Count, wxEmptyString, 
                             wxDefaultPosition, wxDefaultSize, 
                             wxSP_ARROW_KEYS, 1, 9, 1);
  right->Add(compCount, 0, wxEXPAND);
  
  btnFit = new wxButton(this, ID_GD_Fit, _("Fit"));
  right->Add(btnFit, 0, wxEXPAND);

  output = new wxTextCtrl(this, wxID_ANY, wxEmptyString, 
                          wxDefaultPosition, wxDefaultSize,
                          wxTE_MULTILINE | wxTE_READONLY);
  right->Add(output, 1, wxEXPAND);

  sizer->Add(right, 1.0, wxEXPAND);

  SetSizer(sizer);
}

GraphDialog::~GraphDialog() {
  if (fitter != NULL) {
    delete fitter;
  }
}

void GraphDialog::SetGraph(vector<float> x, vector<float> y) {

  fitter = new Fitter(x, y);


  data->SetData(x, y);
  data->SetDrawOutsideMargins(false);
  data->SetContinuity(true);
  plot->Fit();
}

void GraphDialog::OnFit(wxCommandEvent &) {
  if (fitter != NULL) {
    fitter->SetComponentCount(compCount->GetValue());
    fitter->Fit();

    vector<double> params = fitter->GetParameters();
    output->Clear();

    for (int i=0; i < params.size(); i++) {
      wxString t;
      if (i % 2 == 0) {
        t = wxString::Format(_("A(%d) = %f \n"), i, params[i]);
      } else {
        t = wxString::Format(_("T(%d) = %f \n"), i, params[i]);        
      }
      output->AppendText(t);
    }
  }
}
