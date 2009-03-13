#include <iostream>
#include <fstream>

#include "../fileformat/sdt.h"

using namespace std;

int main() {

  SDT data("data/test-skin.sdt");
  ushort * t = data.GetDataBlock(0);

  for (int i = 0; i < 256; i++) {
    cout << i << " " << t[i] << endl;
  }

  return 0;
}
