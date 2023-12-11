#include "ns_interface.h"

NorthstarData* g_init_data;

CreateInterfaceFn _p_ns_create_interface;

void init_ns_interface(NorthstarData* init_data)
{
  _p_ns_create_interface = (CreateInterfaceFn)GetProcAddress(init_data->ns_module, "CreateInterface");
  g_init_data = init_data;
}

void* ns_create_interface(char* name, InterfaceStatus* status)
{
  return _p_ns_create_interface(name, status);
}
