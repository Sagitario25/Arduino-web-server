#include "webserv.h"

void null_terminate(void *buf, size_t len)
{
  ((char *)buf)[len] = '\0';
}