#include "svdpanel.h"

BEGIN_EVENT_TABLE(SVDPanel, wxPanel) 

EVT_BUTTON(ID_SVD_COMP, SVDPanel::Compute)

END_EVENT_TABLE()


SVDPanel::SVDPanel(wxWindow * parent, wxWindowID id) 
  : wxPanel(parent, id, wxDefaultPosition),
    block(NULL) {

  wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);

  plot = new mpWindow(this, wxID_ANY);
  plot->SetMargins(0, 0, 100, 100);

  plot->LockAspect(false);

  sizer->Add(plot, 1.0, wxEXPAND);
  mpScaleX * scaleX = new mpScaleX(_("value"), mpALIGN_BORDER_BOTTOM, true);
  mpScaleY * scaleY = new mpScaleY(_("SV"), mpALIGN_BORDER_LEFT, true);
  plot->AddLayer(scaleX);
  plot->AddLayer(scaleY);

  svs = new mpFXYVector();
  svs->SetDrawOutsideMargins(false);
  svs->SetPen(wxPen(*wxRED, 2, wxSHORT_DASH));
  plot->AddLayer(svs);

  compute = new wxButton(this, ID_SVD_COMP, _("Compute"));
  sizer->Add(compute, 0, wxEXPAND);

  SetSizer(sizer);
  sizer->SetSizeHints(this);
}

SVDPanel::~SVDPanel() {
  if (block != NULL) {
    delete block;
  }
}

void SVDPanel::SetImage(DataBlock * image) {
  block = new SVDBlock(*image);
}

void SVDPanel::Compute(wxCommandEvent &) {
  if (block != NULL) {
    wxBeginBusyCursor();

    vector<float> y = block->GetSV();
    vector<float> x = block->GetXs();

    svs->SetData(x, y);
    svs->SetContinuity(false);
    plot->Fit();
    wxEndBusyCursor();
  }
}  
