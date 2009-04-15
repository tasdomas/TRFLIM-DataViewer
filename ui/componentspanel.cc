#include "imagepanel.h"
#include "enums.h"

BEGIN_EVENT_TABLE(ComponentsPanel, ImagePanel)
EVT_BUTTON(ID_ComputeComponents, ComponentsPanel::Compute)
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

void ComponentsPanel::SetImage(ComponentBlock * image) {
}

void ComponentsPanel::Compute(wxCommandEvent &) {
  CompDialog * parameters = new CompDialog(this, wxID_ANY);
  parameters->ShowModal();
  parameters->Destroy();
}
