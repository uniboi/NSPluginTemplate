#include "plugin_callbacks.h"
#include "bindings/module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bindings/native_closures.h"
#include "cvar/cvar.h"
#include "interfaces/cvar.h"
#include "interfaces/engine_interface.h"
#include "interfaces/sys.h"
#include "squirrel/relay.h"

#define PLUGIN_NAME "P4Plugin"
#define PLUGIN_LOG_NAME PLUGIN_NAME
#define PLUGIN_DEPENDENCY_NAME PLUGIN_NAME
#define PLUGIN_CONTEXT (PCTX_DEDICATED | PCTX_CLIENT)

void reinitialize() {
  ns_log(LOG_INFO, "reinitializing");

  HMODULE sv_module = GetModuleHandleA("server.dll");
  if (sv_module)
    init_relay_sv(sv_module);

  HMODULE cl_module = GetModuleHandleA("client.dll");
  if (cl_module)
    init_relay_cl(cl_module);
}

const char *GetString(IPluginId *self, PluginString prop) {
  switch (prop) {
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

int64_t GetField(IPluginId *self, PluginField prop) {
  switch (prop) {
  case ID_CONTEXT:
    return PLUGIN_CONTEXT;
  default:
    return 0;
  }
}

void Init(
    IPluginCallbacks *self, HMODULE module, NorthstarData *data, char reloaded
) {
  init_ns_interface(module, data);
  sys_init();

  if (reloaded)
    reinitialize();

  ns_log(LOG_INFO, "Successfully initialized");
}

void Finalize(IPluginCallbacks *self) {
  /*
   * Get interfaces from other plugins you depend on here like this
   *
   * HMODULE my_dependency_module = GetModuleHandleA("MyDependency.dll");
   * if(my_dependency_module)
   * {
   * 	void* my_dependency_interface = GetProcAddress(my_dependency_module,
   * "CreateInterface");
   * 	...
   * }
   */

  ns_log(LOG_INFO, "Finalized.");
}

bool Unload(IPluginCallbacks *self) {
  ns_log(LOG_INFO, "Unloading.");
  return true;
}

void OnSqvmCreated(IPluginCallbacks *self, CSquirrelVM *c_sqvm) {
  ns_logf(LOG_INFO, "created %s sqvm", get_context_name(c_sqvm->context));

  switch (c_sqvm->context) {
  case SC_SERVER:
    sv_register_native_closures(c_sqvm);
    break;
  case SC_CLIENT:
    cl_register_native_closures(c_sqvm);
    break;
  case SC_UI:
    ui_register_native_closures(c_sqvm);
    break;
  default:
    ns_logf(LOG_INFO, "invalid context %d", c_sqvm->context);
    return;
  }

  sqapi(c_sqvm->context)->c_sq_define_constant(c_sqvm, "P4_TEST", 2);
}

void OnSqvmDestroyed(IPluginCallbacks *self, CSquirrelVM *c_sqvm) {
  ns_logf(LOG_INFO, "destroying %s sqvm", get_context_name(c_sqvm->context));
}

void OnLibraryLoaded(IPluginCallbacks *self, HMODULE module, const char *name) {
  if (strcmp(name, "server.dll") == 0) {
    g_server = module;
    init_relay_sv(module);
    return;
  }

  if (strcmp(name, "client.dll") == 0) {
    g_client = module;
    init_relay_cl(module);
    return;
  }

  if (strcmp(name, "engine.dll") == 0) {
    g_engine = module;
    init_engine_interface(module);
    engine_cvar_init();
    return;
  }
}

void RunFrame(IPluginCallbacks *self) {}

IPluginCallbacks g_pluginCallbacks = {
    .vftable = &(struct IPluginCallbacks_vftable
    ){.Init = Init,
      .Finalize = Finalize,
      .Unload = Unload,
      .OnSqvmCreated = OnSqvmCreated,
      .OnSqvmDestroyed = OnSqvmDestroyed,
      .OnLibraryLoaded = OnLibraryLoaded,
      .RunFrame = RunFrame}};

void *CreatePluginCallbacks() { return &g_pluginCallbacks; }

IPluginId g_pluginId = {
    .vftable = &(struct IPluginId_vftable
    ){.GetString = GetString, .GetField = GetField}};

void *CreatePluginId() { return &g_pluginId; }
