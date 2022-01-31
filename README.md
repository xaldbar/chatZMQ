# Чат на ZMQ с возможностью отправки отложенных сообщений


## Сборка
Для запуска необходимо перейти в директорию с проектом и собрать его с помощью команды:
```
make all
```


*Чтобы запустить проект у Вас должен быть установлен ZMQ и g++.* 

## Запуск

Запуск сервера и клиентов производится в отдельных терминалах.

Для использования чата неободимо запустить сервер
```
./server
```
И подключить к нему клиенты
```
./client 
```

## Команды для работы

Для начала отправки сообщений необходимо залогинить клиента используя команду **LOGIN**
```
PLS LOG IN: LOGIN <USENAME>
```

Для отправки сообщения
```
SEND <USERNAME> <MESSAGE>
```

Для отправки отложенного сообщения (*Задержка в секундах*)
```
DELAYSEND <DELAY> <USERNAME> <MESSAGE>
```