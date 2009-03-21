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
    book = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

    rawPanel = new ImagePanel(book, wxID_ANY, TRUE);

    book->AddPage(rawPanel, _("Raw"), true);

    sizer->Add(book, 2, wxEXPAND, 0);
    
    dataPanel = new DataPanel(this);
    sizer->Add(dataPanel, 1, wxEXPAND, 0);
    
    SetSizer( sizer );

    sizer->SetSizeHints(this);

    Centre();
}

void MainFrame::OnQuit(wxCommandEvent &evt) {
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
    UpdateSDT(std::string(filename.mb_str()));
  }
}

void MainFrame::UpdateSDT(string fileName) {
  dataPanel->UpdateData(fileName, dataFile->GetBlockCount(), dataFile->GetSetupData());
  rawPanel->SetImage(dataFile->GetDataBlock(0));

}
