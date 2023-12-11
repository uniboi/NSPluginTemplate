#ifndef NS_INTERFACE_H
#define NS_INTERFACE_H

// TODO fix paths
#include "../interface.h"
#include <windows.h>

typedef struct {
  HMODULE ns_module;
  int handle;
} NorthstarData;

void init_ns_interface(NorthstarData* init_data);
void* ns_create_interface(char* name, InterfaceStatus* status);

extern NorthstarData* g_init_data;
#endif
