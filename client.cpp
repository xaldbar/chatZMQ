#include <iostream>
#include "./src/Client/Client.h"

int main() {
  Client client("tcp://127.0.0.1:5555");
  client.connect();
  client.eventLoop();
  client.disconnect();
}