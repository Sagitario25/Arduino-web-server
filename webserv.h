#ifndef WEBSERV_H_
# define WEBSERV_H_

# include <SPI.h>
# include <SdFat.h>
# include <Ethernet.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 128
# endif
# ifndef CLIENTS
#  define CLIENTS 3
# endif

# ifndef BASE_PATH
#  define BASE_PATH "/htdocs"
# endif

enum http_methods {
  NOT,
  GET,
  POST,
  HEAD
};

typedef struct server_client_information {
  EthernetClient client;
  File32 file;
  unsigned char method;
  unsigned int code;
  bool active;
} client;

typedef struct server_information {
  SdFat sd;
  File32 header;
  client clients[CLIENTS];
  client lobby;
  char buff[BUFF_SIZE];
  unsigned int send_cycles;
} enviroment;

extern enviroment env;

void null_terminate(void *buf, size_t len);
unsigned int active_clients(void);
int recieve_client(client *c);
void handshake(client *c);

#endif