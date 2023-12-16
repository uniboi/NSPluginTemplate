#ifndef SYS_H
#define SYS_H

#define NS_SYS_VERSION "NSSys001"

typedef enum {
  LOG_INFO,
  LOG_WARN,
  LOG_ERR,
} LogLevel;

typedef struct CSys {
  struct {
    void (*log)(struct CSys* self, int handle, LogLevel level, char* msg);
    void (*unload)(struct CSys* self, int handle);
  }* vftable;
} CSys;

void sys_init();

void ns_log(LogLevel level, char* msg);
void ns_unload_self();

#endif
