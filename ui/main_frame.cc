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

    ushort * datab = data.GetDataBlock(3);

    image = new wxImage(1024, 1024, true);
    ushort max = 0;
    for (int i = 0; i < 1024; i++) {
      for (int j = 0; j <= 1024; j++) {
        ushort curr = datab[i*1024 + j];
        if (curr > max) {
          max = curr;
        }
      }
    }
    for (int i = 0; i < 1024; i++) {
      for (int j = 0; j <= 1024; j++) {
        ushort curr = (datab[i*1024 + j] * 255) / max;
        image->SetRGB(i,j, curr, curr, curr);
      }
    }

    canvas->SetImage(*image);

    sizer->SetSizeHints(this);

    Centre();
}
