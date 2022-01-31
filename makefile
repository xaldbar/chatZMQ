CXX = g++
FLAGS = -lzmq -pthread -o
all: client server
client: client.cpp ./src/Client/Client.cpp ./src/User/User.cpp
	${CXX} -fsanitize=address client.cpp ./src/Client/Client.cpp ./src/User/User.cpp ${FLAGS} client -w
server: server.cpp ./src/Server/Server.cpp ./src/User/User.cpp
	${CXX} -fsanitize=address server.cpp ./src/Server/Server.cpp ./src/User/User.cpp ${FLAGS} server -w
clear:
	rm client server
