#include "main_frame.h"

MainFrame::MainFrame() 
  : wxFrame(NULL, wxID_ANY, _("DV"), wxDefaultPosition) {
    wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
    
    //canvas for displaying images
    canvas = new DVCanvas(
        this, 
        wxID_ANY, 
        wxDefaultPosition, 
        wxSize(600, 250));
    sizer->Add(canvas, 1, wxEXPAND, 0);

    SetSizer( sizer );

    SDT data("data/test-skin.sdt");

    ushort ** datab = data.ReformatBlocks();
    int x = data.GetSetupParam("SP_SCAN_X");
    int y = data.GetSetupParam("SP_SCAN_Y");
    int adc = data.GetSetupParam("SP_ADC_RE");

    int c_adc = 190;

    image = new wxImage(x, y, true);
    ushort max = 0;
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        ushort curr = datab[i + j*x][c_adc];
        if (curr > max) {
          max = curr;
        }
      }
    }
    if (max == 0) {
      max = 1;
    }
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++) {
        ushort curr = (datab[i + j*x][c_adc] * 255) / max;
        image->SetRGB(i,j, curr, curr, curr);
      }
    }
    
    wxImage * t = new wxImage(image->Scale(x*4, y*4));
    canvas->SetImage(*t);

    sizer->SetSizeHints(this);

    Centre();
}
