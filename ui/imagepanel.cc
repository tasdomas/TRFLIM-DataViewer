#include "imagepanel.h"
#include "enums.h"

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)

EVT_COMMAND_SCROLL(ID_Slide, ImagePanel::OnSlide)
EVT_BUTTON(ID_ZoomIn, ImagePanel::ZoomIn)
EVT_BUTTON(ID_ZoomOut, ImagePanel::ZoomOut)
EVT_BUTTON(ID_SaveImage, ImagePanel::Save)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxWindow * parent, wxWindowID id, bool multiImage) 
: wxPanel(parent, id, wxDefaultPosition),
  block(NULL), multi(multiImage), zoom(1.0) {

  wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer * sizerLeft = new wxBoxSizer(wxVERTICAL);

  canvas = new DVCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(200, 200));
  sizerLeft->Add(canvas, 1, wxEXPAND);

  if (multiImage) {
    wxBoxSizer * scrollSizer = new wxBoxSizer(wxHORIZONTAL);
    scroller = new wxScrollBar(this, ID_Slide);
    scrollSizer->Add(scroller, 1);
    index = new wxStaticText(this, wxID_ANY, _("0/0"));
    scrollSizer->Add(index, 0.1);
    sizerLeft->Add(scrollSizer, 0.1, wxEXPAND);
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

  if (multi) {
    scroller->SetScrollbar(0, 1, image->GetZ() - 1, 1);
    index->SetLabel(wxString::Format(_("%d/%d"), 1, block->GetZ()));

    canvas->SetImage(block->GetImage(0), block->GetX(), block->GetY());
    canvas->Zoom(zoom);
  } else {
    canvas->SetImage(block);
    canvas->Zoom(zoom);
  }

}

void ImagePanel::OnSlide(wxScrollEvent & evt) {
  if (block != NULL) {
    int pos = evt.GetPosition();

    index->SetLabel(wxString::Format(_("%d/%d"), pos+1, block->GetZ()));

    canvas->SetImage(block->GetImage(pos), block->GetX(), block->GetY());
    canvas->Zoom(zoom);
    canvas->Refresh();
    
    
  }
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
