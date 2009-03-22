#ifndef DV_CANVAS_H
#define DV_CANVAS_H

#include "wx/wx.h"
#include "../fileformat/datablock.h"

class DVCanvas : public wxScrolledWindow {
public:
  DVCanvas(wxWindow * parent, wxWindowID id, 
      const wxPoint & pos = wxDefaultPosition, const wxSize & size = wxDefaultSize);

  ~DVCanvas();

  void Zoom(float zoom);

  void OnDraw(wxDC& dc);

  void SetImage(wxImage & img);

  void SetImage(ushort * img, int size_x, int size_y);
  void SetImage(DataBlock * block);
  
  void SaveImage(wxString & name, float zoom);

private:
  wxImage * image;
  wxBitmap * bitmap;
};


#endif
