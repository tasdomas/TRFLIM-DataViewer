#include "test_app.h"

#include <vector>
#include "math.h"

using namespace std;

IMPLEMENT_APP(TestApp)

bool TestApp::OnInit() {
  wxInitAllImageHandlers();
  GraphDialog * mainframe = new GraphDialog(NULL, -1);
  mainframe->Show(TRUE);

  float step = 0.2;
  
  vector<float> x;
  vector<float> y;

  for (int i = 0; i < 50; i++) {
    x.push_back(i * step);
    y.push_back(sin(x[i]));
  }

  mainframe->SetGraph(x,y);

  return true;
}
