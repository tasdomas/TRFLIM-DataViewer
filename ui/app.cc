#include "app.h"

IMPLEMENT_APP(DVApp)

bool DVApp::OnInit() {
  wxInitAllImageHandlers();
  MainFrame * mainframe = new MainFrame();
  mainframe->Show(TRUE);

  return true;
}
