#include "graphdialog.h"


GraphDialog::GraphDialog(wxWindow * parent, wxWindowID id) 
  : wxDialog(parent, id, _("Point plot"),
             wxDefaultPosition, wxSize(400, 200),
             wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
    data(NULL) {

  wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);

  plot = new mpWindow(this, -1);
  plot->SetMargins(0,0,100,100);

  plot->LockAspect(false);

  sizer->Add(plot, 1, wxEXPAND);
  mpScaleX * scaleX = new mpScaleX(_("time (ns)"), mpALIGN_BORDER_BOTTOM, true);
  mpScaleY * scaleY = new mpScaleY(_("photon count"), mpALIGN_BORDER_LEFT, true);
  plot->AddLayer(scaleX);
  plot->AddLayer(scaleY);

  data = new mpFXYVector();
  data->SetDrawOutsideMargins(false);
  plot->AddLayer(data);

  SetSizer(sizer);
}

GraphDialog::~GraphDialog() {
}

void GraphDialog::SetGraph(vector<float> x, vector<float> y) {
  data->SetData(x, y);
  data->SetDrawOutsideMargins(false);
  data->SetContinuity(true);
  plot->Fit();
}
