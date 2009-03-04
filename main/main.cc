#include <iostream>
#include <fstream>

#include "../fileformat/fileformat.h"

using namespace std;

int main() {
  FileHeader fh;

  fstream sdt("data/test-skin.sdt",ios::binary|ios::in);
  
  sdt >> fh;

  cout << fh.data_count;

  return 0;
}
