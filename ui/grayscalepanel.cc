#include "imagepanel.h"
#include "enums.h"

BEGIN_EVENT_TABLE(GrayScalePanel, ImagePanel)
EVT_COMMAND_SCROLL(ID_Slide, GrayScalePanel::OnSlide)
END_EVENT_TABLE()

GrayScalePanel::GrayScalePanel(wxWindow * parent, wxWindowID id, bool multiImage) 
: ImagePanel(parent, id), multi(multiImage) {
  if (multiImage) {
    wxBoxSizer * scrollSizer = new wxBoxSizer(wxHORIZONTAL);
    scroller = new wxScrollBar(this, ID_Slide);
    scrollSizer->Add(scroller, 1);
    index = new wxStaticText(this, wxID_ANY, _("0/0"));
    scrollSizer->Add(index, 0.1);
    sizerLeft->Add(scrollSizer, 0.1, wxEXPAND);
  }
}

GrayScalePanel::~GrayScalePanel() {
}

void GrayScalePanel::OnSlide(wxScrollEvent & evt) {
  if (block != NULL) {
    int pos = evt.GetPosition();

    index->SetLabel(wxString::Format(_("%e/%e"), 
                                     (float)pos*block->GetTimeScale(), 
                                     (float)block->GetZ()*block->GetTimeScale()));

    canvas->SetImage(block->GetImage(pos), block->GetX(), block->GetY());
    canvas->Zoom(zoom);
    canvas->Refresh();
    
    
  }
}

void GrayScalePanel::SetImage(DataBlock * image) {
  block = image;
  
  if (multi) {
    scroller->SetScrollbar(0, 1, image->GetZ() - 1, 1);
    index->SetLabel(wxString::Format(_("%e/%e"), 0.0, (float)block->GetZ()*block->GetTimeScale()));

    canvas->SetImage(block->GetImage(0), block->GetX(), block->GetY());
    canvas->Zoom(zoom);

  } else {
    canvas->SetImage(block);
    canvas->Zoom(zoom);
  }
  
}
