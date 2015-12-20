#ifndef GPRSL_h
#define GPRSL_h

#include "Arduino.h"

class GPRSL
{
public:
  GPRSL();
  boolean START();
  String POST(String var, char server[], char path[], char token[]);
  String PUT(String var, char server[], char path[], char token[]);
};

#endif
