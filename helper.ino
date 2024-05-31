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

void send_file(EthernetClient *client, File32 *file)
{
  size_t readed;

  while ((readed = file->readBytes(env.buff, BUFF_SIZE)) == BUFF_SIZE)
    client->write(env.buff, BUFF_SIZE);
  client->write(env.buff, readed);
}