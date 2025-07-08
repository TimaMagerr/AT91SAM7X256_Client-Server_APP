#pragma once

#include "libraries.h"
#include "structs.h"

using namespace std;
//Функция принятия сообщений в цикле
void Recieve(buffSock* data);

//Функция отправки сообщений в цикле
void Send(buffSock* data);

//Функция единичной отправки сообщения
void singleSend(SOCKET* socket, char& choice);

//Функция единичного принятия сообщения
void singleRecieve(SOCKET* socket, char& rec);

//Функция реализации логики клиента
void ClientData(SOCKET* socket, vector<double>& calculateData);

//Фукнция реализации логики сервера
void ServerData(SOCKET* socket);
//avgFunc avgAndAboveAvg(vector<int>& numbers);

// Функция для преобразования вектора double в вектор char
vector<char> doubleToCharVector(const vector<double>& doubles);

// Функция для преобразования вектора int в вектор char
vector<char> intToCharVector(const vector<int>& doubles);

// Функция для преобразования вектора char в вектор double
vector<double> charToDoubleVector(const vector<char>& chars);

// Функция для преобразования вектора char в вектор int
vector<int> charToIntVector(const vector<char>& chars);

//Функция подсчета среднего арифметического и чисел, что больше ср.ар.
template <typename T> vector<double> avgAndAboveAvg(vector<T>& numbers);

//Заполнение вектора int
vector<double> listDoubleNumbers(vector<double>& numbers);

//Заполнение вектора double
vector<int> listIntNumbers(vector<int>& numbers);

//Вывод вектора на экран
template <typename Type> void printVec(vector<Type>& data);

//Задаем сетевой адрес
void ipInit(int erStat, in_addr& ip_to_num);

//Инициализация сокетных интерфейсов
void sockInterfaces(int erStat, WSADATA& wsdata);

//Инициализация сокета
void sockInit(SOCKET& Sock);

//Привязка сокета сервера к паре IP-адрес/Порт
void ipPortBind(int erStat, sockaddr_in& info, in_addr& ip_to_num, SOCKET& sock);

//Подключение к клиента к серверу
void ipPortConnect(int erStat, sockaddr_in& servInfo, in_addr& ip_to_num, SOCKET& ClientSock);

//Прослушка порта listen()
void listenPort(int erStat, SOCKET& ServSock);

//Подтверждение подключения
void acceptConn(sockaddr_in& clientInfo, SOCKET& ClientConn, SOCKET& ServSock);

//Принятие сообщения (char-овского)
void recMessage(SOCKET* sock, vector<char>& buffer, short& packetSize);

void serverResponse(SOCKET* sock, vector<char>& buffer, short& packetSize);

//Отправка числа int
void sendNumbMessage(SOCKET* sock, int numb, int packetSize);




