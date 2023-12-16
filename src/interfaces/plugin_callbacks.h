#ifndef PLUGIN_CALLBACKS_H
#define PLUGIN_CALLBACKS_H

#include <windows.h>
#include <stdint.h>
#include "interfaces/sys.h"
#include "interface.h"
#include "interfaces/ns_interface.h"

#define PLUGIN_ID_VERSION "PluginId001"

typedef enum {
  ID_NAME = 0,
  ID_LOG_NAME,
  ID_DEPENDENCY_NAME,
} PluginString;

typedef enum {
  ID_CONTEXT = 0
} PluginField;

enum PluginContext {
  PCTX_DEDICATED = 0x1, // load on dedicated servers
  PCTX_CLIENT = 0x2 // load on clients
};

typedef union {
  char* string;
  int64_t number;
} PluginProperty;

// interface to query basic data of the plugin
typedef struct IPluginId {
  struct IPluginId_vftable {
    const char* (*GetString)(struct IPluginId* self, PluginString prop);
    int64_t (*GetField)(struct IPluginId* self, PluginField prop);
  }* vftable;
} IPluginId;

void* CreatePluginId();

// interface that defines all launcher callbacks
typedef struct IPluginCallbacks {
  struct IPluginCallbacks_vftable{
   void (*Init)(struct IPluginCallbacks* self, NorthstarData* data);
   void (*Finalize)(struct IPluginCallbacks* self);
   void (*Unload)(struct IPluginCallbacks* self);
   void (*OnSqvmCreated)(struct IPluginCallbacks* self, void* c_sqvm);
   void (*OnSqvmDestroyed)(struct IPluginCallbacks* self, int context);
   void (*OnLibraryLoaded)(struct IPluginCallbacks* self, HMODULE module, wchar_t* name);
   void (*RunFrame)(struct IPluginCallbacks* self);
  }* vftable;
} IPluginCallbacks;

void* CreatePluginCallbacks();

#endif
