#include "webserv.h"

void null_terminate(void *buf, size_t len)
{
  ((char *)buf)[len] = '\0';
}

void end_client(client *c)
{
  c->client.flush();
  c->client.stop();
  c->file.close();
  c->active = false;
}