#include "imagepanel.h"
#include "enums.h"

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
  
