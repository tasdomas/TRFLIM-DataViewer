#ifndef DV_IMAGE_PANEL_H
#define DV_IMAGE_PANEL_H

#include "wx/wx.h"
#include "canvas.h"
#include "compdialog.h"
#include "graphdialog.h"
#include "../fileformat/datablock.h"
#include "../lib/componentblock.h"
#include "wx/spinctrl.h"

/* generic image panel class */
class ImagePanel : public wxPanel {
 public:
  ImagePanel(wxWindow * parent, wxWindowID id = wxID_ANY);
  ~ImagePanel();

  void ZoomIn(wxCommandEvent &);
  void ZoomOut(wxCommandEvent &);
  void Save(wxCommandEvent &);

  void SetImage(DataBlock * image);

  DECLARE_EVENT_TABLE()

 protected:

  DVCanvas * canvas;
  DataBlock * block;

  float zoom;

  wxBoxSizer * sizer;
  wxBoxSizer * sizerLeft;
};

class GrayScalePanel : public ImagePanel {
 public:
  GrayScalePanel(wxWindow * parent, wxWindowID = wxID_ANY, bool multiImage = false);
  ~GrayScalePanel();

  void OnSlide(wxScrollEvent & evt);
  void SetImage(DataBlock * image);
  DECLARE_EVENT_TABLE()
 private:
  wxScrollBar * scroller;
  wxStaticText * index;
  bool multi;
};

class ComponentsPanel : public ImagePanel {
 public:
  ComponentsPanel(wxWindow * parent, wxWindowID = wxID_ANY);
  ~ComponentsPanel();

  void SetImage(DataBlock * image);
  void Compute(wxCommandEvent &);
  void ChangeComponent(wxSpinEvent & evt);
  DECLARE_EVENT_TABLE()
 protected:
  wxSpinCtrl * compNo;
  wxButton * btnCompute;
};
#endif
