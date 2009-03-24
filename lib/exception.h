#ifndef DV_BASIC_EXCEPTION_H
#define DV_BASIC_EXCEPTION_H

#include <string>
using namespace std;

class BasicException {

 public:
  BasicException();
  BasicException(string message);

  string GetMsg();

 private:
  string msg;
};

#endif
