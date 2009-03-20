#include "main_frame.h"

enum {
  ID_Quit = 1,
  ID_Load
};

BEGIN_EVENT_TABLE(MainFrame, wxFrame) 
  EVT_MENU(ID_Quit, MainFrame::OnQuit)
  EVT_MENU(ID_Load, MainFrame::OnLoad)
END_EVENT_TABLE()

MainFrame::MainFrame() 
: wxFrame(NULL, wxID_ANY, _("DV"), wxDefaultPosition),
  dataFile(NULL) {
    //the menu
    wxMenu * menuData = new wxMenu;

    menuData->Append( ID_Load, _("&Load.."));
    menuData->AppendSeparator();
    menuData->Append( ID_Quit, _("E&xit"));

    wxMenuBar *menu = new wxMenuBar;
    menu->Append( menuData, _("&Data"));

    SetMenuBar(menu);
    
    wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);
    
    //canvas for displaying images
    canvas = new DVCanvas(
        this, 
        wxID_ANY, 
        wxDefaultPosition, 
        wxSize(250, 250));
    sizer->Add(canvas, 1, wxEXPAND, 0);
    
    dataPanel = new DataPanel(this);
    sizer->Add(dataPanel, 0.11, wxEXPAND, 0);
    
    SetSizer( sizer );

    sizer->SetSizeHints(this);

    Centre();
}

void MainFrame::OnQuit(wxCommandEvent &evt) {
  delete image;
  delete canvas;
  Close(TRUE);
}

// load file
void MainFrame::OnLoad(wxCommandEvent &evt) {

  wxString filename = wxFileSelector(
    _("SDT file to open"),
    _(""),
    _("plot"),
    _(""),
    _("*.sdt"),
    wxFD_OPEN | wxFD_FILE_MUST_EXIST,
    this
  ); 
  if (! filename.empty()) {
    if (dataFile != NULL) {
      delete dataFile;
    }

    string file = std::string(filename.mb_str()); 
    dataFile = new SDT(file);
    UpdateSDT();
  }
}

void MainFrame::UpdateSDT() {
  DataBlock * datab = dataFile->GetDataBlock(0);
  int x = dataFile->GetSetupParam("SP_SCAN_X");
  int y = dataFile->GetSetupParam("SP_SCAN_Y");
  int adc = dataFile->GetSetupParam("SP_ADC_RE");

  int c_adc = 190;
  ushort * block = datab->GetImage(c_adc);

  image = new wxImage(x, y, true);
  ushort max = 0;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      ushort curr = block[i + j*x];
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
      ushort curr = (block[i + j*x] * 255) / max;
      image->SetRGB(i,j, curr, curr, curr);
    }
  }
    
  image->Rescale(x*4, y*4);
  canvas->SetImage(*image);
  canvas->Refresh();
}
