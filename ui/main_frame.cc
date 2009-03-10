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

    image = new wxImage(1000, 1000, true);
    for (int i = 0; i < 1000; i++) {
      for (int j = 0; j <= 1000; j++) {
        if (i < j) {
          image->SetRGB(i,j, 0, 0, 0);
        } else {
          image->SetRGB(i,j, 50, 20, 20);
        }
      }
    }

    canvas->SetImage(*image);

    sizer->SetSizeHints(this);

    Centre();
}
