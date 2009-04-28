#include "canvas.h"
#include "imagepanel.h"

BEGIN_EVENT_TABLE(DVCanvas, wxScrolledWindow)

EVT_LEFT_DOWN(DVCanvas::MouseDown)

END_EVENT_TABLE()

DVCanvas::DVCanvas(wxWindow * parent, wxWindowID id, 
const wxPoint & pos, const wxSize & size) 
  : wxScrolledWindow(parent, id, pos, size, wxHSCROLL | wxVSCROLL),
  image(NULL), bitmap(NULL), data(NULL) {

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
  data = NULL;

  image = new wxImage(img);
  bitmap = new wxBitmap(*image);

  SetVirtualSizeHints(image->GetWidth(), image->GetHeight());
  SetScrollbars(1, 1, image->GetWidth(), image->GetHeight());
}

void DVCanvas::SetImage(DataBlock * block) {
  image = new wxImage(block->GetX(), block->GetY());
  data = block;

  int hmax = 0;
  int smax = 0;
  for (int i = 0; i < block->GetX(); i++) {
    for (int j = 0; j < block->GetY(); j++) {
      if (block->GetPoint(i, j, 0) > hmax) {
        hmax = block->GetPoint(i, j, 0);
      }
      if (block->GetPoint(i, j, 1) > smax) {
        smax = block->GetPoint(i, j, 1);
      }
    }
  }

  for (int i = 0; i < block->GetX(); i++) {
    for (int j = 0; j < block->GetY(); j++) {
      wxImage::HSVValue t (0.75* (1.0 - (float)block->GetPoint(i, j, 1) / smax),
                           1.0,
                           (float)block->GetPoint(i, j, 0) / hmax
                           );
      wxImage::RGBValue tt = wxImage::HSVtoRGB(t);
      //char val = 256 * block->GetPoint(i, j, 0) / hmax;
      image->SetRGB(i, j, tt.red, tt.green, tt.blue);
    }
  }
}

void DVCanvas::SetImage(uushort * img, int size_x, int size_y) {
  if (image != NULL) {
    delete image;
    delete bitmap;
  }

  image = new wxImage(size_x, size_y, true);
  uushort max = 0;
  for (int i = 0; i < size_x; i++) {
    for (int j = 0; j < size_y; j++) {
      uushort curr = img[i + j*size_x];
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
      uushort curr = (img[i + j*size_x] * 255) / max;
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

void DVCanvas::Zoom(float zoom) {
  if (image != NULL) {
    delete bitmap;

    bitmap = new wxBitmap(image->Scale((int)(image->GetWidth() * zoom),
                                         (int)(image->GetHeight() * zoom)));

    SetVirtualSizeHints(bitmap->GetWidth(), bitmap->GetHeight());
    SetScrollbars(1, 1, bitmap->GetWidth(), bitmap->GetHeight()); 

    Refresh();
  }
}

void DVCanvas::SaveImage(wxString & name, float zoom) {
  if (image != NULL) {
    wxImage img (image->Scale((int)image->GetWidth() * zoom, 
                               (int)image->GetHeight() * zoom));
    img.SaveFile(name);
  }
}

void DVCanvas::MouseDown(wxMouseEvent & evt) {
  wxPoint pt = evt.GetLogicalPosition(*(new wxClientDC(this)));

  if ((image != NULL) && (evt.m_controlDown)) {
    float zoom = (float)bitmap->GetWidth() / image->GetWidth();
    pt.x = pt.x / zoom;
    pt.y = pt.y / zoom;

    PointEvent event(POINT_EVT, 0, pt.x, pt.y);
    GetEventHandler()->ProcessEvent( event );
  } else {

    if ((image != NULL) && (data != NULL)) {
      float zoom = (float)bitmap->GetWidth() / image->GetWidth();
      pt.x = pt.x / zoom;
      pt.y = pt.y / zoom;

      if ((pt.x <= bitmap->GetWidth()) && (pt.y < bitmap->GetHeight())) {

        int intensity = data->GetPoint(pt.x, pt.y, 0);
        int fwhm = data->GetPoint(pt.x, pt.y, 1);
        wxFrame * frame = (wxFrame*)(((GetParent())->GetParent())->GetParent());
        frame->SetStatusText(wxString::Format(_("Int: %d, FWHM: %d"), intensity, fwhm));
      }
    }
  }
  
  evt.Skip();
}
