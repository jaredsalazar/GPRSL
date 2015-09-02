#ifndef GPRSL_h
#define GPRSL_h

#include "Arduino.h"

class GPRSL 
{
public:
  GPRSL();
  void START();
  String POST(String var, char server[], char path[], char token[]);
};

#endif