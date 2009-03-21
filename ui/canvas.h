#ifndef DV_CANVAS_H
#define DV_CANVAS_H

#include "wx/wx.h"

class DVCanvas : public wxScrolledWindow {
public:
  DVCanvas(wxWindow * parent, wxWindowID id, 
      const wxPoint & pos = wxDefaultPosition, const wxSize & size = wxDefaultSize);

  ~DVCanvas();

  void OnDraw(wxDC& dc);

  void SetImage(wxImage & img);
private:
  wxImage * image;
  wxBitmap * bitmap;
};


#endif
