#include "exception.h"

BasicException::BasicException() 
  : msg("") {
}

BasicException::BasicException(string message) 
  : msg(message) {
}

string BasicException::GetMsg() {
  return msg;
}
