#include "scaleframe.h"

ScaleFrame::ScaleFrame()
  : wxFrame(NULL, wxID_ANY, _("Scale"), wxDefaultPosition, wxSize(250, 250)) {

  wxGridBagSizer * sizer = new wxGridBagSizer();
  
  wxStaticText * text = new wxStaticText(this, wxID_ANY, _("Intensity"));
  sizer->Add(text, wxGBPosition(0,0));

  wxStaticText * text2 = new wxStaticText(this, wxID_ANY, _("FWHM"));
  sizer->Add(text2, wxGBPosition(1,1));

  DVCanvas * canvas = new DVCanvas(this, wxID_ANY, wxDefaultPosition, wxSize(200,200));
  sizer->Add(canvas, wxGBPosition(0, 1));

  wxImage img (200, 200, true);
  for (int x = 0; x  < 200; x++) {
    for (int y = 0; y < 200; y++) {
      wxImage::HSVValue t (0.75 - 0.75*(float)y / 200,
                           1.0,
                           1.0 - (float)x / 200
                           );
      wxImage::RGBValue tt = wxImage::HSVtoRGB(t);
      img.SetRGB(x, y, tt.red, tt.green, tt.blue);
    }
  }
  canvas->SetImage(img);
  SetSizer(sizer);
}

  

  

  
