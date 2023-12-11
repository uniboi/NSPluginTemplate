#ifndef LOG_H
#define LOG_H

#define NS_LOGGING_VERSION "NSLogging001"

typedef enum {
  LOG_INFO,
  LOG_WARN,
  LOG_ERR,
} LogLevel;

typedef struct CLogging {
  struct {
    void (*log)(struct CLogging* self, int handle, LogLevel level, char* msg);
  }* vftable;
} CLogging;

void logger_init();

void ns_log(LogLevel level, char* msg);

#endif
