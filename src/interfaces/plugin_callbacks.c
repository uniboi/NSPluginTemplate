#include <stdlib.h>
#include <stdio.h>
#include "plugin_callbacks.h"

#define PLUGIN_NAME "P4Plugin"
#define PLUGIN_LOG_NAME PLUGIN_NAME
#define PLUGIN_DEPENDENCY_NAME PLUGIN_NAME
#define PLUGIN_CONTEXT (PCTX_DEDICATED | PCTX_CLIENT)

const char* GetString(IPluginId* self, PluginString prop)
{
  switch(prop)
  {
    case ID_NAME:
      return PLUGIN_NAME;
      break;
    case ID_LOG_NAME:
      return PLUGIN_LOG_NAME;
      break;
    case ID_DEPENDENCY_NAME:
      return PLUGIN_DEPENDENCY_NAME;
      break;
    default:
      return 0;
  }
}

int64_t GetField(IPluginId* self, PluginField prop)
{
  switch(prop)
  {
    case ID_CONTEXT:
      return PLUGIN_CONTEXT;
    default:
      return 0;
    }
}

void Init(IPluginCallbacks* self, NorthstarData* data)
{
  init_ns_interface(data);
  sys_init();
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

void Unload(IPluginCallbacks* self) {};

void OnSqvmCreated(IPluginCallbacks* self, void* c_sqvm) {}

void OnSqvmDestroyed(IPluginCallbacks* self, int context) {}

void OnLibraryLoaded(IPluginCallbacks* self, HMODULE module, wchar_t* name) {}

void RunFrame(IPluginCallbacks* self) {}

IPluginCallbacks g_pluginCallbacks = {
  .vftable = &(struct IPluginCallbacks_vftable){
    .Init = Init,
    .Finalize = Finalize,
    .Unload = Unload,
    .OnSqvmCreated = OnSqvmCreated,
    .OnSqvmDestroyed = OnSqvmDestroyed,
    .OnLibraryLoaded = OnLibraryLoaded,
    .RunFrame = RunFrame
  }
};

void* CreatePluginCallbacks() { return &g_pluginCallbacks; }

IPluginId g_pluginId = {
  .vftable = &(struct IPluginId_vftable){
    .GetString = GetString,
    .GetField = GetField
  }
};

void* CreatePluginId() { return &g_pluginId; }

