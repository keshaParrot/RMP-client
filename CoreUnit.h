#ifndef COREUNIT_H
#define COREUNIT_H

#include "MyDictionary.h"

class CoreUnit {
  public:
    char name[30];
    Dictionary load;
    float temperature;
    float frequency;
    float voltage;

    CoreUnit();
};

#endif  // COREUNIT_H
