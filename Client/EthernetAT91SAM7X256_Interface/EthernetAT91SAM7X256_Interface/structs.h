#pragma once
#include "libraries.h"

//���������, �������� ������ ��� ������������� ��� ������� �������� � �������� ���������
typedef struct {
    std::vector<char> buff;
    SOCKET* socket;
    const char* user;
} buffSock;

//��������� ��� ��������� �������� �������� ����� � ���-�� �����, ������ ��������
typedef struct {
    double average;
    int countAboveAvg;
}avgFunc;
