#include "log.h"
#include "../interfaces/ns_interface.h"

CLogging* logger;

void logger_init()
{
 logger = ns_create_interface(NS_LOGGING_VERSION, 0);
}

void ns_log(LogLevel level, char* msg)
{
  logger->vftable->log(logger, g_init_data->handle, level, msg);
}
