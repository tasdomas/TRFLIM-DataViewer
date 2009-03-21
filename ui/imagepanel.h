#ifndef DV_IMAGE_PANEL_H
#define DV_IMAGE_PANEL_H

#include "wx/wx.h"
#include "canvas.h"

class ImagePanel : public wxPanel {
 public:
  ImagePanel(wxWindow * parent, wxWindowID id = wxID_ANY, bool multiImage = TRUE);
  ~ImagePanel();

 private:
  DVCanvas * canvas;
  wxScrollBar * scroller;
};

#endif
