#include "webserv.h"

const char *base_path = "htdocs";
const size_t base_path_len = strlen(base_path);
const char *notfoundf = "notfound";
const char *contenttype_path = "ctype/";
const char *sends_cyclef = "send_cycles";

enviroment env;
EthernetServer server(0);

void setup(){
  File32 file;

  //Serial and SD initialization
  Serial.begin(9600);
  Serial.print("SD ");
  if (!env.sd.begin(4, SPI_FULL_SPEED)){
    Serial.println("KO");
  } else {
    Serial.println("OK");
  }


  //Ethernet initialization
  // IP
  file = env.sd.open("ip", FILE_READ);
  int ip_list[4];
  for (int i = 0; i < 4; i ++){
    null_terminate(env.buff, file.readBytesUntil('.', env.buff, 4));
    ip_list[i] = atoi(env.buff);
  }
  file.close();
  IPAddress ip (ip_list[0], ip_list[1], ip_list[2], ip_list[3]);
  //Get port
  file = env.sd.open("port", FILE_READ);
  null_terminate(env.buff, file.readBytes(env.buff, BUFF_SIZE));
  unsigned int port = atol(env.buff);
  //MAC setup
  byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  //Server setup
  Ethernet.begin(mac, ip);
  server = EthernetServer(port);
  server.begin ();


  //Print info to the serial
  Serial.print ("Server at http://");
  Serial.print (Ethernet.localIP ());
  Serial.print (':');
  Serial.println (port);

  //Open static files
  file = env.sd.open(sends_cyclef, FILE_READ);
  env.send_cycles = file.parseInt();
  file.close();
  env.header = env.sd.open("header", FILE_READ);

  //Empty client memory
  memset(&env.clients, 0, sizeof(client) * CLIENTS);
}

void loop(){
  env.lobby.client = server.accept();
  if (env.lobby.client){
    Serial.print('s');
    if (recieve_client(&env.lobby)) {
      handshake(&env.lobby);
      Serial.print(env.lobby.method);
    }
  } else {
    Serial.print('n');
  }
  delay(1000);
  /*for (unsigned int i = 0; i < sends_cycle; i ++){
      if (send_buf(&file, &main_client) != BUFF_SIZE){
        main_client.flush();
        main_client.stop();
        file.close();
        break;
      }
  }*/
}