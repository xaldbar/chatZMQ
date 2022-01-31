#include <iostream>
#include "./src/Server/Server.h"

int main() {
  Server server("tcp://127.0.0.1:5555");
  server.run();
  server.eventLoop();
  server.stop();
}