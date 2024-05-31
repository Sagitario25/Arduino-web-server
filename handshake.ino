#include "webserv.h"

static void send_content_type(client *c)
{
  size_t len = strlen(CONTENT_TYPE_DIR) + FORMAT_SIZE;
  char path[len] = "";
  File32 file;

  strcat(path, CONTENT_TYPE_DIR);
  strcat(path, c->format);
  Serial.println(path);
  file = env.sd.open(path, FILE_READ);
  if (!file) {
    c->client.write(DEFAULT_CONTENT_TYPE);
    return;
  }
  send_file(&c->client, &file);
  file.close();
}

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
  send_content_type(c);
  Serial.println(c->format);
  send_header_chunk(c);//Server
  c->client.write("\n", 1);
}

void handshake(client *c)
{
  unsigned int active = active_clients();

  send_header(c);
  if (c->method != HEAD) {
    c->active = true;
    memcpy(&env.clients[active], c, sizeof(client));
  } else
    end_client(c);
}