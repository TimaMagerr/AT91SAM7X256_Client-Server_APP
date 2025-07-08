#pragma once

#include "libraries.h"
#include "structs.h"

using namespace std;
//������� �������� ��������� � �����
void Recieve(buffSock* data);

//������� �������� ��������� � �����
void Send(buffSock* data);

//������� ��������� �������� ���������
void singleSend(SOCKET* socket, char& choice);

//������� ���������� �������� ���������
void singleRecieve(SOCKET* socket, char& rec);

//������� ���������� ������ �������
void ClientData(SOCKET* socket, vector<double>& calculateData);

//������� ���������� ������ �������
void ServerData(SOCKET* socket);
//avgFunc avgAndAboveAvg(vector<int>& numbers);

// ������� ��� �������������� ������� double � ������ char
vector<char> doubleToCharVector(const vector<double>& doubles);

// ������� ��� �������������� ������� int � ������ char
vector<char> intToCharVector(const vector<int>& doubles);

// ������� ��� �������������� ������� char � ������ double
vector<double> charToDoubleVector(const vector<char>& chars);

// ������� ��� �������������� ������� char � ������ int
vector<int> charToIntVector(const vector<char>& chars);

//������� �������� �������� ��������������� � �����, ��� ������ ��.��.
template <typename T> vector<double> avgAndAboveAvg(vector<T>& numbers);

//���������� ������� int
vector<double> listDoubleNumbers(vector<double>& numbers);

//���������� ������� double
vector<int> listIntNumbers(vector<int>& numbers);

//����� ������� �� �����
template <typename Type> void printVec(vector<Type>& data);

//������ ������� �����
void ipInit(int erStat, in_addr& ip_to_num);

//������������� �������� �����������
void sockInterfaces(int erStat, WSADATA& wsdata);

//������������� ������
void sockInit(SOCKET& Sock);

//�������� ������ ������� � ���� IP-�����/����
void ipPortBind(int erStat, sockaddr_in& info, in_addr& ip_to_num, SOCKET& sock);

//����������� � ������� � �������
void ipPortConnect(int erStat, sockaddr_in& servInfo, in_addr& ip_to_num, SOCKET& ClientSock);

//��������� ����� listen()
void listenPort(int erStat, SOCKET& ServSock);

//������������� �����������
void acceptConn(sockaddr_in& clientInfo, SOCKET& ClientConn, SOCKET& ServSock);

//�������� ��������� (char-�������)
void recMessage(SOCKET* sock, vector<char>& buffer, short& packetSize);

void serverResponse(SOCKET* sock, vector<char>& buffer, short& packetSize);

//�������� ����� int
void sendNumbMessage(SOCKET* sock, int numb, int packetSize);




