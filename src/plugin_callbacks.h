#ifndef PLUGIN_CALLBACKS_H
#define PLUGIN_CALLBACKS_H

#include <windows.h>
#include <stdint.h>
#include "log/log.h"
#include "interface.h"
#include "interfaces/ns_interface.h"

#define PLUGIN_ID_VERSION "PluginId001"

typedef enum {
  ID_NAME = 0,
  ID_LOG_NAME,
  ID_DEPENDENCY_NAME,
  ID_CONTEXT,
} PluginPropertyId;

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
    PluginProperty (*GetProperty)(struct IPluginId* self, PluginPropertyId pop);
  }* vftable;
} IPluginId;

void* CreatePluginId();

// interface that defines all launcher callbacks
typedef struct IPluginCallbacks {
  struct IPluginCallbacks_vftable{
   void (*Init)(struct IPluginCallbacks* self, NorthstarData* data);
   void (*Finalize)(struct IPluginCallbacks* self);
  }* vftable;
} IPluginCallbacks;

void* CreatePluginCallbacks();

#endif
