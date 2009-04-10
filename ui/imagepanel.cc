#include "imagepanel.h"
#include "enums.h"

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_BUTTON(ID_ZoomIn, ImagePanel::ZoomIn)
EVT_BUTTON(ID_ZoomOut, ImagePanel::ZoomOut)
EVT_BUTTON(ID_SaveImage, ImagePanel::Save)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxWindow * parent, wxWindowID id) 
: wxPanel(parent, id, wxDefaultPosition),
  block(NULL), zoom(1.0) {

  sizer = new wxBoxSizer(wxHORIZONTAL);

  sizerLeft = new wxBoxSizer(wxVERTICAL);

  canvas = new DVCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
  sizerLeft->Add(canvas, 1, wxEXPAND);

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

  canvas->SetImage(block);
  canvas->Zoom(zoom);

}

void ImagePanel::ZoomIn(wxCommandEvent &) {
  zoom = zoom * 2;
  if (block != NULL) {
    canvas->Zoom(zoom);
  }
}

void ImagePanel::ZoomOut(wxCommandEvent &) {
  zoom = zoom / 2;
  if (block != NULL) {
    canvas->Zoom(zoom);
  }
}

void ImagePanel::Save(wxCommandEvent &) {
  wxString filename = wxFileSelector(
    _("Nurodykite bylos pavadinimą"),
    _(""),
    _(""),
    _(""),
    _("*.png"),
    wxFD_SAVE | wxFD_OVERWRITE_PROMPT,
    this
  ); 
  if (! filename.empty()) {
    canvas->SaveImage(filename, zoom);
  }
}
