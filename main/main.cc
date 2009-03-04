#include <iostream>
#include <fstream>

#include "../fileformat/fileformat.h"

using namespace std;

int main() {
  FileHeader fh;

  fstream sdt("data/test-skin.sdt",ios::binary|ios::in);
  
  sdt >> fh;

  cout << hex << fh.revision;

  return 0;
}
