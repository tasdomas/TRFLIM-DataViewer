#include "canvas.h"

DVCanvas::DVCanvas(wxWindow * parent, wxWindowID id, 
const wxPoint & pos, const wxSize & size) 
  : wxScrolledWindow(parent, id, pos, size, wxHSCROLL | wxVSCROLL),
  image(NULL), bitmap(NULL) {

}

DVCanvas::~DVCanvas() {
  if (image != NULL) {
    delete image;
  }
  if (bitmap != NULL) {
    delete bitmap;
  }
}

void DVCanvas::SetImage(wxImage & img) {
  if (image != NULL) {
    delete image;
    delete bitmap;
  }
  image = new wxImage(img);
  bitmap = new wxBitmap(*image);

  SetVirtualSizeHints(image->GetWidth(), image->GetHeight());
  SetScrollbars(1, 1, image->GetWidth(), image->GetHeight());
}

void DVCanvas::OnDraw(wxDC& dc) {
  if (bitmap != NULL) {
    dc.DrawBitmap(*bitmap, 0, 0, false);
  }
}

