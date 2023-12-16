#include "interfaces/sys.h"
#include "interfaces/ns_interface.h"

CSys* sys;

void sys_init()
{
 sys = ns_create_interface(NS_SYS_VERSION, 0);
}

void ns_log(LogLevel level, char* msg)
{
  sys->vftable->log(sys, g_init_data->handle, level, msg);
}

void ns_unload_self()
{
  sys->vftable->unload(sys, g_init_data->handle);
}
