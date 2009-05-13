#include "main_frame.h"
#include "enums.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame) 

EVT_MENU(ID_Quit, MainFrame::OnQuit)
EVT_MENU(ID_Load, MainFrame::OnLoad)
EVT_MENU(ID_LoadSimple, MainFrame::OnLoadSimple)
EVT_MENU(ID_Scale, MainFrame::ShowScale)
EVT_CHOICE(ID_BlockNo, MainFrame::OnBlockSelect)
EVT_BUTTON(ID_Margins, MainFrame::SetMargins)

END_EVENT_TABLE()

MainFrame::MainFrame() 
: wxFrame(NULL, wxID_ANY, _("DV"), wxDefaultPosition),
  scaleFrame(NULL), dataFile(NULL), fwhm(NULL) {
    //the menu

  pos = 0;
    wxMenu * menuData = new wxMenu;
    CreateStatusBar();

    menuData->Append( ID_Load, _("&Load.."));
    menuData->Append( ID_LoadSimple, _("&Load Simple.."));
    menuData->AppendSeparator();
    menuData->Append( ID_Quit, _("E&xit"));

    wxMenu * menuHelp = new wxMenu;
    menuHelp->Append( ID_Scale, _("&Scale"));

    wxMenuBar *menu = new wxMenuBar;
    menu->Append( menuData, _("&Data"));
    menu->Append( menuHelp, _("&Help"));

    SetMenuBar(menu);
    
    wxBoxSizer * sizer = new wxBoxSizer(wxHORIZONTAL);
    
    //canvas for displaying images
    book = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_TOP);

    rawPanel = new GrayScalePanel(book, wxID_ANY, TRUE, TRUE);
    fwhmPanel = new GrayScalePanel(book, wxID_ANY, FALSE);    
    componentsPanel = new ComponentsPanel(book, wxID_ANY);

    book->AddPage(rawPanel, _("Raw"), true);
    book->AddPage(fwhmPanel, _("FWHM"), false);
    book->AddPage(componentsPanel, _("Comp"), false);

    sizer->Add(book, 2, wxEXPAND, 0);
    
    dataPanel = new DataPanel(this);
    sizer->Add(dataPanel, 1, wxEXPAND, 0);
    
    SetSizer( sizer );

    sizer->SetSizeHints(this);

    Centre();
}

void MainFrame::OnQuit(wxCommandEvent &) {
  Close(TRUE);
  if (fwhm != NULL) {
    delete fwhm;
  }
}

// load file
void MainFrame::OnLoad(wxCommandEvent &) {
  pos = 0;
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
    wxBeginBusyCursor();
    if (dataFile != NULL) {
      delete dataFile;
    }

    string file = std::string(filename.mb_str()); 
    dataFile = new SDT(file);
    UpdateSDT(std::string(filename.mb_str()));
    wxEndBusyCursor();
  }
}

void MainFrame::OnLoadSimple(wxCommandEvent&) {
  pos = 0;
  wxString filename = wxFileSelector(
    _(".simple file to open"),
    _(""),
    _("plot"),
    _(""),
    _("*.simple"),
    wxFD_OPEN | wxFD_FILE_MUST_EXIST,
    this
  ); 
  if (! filename.empty()) {
    wxBeginBusyCursor();
    if (dataFile != NULL) {
      delete dataFile;
    }

    string file = std::string(filename.mb_str()); 
    dataFile = new SimpleSDT(file);
    UpdateSDT(file);
    wxEndBusyCursor();
  }
}

void MainFrame::UpdateSDT(string fileName) {
  dataPanel->UpdateData(fileName, dataFile->GetBlockCount() - 1, dataFile->GetSetupData());
  rawPanel->SetImage(dataFile->GetDataBlock(0));
  if (fwhm != NULL) {
    delete fwhm;
  }
  fwhm = new FWHMBlock(dataFile->GetDataBlock(0));
  fwhmPanel->SetImage(fwhm);
  
  componentsPanel->SetImage(dataFile->GetDataBlock(0));
}

void MainFrame::OnBlockSelect(wxCommandEvent& evt) {
  wxBeginBusyCursor();
  pos = evt.GetSelection();
  
  rawPanel->SetImage(dataFile->GetDataBlock(pos));
  if (fwhm != NULL) {
    delete fwhm;
  }
  fwhm = new FWHMBlock(dataFile->GetDataBlock(pos));
  fwhmPanel->SetImage(fwhm);
  componentsPanel->SetImage(dataFile->GetDataBlock(pos));

  wxEndBusyCursor();
}

void MainFrame::ShowScale(wxCommandEvent&) {
  scaleFrame = new ScaleFrame();

  scaleFrame->Show(true);
}

void MainFrame::SetMargins(wxCommandEvent&) {
  if (dataFile != NULL) {
    MarginsDialog * dia = new MarginsDialog(this, wxID_ANY, dataFile->GetDataBlock(pos));
    dia->ShowModal();
    dia->Destroy();
    
    rawPanel->SetImage(dataFile->GetDataBlock(pos));
    if (fwhm != NULL) {
      delete fwhm;
    }
    fwhm = new FWHMBlock(dataFile->GetDataBlock(pos));
    fwhmPanel->SetImage(fwhm);
    componentsPanel->SetImage(dataFile->GetDataBlock(pos));
  } else {
    wxMessageBox(_("Load a file first."));
  }
}
