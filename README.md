# C++ TCP Raw Socket Server

Простой и корректный TCP-сервер на C++ с использованием сырых сокетов Linux. Принимает и обрабатывает данные от клиентов в реальном времени.

## Особенности

- Чистые сокеты Linux (без внешних библиотек)
- Корректная обработка ошибок
- Легко расширяемая логика обработки данных
- Работа с несколькими клиентами последовательно

## Требования

- Linux OS
- g++ с поддержкой C++11 или новее
- Стандартные библиотеки POSIX

## Установка и запуск

### Компиляция сервера

```bash
# Компиляция объектных файлов
g++ -c server.cpp -o server.o
g++ -c task_manager.cpp -o task_manager.o
g++ -c http_handler.cpp -o http_handler.o
g++ -c parser.cpp -o parser.o
g++ -c models.cpp -o models.o
g++ -c run_process.cpp -o run_process.o

# Линковка
g++ server.o http_handler.o parser.o models.o task_manager.o run_process.o -o server
```


### Компиляция тестового клиента (опционально)
```bash
# Компиляция
g++ -c client.cpp -o client.o

# Линковка
g++ client.o -o client
```
### Запуск клиента

```bash
./client
```

## Использование

1. Запустите сервер
2. Подключитесь через тестовый клиент 
3. Отправляйте текстовые сообщения
4. Сервер преобразует их в ВЕРХНИЙ РЕГИСТР и отправит обратно


## Структура проекта

```
.
├── server.cpp # Основной код сервера
├── client.cpp # Тестовый клиент
├── http_handler.cpp # HTTP обработчик запросов
├── task_manager.cpp # Управление задачами
├── parser.cpp # Парсер данных
├── models.cpp # Модели данных
├── run_process.cpp # Утилита запуска процессов
├── Dockerfile # Docker конфигурация
├── Docker.yml # Docker Compose конфигурация
└── README.md # Документация
```
