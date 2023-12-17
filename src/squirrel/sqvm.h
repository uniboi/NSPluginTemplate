#ifndef SQVM_H
#define SQVM_H

#include "squirrel/squirrel.h"

typedef struct HSquirrelVM {
  void* vftable;
  int uiRef;

} HSquirrelVM;

#endif
