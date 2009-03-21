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

void DVCanvas::SetImage(ushort * img, int size_x, int size_y) {
  if (image != NULL) {
    delete image;
    delete bitmap;
  }

  image = new wxImage(size_x, size_y, true);
  ushort max = 0;
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      ushort curr = img[i + j*size_x];
      if (curr > max) {
        max = curr;
      }
    }
  }
  if (max == 0) {
    max = 1;
  }
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      ushort curr = (img[i + j*size_x] * 255) / max;
      image->SetRGB(i,j, curr, curr, curr);
    }
  }

  bitmap = new wxBitmap(*image);

  SetVirtualSizeHints(image->GetWidth(), image->GetHeight());
  SetScrollbars(1, 1, image->GetWidth(), image->GetHeight());    
}

void DVCanvas::OnDraw(wxDC& dc) {
  if (bitmap != NULL) {
    dc.DrawBitmap(*bitmap, 0, 0, false);
  }
}

