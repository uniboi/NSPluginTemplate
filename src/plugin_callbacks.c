#include <stdlib.h>
#include <stdio.h>
#include "plugin_callbacks.h"

#define PLUGIN_NAME "P4Plugin"
#define PLUGIN_LOG_NAME PLUGIN_NAME
#define PLUGIN_DEPENDENCY_NAME PLUGIN_NAME
#define PLUGIN_CONTEXT (PCTX_DEDICATED | PCTX_CLIENT)

PluginProperty GetProperty(IPluginId* self, PluginPropertyId prop)
{
  PluginProperty value;

  switch(prop)
  {
    case ID_NAME:
      value.string = PLUGIN_NAME;
      break;
    case ID_LOG_NAME:
      value.string = PLUGIN_LOG_NAME;
      break;
    case ID_DEPENDENCY_NAME:
      value.string = PLUGIN_DEPENDENCY_NAME;
      break;
    case ID_CONTEXT:
      value.number = PCTX_DEDICATED;
      break;
    default:
      value.number = 0;
  }

  return value;
}

void Init(IPluginCallbacks* self, NorthstarData* data)
{
  init_ns_interface(data);
  logger_init();
  ns_log(LOG_INFO, "Successfully initialized");
}

void Finalize(IPluginCallbacks* self)
{
  /*
   * Get interfaces from other plugins you depend on here like this
   *
   * HMODULE my_dependency_module = GetModuleHandleA("MyDependency.dll");
   * if(my_dependency_module)
   * {
   * 	void* my_dependency_interface = GetProcAddress(my_dependency_module, "CreateInterface");
   * 	...
   * }
   */
}

IPluginCallbacks g_pluginCallbacks = {
  .vftable = &(struct IPluginCallbacks_vftable){
    .Init = Init,
    .Finalize = Finalize
  }
};

void* CreatePluginCallbacks() { return &g_pluginCallbacks; }

IPluginId g_pluginId = {
  .vftable = &(struct IPluginId_vftable){
    .GetProperty = GetProperty
  }
};

void* CreatePluginId() { return &g_pluginId; }

