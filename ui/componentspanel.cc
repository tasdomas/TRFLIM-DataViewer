#include "imagepanel.h"
#include "enums.h"

BEGIN_EVENT_TABLE(ComponentsPanel, ImagePanel)
EVT_BUTTON(ID_ComputeComponents, ComponentsPanel::Compute)
EVT_SPINCTRL(ID_ComponentNo, ComponentsPanel::ChangeComponent)
END_EVENT_TABLE()

ComponentsPanel::ComponentsPanel(wxWindow * parent, wxWindowID id) 
  : ImagePanel(parent, id) {
  
  wxBoxSizer * ctrlSizer = new wxBoxSizer(wxHORIZONTAL);
  btnCompute = new wxButton(this, ID_ComputeComponents, _("Compute"));
  ctrlSizer->Add(btnCompute, 0);
  
  compNo = new wxSpinCtrl(this, ID_ComponentNo);
  ctrlSizer->Add(compNo, 0);
  
  sizerLeft->Add(ctrlSizer, 0.1, wxEXPAND);
}

ComponentsPanel::~ComponentsPanel() {
}

void ComponentsPanel::SetImage(DataBlock * image) {
  block = new ComponentBlock(image);
}

void ComponentsPanel::Compute(wxCommandEvent &) {
  if (block != NULL) {
    CompDialog * parameters = new CompDialog(this, wxID_ANY);
    if (parameters->ShowModal()) {
      vector<float> lifetimes = parameters->GetLifetimes();
      float sigma = parameters->GetSigma();
      int count = parameters->GetCount();

      ((ComponentBlock*)block)->Compute(sigma, count, lifetimes);
      canvas->SetImage(block->GetImage(0), block->GetX(), block->GetY());
      canvas->Zoom(zoom);
      canvas->Refresh();

      compNo->SetRange(1, count);
      compNo->SetValue(1);
    }
    parameters->Destroy();

  } else {
    wxMessageBox(_("Load the data file first"));
  }
}

void ComponentsPanel::ChangeComponent(wxSpinEvent & evt) {
  canvas->SetImage(block->GetImage(evt.GetPosition()-1), block->GetX(), block->GetY());
  canvas->Zoom(zoom);
  canvas->Refresh();

}
