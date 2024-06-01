#include "webserv.h"

void report_entry(client *c)
{
  //c->file.getName(env.buff, BUFF_SIZE);

  Serial.print(c->id);
  Serial.print('\t');
  Serial.print(c->client.remoteIP());
  Serial.print(':');
  Serial.print(c->client.remotePort());
  Serial.print('\t');
  Serial.print(c->method);
  Serial.print('\t');
  Serial.print(c->code);
  Serial.print('\t');
  Serial.print(env.buff);
  Serial.println();
}

void report_serve(client *c)
{
  Serial.print(c->id);
  Serial.print('\t');
  Serial.print("Serving");
  Serial.println();
}

void report_exit(client *c)
{
  Serial.print(c->id);
  Serial.print('\t');
  Serial.print("Exiting");
  Serial.println();
}