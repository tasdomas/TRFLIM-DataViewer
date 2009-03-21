#ifndef DV_MAIN_FRAME_H
#define DV_MAIN_FRAME_H

#include "wx/wx.h"
#include "wx/notebook.h"

#include "canvas.h"
#include "datapanel.h"
#include "imagepanel.h"

#include "../fileformat/sdt.h"
#include "../fileformat/datablock.h"

class MainFrame : public wxFrame {
  protected:
    wxImage * image;
    wxNotebook * book;
    DataPanel * dataPanel;
    ImagePanel * rawPanel;

    SDT * dataFile;

    void UpdateSDT(string fileName = "");
  public:
    MainFrame();

    void OnQuit(wxCommandEvent&);
    void OnLoad(wxCommandEvent&);
  private:
    DECLARE_EVENT_TABLE()

};

#endif
