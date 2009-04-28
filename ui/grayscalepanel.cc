#include "imagepanel.h"
#include "enums.h"

DEFINE_EVENT_TYPE(POINT_EVT);
IMPLEMENT_DYNAMIC_CLASS( PointEvent, wxCommandEvent )

PointEvent::PointEvent(WXTYPE commandEventType, int id, int px, int py) 
  : wxCommandEvent(commandEventType, id) {
  x = px;
  y = py;
}

int PointEvent::GetX() {
  return x;
}

int PointEvent::GetY() {
  return y;
}

PointEvent* PointEvent::Clone() { 
  return new PointEvent(*this); 
}

BEGIN_EVENT_TABLE(GrayScalePanel, ImagePanel)
EVT_COMMAND_SCROLL(ID_Slide, GrayScalePanel::OnSlide)
EVT_POINT_EVENT(GrayScalePanel::OnCtrlClick)
END_EVENT_TABLE()

GrayScalePanel::GrayScalePanel(wxWindow * parent, wxWindowID id, 
                               bool multiImage, bool clickPlot) 
: ImagePanel(parent, id), multi(multiImage), clickPlotting(clickPlot) {
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

void GrayScalePanel::OnCtrlClick(PointEvent & evt) {
  if ((clickPlotting) && (block != NULL)) {
    GraphDialog * dia = new GraphDialog(this, wxID_ANY);
    
    dia->SetGraph(block->GetTime(), block->GetPoint(evt.GetX(), evt.GetY()));
    dia->Show();
  }
    
}
