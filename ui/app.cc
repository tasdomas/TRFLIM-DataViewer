#include "app.h"

IMPLEMENT_APP(DVApp)

bool DVApp::OnInit() {
  MainFrame * mainframe = new MainFrame();
  mainframe->Show(TRUE);

  return true;
}
