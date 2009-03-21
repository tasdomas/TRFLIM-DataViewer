#include "imagepanel.h"

enum {
  ID_ZoomIn = 1,
  ID_ZoomOut,
  ID_SaveImage,
  ID_Slide
};

ImagePanel::ImagePanel(wxWindow * parent, wxWindowID id, bool multiImage) 
  : wxPanel(parent, id, wxDefaultPosition, wxSize(250, 250)) {

  wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer * sizerLeft = new wxBoxSizer(wxVERTICAL);

  canvas = new DVCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
  sizerLeft->Add(canvas, 1, wxEXPAND);

  if (multiImage) {
    scroller = new wxScrollBar(this, ID_Slide);
    sizerLeft->Add(scroller, 0, wxEXPAND);
  }

  sizer->Add(sizerLeft, 1, wxEXPAND);
  /*
  wxBoxSizer * sizerRight = new wxBoxSizer(wxVERTICAL);
  
  wxButton * btn = new wxButton(this, ID_ZoomIn, _("+"));
  sizerRight->Add(btn, 0);

  btn = new wxButton(this, ID_ZoomOut, _("-"));
  sizerRight->Add(btn, 0);

  btn = new wxButton(this, ID_SaveImage, _("Save"));
  sizerRight->Add(btn, 0);

  sizer->Add(sizerRight, 0);
  */
  SetSizer(sizerLeft);
  sizerLeft->SetSizeHints(this);
}

ImagePanel::~ImagePanel() {
}
