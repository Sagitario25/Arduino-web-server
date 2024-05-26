#include "webserv.h"

static void send_header_chunk(client *c)
{
  size_t readed;

  while ((readed = env.header.readBytesUntil(';', env.buff, BUFF_SIZE)) == BUFF_SIZE) {
    c->client.write(env.buff, BUFF_SIZE);
  }
  c->client.write(env.buff, readed);
  env.header.read();
}

void send_header(client *c)
{
  unsigned long size = c->file.size();

  env.header.seek(0);
  send_header_chunk(c);//HTTP header
  c->client.print(c->code);
  send_header_chunk(c);//Content length
  c->client.print(size);
  send_header_chunk(c);//Content type
  c->client.write("text/plain", 10);
  send_header_chunk(c);//Server
  c->client.write("\n", 1);
}

void handshake(client *c)
{
  unsigned int active = active_clients();

  send_header(c);
  c->active = true;
  env.clients[active] = *c;
}