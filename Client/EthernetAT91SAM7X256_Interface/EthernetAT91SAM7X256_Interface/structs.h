#pragma once
#include "libraries.h"

//Структура, хранящая данные для инициализации для функций отправки и принятия сообщений
typedef struct {
    std::vector<char> buff;
    SOCKET* socket;
    const char* user;
} buffSock;

//Структура для получения среднего значений чисел и кол-ва чисел, больше среднего
typedef struct {
    double average;
    int countAboveAvg;
}avgFunc;
