#ifndef DV_IMAGE_PANEL_H
#define DV_IMAGE_PANEL_H

#include "wx/wx.h"
#include "canvas.h"
#include "../fileformat/datablock.h"

class ImagePanel : public wxPanel {
 public:
  ImagePanel(wxWindow * parent, wxWindowID id = wxID_ANY, bool multiImage = TRUE);
  ~ImagePanel();

  void OnSlide(wxScrollEvent & evt);
  void ZoomIn(wxCommandEvent & evt);
  void ZoomOut(wxCommandEvent & evt);

  void SetImage(DataBlock * image);

  DECLARE_EVENT_TABLE()

 private:
  DVCanvas * canvas;
  DataBlock * block;
  wxScrollBar * scroller;
  
  float zoom;
};

#endif
