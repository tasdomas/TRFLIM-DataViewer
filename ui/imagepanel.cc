#include "imagepanel.h"

enum {
  ID_ZoomIn = 1,
  ID_ZoomOut,
  ID_SaveImage,
  ID_Slide
};

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)

EVT_COMMAND_SCROLL(ID_Slide, ImagePanel::OnSlide)
EVT_BUTTON(ID_ZoomIn, ImagePanel::ZoomIn)
EVT_BUTTON(ID_ZoomOut, ImagePanel::ZoomOut)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxWindow * parent, wxWindowID id, bool multiImage) 
: wxPanel(parent, id, wxDefaultPosition),
  block(NULL), zoom(1.0) {

  wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer * sizerLeft = new wxBoxSizer(wxVERTICAL);

  canvas = new DVCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
  sizerLeft->Add(canvas, 1, wxEXPAND);

  if (multiImage) {
    scroller = new wxScrollBar(this, ID_Slide);
    sizerLeft->Add(scroller, 0.1, wxEXPAND);
  }

  sizer->Add(sizerLeft, 1, wxEXPAND);
  
  wxBoxSizer * sizerRight = new wxBoxSizer(wxVERTICAL);
  
  wxButton * btn = new wxButton(this, ID_ZoomIn, _("+"));
  sizerRight->Add(btn, 0);

  btn = new wxButton(this, ID_ZoomOut, _("-"));
  sizerRight->Add(btn, 0);

  btn = new wxButton(this, ID_SaveImage, _("Save"));
  sizerRight->Add(btn, 0);

  sizer->Add(sizerRight, 0);
  
  SetSizer(sizer);
  sizer->SetSizeHints(this);
}

ImagePanel::~ImagePanel() {
}

void ImagePanel::SetImage(DataBlock * image) {
  block = image;

  scroller->SetScrollbar(0, 1, image->GetZ() - 1, 1);

  canvas->SetImage(block->GetImage(0), block->GetX(), block->GetY());
  canvas->Zoom(zoom);

}

void ImagePanel::OnSlide(wxScrollEvent & evt) {
  if (block != NULL) {
    int pos = evt.GetPosition();
    canvas->SetImage(block->GetImage(pos), block->GetX(), block->GetY());
    canvas->Zoom(zoom);
    canvas->Refresh();
  }
}

void ImagePanel::ZoomIn(wxCommandEvent & evt) {
  zoom = zoom * 2;
  if (block != NULL) {
    canvas->Zoom(zoom);
  }
}

void ImagePanel::ZoomOut(wxCommandEvent & evt) {
  zoom = zoom / 2;
  if (block != NULL) {
    canvas->Zoom(zoom);
  }
}
