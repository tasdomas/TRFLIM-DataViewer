#ifndef DV_MAIN_FRAME_H
#define DV_MAIN_FRAME_H

#include "wx/wx.h"
#include "wx/notebook.h"

#include "canvas.h"
#include "datapanel.h"
#include "imagepanel.h"
#include "scaleframe.h"
#include "marginsdialog.h"

#include "../fileformat/sdt.h"
#include "../fileformat/datablock.h"
#include "../lib/fwhmblock.h"

class MainFrame : public wxFrame {
  protected:
    wxImage * image;
    wxNotebook * book;
    DataPanel * dataPanel;
    GrayScalePanel * rawPanel;
    GrayScalePanel * fwhmPanel;
    ComponentsPanel * componentsPanel;
    ScaleFrame * scaleFrame;

    SDT * dataFile;

    FWHMBlock * fwhm;

    void UpdateSDT(string fileName = "");
  public:
    MainFrame();

    void OnQuit(wxCommandEvent&);
    void OnLoad(wxCommandEvent&);
    void ShowScale(wxCommandEvent&);
    void OnBlockSelect(wxSpinEvent& evt);
    void SetMargins(wxCommandEvent &);
  private:
    int pos;
    DECLARE_EVENT_TABLE()

};

#endif
