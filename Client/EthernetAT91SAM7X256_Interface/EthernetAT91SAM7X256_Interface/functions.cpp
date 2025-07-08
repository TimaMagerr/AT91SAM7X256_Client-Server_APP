#include "libraries.h"
#include "parameters.h"
#include "functions.h"
#include "structs.h"

using namespace std;

void Send(buffSock* data) {
    while (true) {
        cout << endl << data->user << " message: ";
        fgets(data->buff.data(), data->buff.size(), stdin);

        if (data->buff[0] == 'x' && data->buff[1] == 'x' && data->buff[2] == 'x') {
            shutdown(*(data->socket), SD_BOTH);
            closesocket(*(data->socket));
            WSACleanup();
            break;
        }

        int packet_size = send(*(data->socket), data->buff.data(), data->buff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            cout << endl << "Can't send message to " << data->user << ".Error # " << WSAGetLastError();
            closesocket(*(data->socket));
            WSACleanup();
            break;
        }
    }
}

void Recieve(buffSock* data) {
    while (true) {
        int packet_size = recv(*(data->socket), data->buff.data(), data->buff.size(), 0);
        if (packet_size == SOCKET_ERROR) {
            cout << endl << "Can't receive message from " << data->user << ".Error # " << WSAGetLastError();
            closesocket(*(data->socket));
            WSACleanup();
            break;
        }
        else {
            cout << endl << "\t\t\t\t" << data->user << " message: " << data->buff.data();
        }
    }
}


//������� �������� ���������
void recMessage(SOCKET* sock, vector<char>& buffer, short& packetSize) {
    //cout << "Waiting message from server...\n";
    packetSize = recv(*sock, buffer.data(), buffer.size(), 0);
    if (packetSize == SOCKET_ERROR) {
        cout << "Recv failed: Error#" << WSAGetLastError() << endl;
        closesocket(*sock);
        WSACleanup();
    }
    //else
        //cout << "�lient recv message!\n";
}

void serverResponse(SOCKET* sock, vector<char>& buffer, short& packetSize) {
    recMessage(sock, buffer, packetSize);
    //cout << "Server response:\n" << buffer.data() << endl;
    //memset(buffer.data(), 0, buffer.size()); //������� �����
}

void sendNumbMessage(SOCKET* sock, int numb, int packetSize) {
    stringstream sNumb;
    sNumb << numb << endl; //������� ������ � ������������ \n
    string stringNumb = sNumb.str();
    //cout << stringNumb;
    packetSize = send(*sock, stringNumb.c_str(), stringNumb.length(), 0);

    if (packetSize == SOCKET_ERROR) {
        cout << "Send failed: Error#" << WSAGetLastError() << endl;
        closesocket(*sock);
        WSACleanup();
    }
    else {
        cout << "����� ����������!\n";
    }
}


void singleSend(SOCKET* socket, char& choice) {
    int packet_size = send(*socket, &choice, sizeof(choice), 0);

    if (packet_size == SOCKET_ERROR) {
        cout << endl << "Error # " << WSAGetLastError();
        closesocket(*socket);
        WSACleanup();
    }
    else {
        cout << endl << "����� ���������" << endl;
    }
}

void singleRecieve(SOCKET* socket, char& rec) {
    int packet_size = recv(*socket, &rec, sizeof(rec), 0);

    if (packet_size == SOCKET_ERROR) {
        cout << "Error # " << WSAGetLastError();
        closesocket(*socket);
        WSACleanup();
    }
    else {
        cout << endl << "����� ������� " << endl;
    }
}


// ������� ��� �������������� ������� double � ������ char
vector<char> doubleToCharVector(const vector<double>& doubles) {
    vector<char> charVector;
    for (const double& d : doubles) {
        // ����������� ������ �������� double � ����� ���� char
        //const char* bytes = reinterpret_cast<const char*>(&d);
        const char* bytes = (const char*)(&d);
        // ��������� ����� � ������ char
        charVector.insert(charVector.end(), bytes, bytes + sizeof(double));
    }
    return charVector;
}

// ������� ��� �������������� ������� int � ������ char
vector<char> intToCharVector(const vector<int>& doubles) {
    vector<char> charVector;
    for (const int& d : doubles) {
        // ����������� ������ �������� double � ����� ���� char
        //const char* bytes = reinterpret_cast<const char*>(&d);
        const char* bytes = (const char*)(&d);
        // ��������� ����� � ������ char
        charVector.insert(charVector.end(), bytes, bytes + sizeof(int));
    }
    return charVector;
}

// ������� ��� �������������� ������� char � ������ double
vector<double> charToDoubleVector(const vector<char>& chars) {
    vector<double> doubleVector;
    size_t numDoubles = chars.size() / sizeof(double);
    for (size_t i = 0; i < numDoubles; ++i) {
        double d;
        // �������� ����� �� ������� char � ���������� ���� double
        memcpy(&d, &chars[i * sizeof(double)], sizeof(double));
        doubleVector.push_back(d);
    }
    return doubleVector;
}

// ������� ��� �������������� ������� char � ������ int
vector<int> charToIntVector(const vector<char>& chars) {
    vector<int> intVector;
    size_t numInt = chars.size() / sizeof(int);
    for (size_t i = 0; i < numInt; ++i) {
        int d;
        // �������� ����� �� ������� char � ���������� ���� double
        memcpy(&d, &chars[i * sizeof(int)], sizeof(int));
        intVector.push_back(d);
    }
    return intVector;
}

//������� �������� �������� ��������������� � �����, ��� ������ ��.��.
template <typename T>
vector<double> avgAndAboveAvg(vector<T>& numbers) {
    cout << "������� �������� ��������������� � ���-�� �����, ������ ����..." << endl;
    double sum = 0; //����� �����
    int countNumb = 0; //���-�� �����

    for (int i = 0; i < BUFF_SIZE; i++) {
        if (numbers[i] == 0)
            break;
        sum += numbers[i];
        countNumb++;
    }
    double avg = round(sum / countNumb * pow(10, precision)) / pow(10, precision); ////������� �������� ��������� �� precision ������ ����� �������

    int countAbove = 0;//���-�� �����, ������� �������� ���������������
    for (int i = 0; i < BUFF_SIZE; i++) {
        if (numbers[i] > avg)
            countAbove++;
    }

    vector <double> calculate(BUFF_SIZE); //������ ��� �������� �������� ����. � ���-�� �����, ��� ������ ����
    calculate.at(0) = avg;//1-�� ����� - �������
    calculate.at(1) = countAbove;//2-�� ����� - ���-�� ����� ������ ��������

    std::cout << "�������� ��������� � ������ � ��������������� ������� (������� � ���-�� ����� ������ ��������)" << endl;

    return calculate;
}

//������� ���������� ������� ������� �����
vector<double> listDoubleNumbers(vector<double>& numbers) {
    std::cout << "������� ���-�� ����� ��� �������� �������� ���������������" << endl;
    int countNumb = 0;
    cin >> countNumb;
    cout << "��������� ����� �������� - 1;\n��������� ������� - 2" << endl;
    int choice;
    cin >> choice;
    while ((choice != 1) && (choice != 2)) {
        cout << "������������ ����. ��������� �������" << endl;
        cin >> choice;
    }
    switch (choice) {
        //Random
    case 1: {
        cout << "������� ������� ������� ��� �����" << endl;
        int max;
        cin >> max;
        for (int i = 0; i < countNumb; i++) {
            numbers[i] = round((double)rand() / RAND_MAX * max * pow(10, precision)) / pow(10, precision);
            //numbers[i] = (double)rand() / RAND_MAX * max;
        }
        break;
    }
    case 2: {
        cout << "������� �����" << endl;

        for (int i = 0; i < countNumb; i++) {
            double numb;
            cin >> numb;
            numbers[i] = numb;
        }
    }
    }
    cout << "��������� �����:" << endl;
    for (int i = 0; i < countNumb; i++) {
        cout << numbers[i] << "; ";
    }
    cout << endl;
    //this_thread::sleep_for(chrono::milliseconds(20000));
    return numbers;
}

//������� ���������� ������� ����� �����
vector<int> listIntNumbers(vector<int>& numbers) {
    cout << "������� ���-�� ����� ��� �������� �������� ���������������" << endl;
    int countNumb = 0;
    cin >> countNumb;
    cout << "��������� ����� �������� - 1;\n��������� ������� - 2" << endl;
    int choice;
    cin >> choice;
    while ((choice != 1) && (choice != 2)) {
        cout << "������������ ����. ��������� �������" << endl;
        cin >> choice;
    }
    switch (choice) {
        //Random
    case 1: {
        cout << "������� ������� � ������ ������� ��� ����� (max / low)" << endl;
        int max, low;
        cin >> max;
        cin >> low;
        for (int i = 0; i < countNumb; i++) {
            numbers.push_back(rand() % (max - low) + low);
        }
        break;
    }
    case 2: {
        cout << "������� �����" << endl;

        for (int i = 0; i < countNumb; i++) {
            int numb;
            cin >> numb;
            numbers.push_back(numb);
        }
    }
    }
    cout << "��������� �����:" << endl;
    for (int num : numbers) {
        cout << num << "; ";
    }
    cout << endl;
    return numbers;
}
template <typename Type>
void printVec(vector<Type>& data) {
    for (Type num : data) {
        if (num == 0)
            break;
        cout << num << "; ";
    }
    cout << endl;
}

void ClientData(SOCKET* socket, vector<double>& calculateData) {
    vector<char> recvBuff(BUFF_SIZE * sizeof(double));//������ ��� �������� ���������
    vector<char> sendBuff(BUFF_SIZE * sizeof(double));//������ ��� �������� ���������
    short packet_size = 0;
    char choice;
    bool flag = true;
    while (flag) {

        //���������� ������� �������
        vector<double> sourceData(BUFF_SIZE);
        sourceData = listDoubleNumbers(sourceData);
        //cout << "������ ������� double " << sourceData.size() << endl;

        // ����������� ������ double � ������ char � ������� ��������� �����
        cout << "===========������������ ��������� ������ double --> char ����� ���������===========" << endl;
        sendBuff = doubleToCharVector(sourceData);
        //cout << "������ ������� char " << sendBuff.size() << endl;

        //���������� ������ 
        packet_size = send(*(socket), sendBuff.data(), sendBuff.size(), 0);

        //��������� ������
        if (packet_size == SOCKET_ERROR) {
            cout << endl << "�� ���������� ��������� ������ �� ������. ������# " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            //break;
        }
        else {
            cout << endl << "===========������������ �������� ������ �� ���������...===========" << endl;
        }

        //��������� ������ � ���������� ����
        packet_size = recv(*(socket), recvBuff.data(), recvBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            cout << endl << "���������� �������� ������������ ������ � �������. ������# " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            //break;
        }
        else {

            //������������ ���������� ������ char ������� � double
            cout << "������ ������� char " << recvBuff.size() << endl;
            cout << "===========������������ ��������� ������ char --> double ����� ����������===========" << endl;
            calculateData = charToDoubleVector(recvBuff);
            cout << endl << "������ ������� ���������� � ��������" << endl;
            //cout << "������ ������� double " << calculateData.size() << endl;
            cout << "���������� ������ �� �������:" << endl;
            printVec(calculateData);
            //this_thread::sleep_for(chrono::milliseconds(20000));
        }

        cout << "���������� ������� ������? (y/n) ";
        cin >> choice;
        if (choice == 'n')
            flag = false;
        else {
            singleSend(socket, choice);
        }
    }
}

void ServerData(SOCKET* socket) {
    vector<char> recvBuff(BUFF_SIZE * sizeof(double));//������ ��� �������� ���������
    vector<char> sendBuff(BUFF_SIZE * sizeof(double));//������ ��� �������� ���������
    short packet_size = 0;
    char choice; //����� ������������, ������� �� ��������
    while (true) {

        //�������� ��������� ��������
        packet_size = recv(*(socket), recvBuff.data(), recvBuff.size(), 0); //������������ �� ���� �����, ��� � ������� ������, ������� ������ ���������
        if (packet_size == SOCKET_ERROR) {
            cout << endl << "�� ����� �������� ������ �� �������. ������# " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            break;
        }
        else {
            cout << "=================������ ������ ������ �� ���������=================" << endl;
        }
        cout << "������ ������� char " << recvBuff.size() << endl;

        cout << endl << "=============����������� ������ char --> double...=============" << endl;
        vector<double> calculate(BUFF_SIZE);
        calculate = charToDoubleVector(recvBuff);//������ ��� ������� ������
        cout << "������ ������� double" << calculate.size() << endl;
        printVec(calculate);

        cout << endl << "=============������������ ������...=============" << endl;
        calculate = avgAndAboveAvg(calculate);
        printVec(calculate);

        cout << endl << "=============������ �������������� � char ����� ���������...=============" << endl;
        sendBuff = doubleToCharVector(calculate);
        cout << "������ ������� char " << sendBuff.size() << endl;

        //�������� ������������� �������� ��������� �� �������
        packet_size = send(*(socket), sendBuff.data(), sendBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            cout << endl << "�� ����� ��������� ��������� �������. ������ # " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            break;
        }
        else {
            cout << "������ ������� ���������� � ���������� �������" << endl;
        }

        cout << "���� ����� ������������..." << endl;
    }
}

/*------------------------------������ � ������------------------------------*/

//������������� IP � ������� �������������
void ipInit(int erStat, in_addr& ip_to_num) {
    //������ ������� �����
    erStat = inet_pton(AF_INET, SERVER_IP, &ip_to_num); //������� �������� � ������� �����(C�������� IPv4, ip-����, ��������� �� ���������)

    //��� �������� �������� ������ ������� - ������
    if (erStat <= 0) {
        cout << "Error in IP translation" << endl;
    }
    else {
        cout << "IP init is OK!" << endl;
    }
}

//�������� �������� ����������� ��� ���������� ������
void sockInterfaces(int erStat, WSADATA& wsdata) {
    erStat = WSAStartup(MAKEWORD(2, 2), &wsdata); //������ ������������ ���������� �������

    if (erStat != 0) {
        cout << "Error initialization socket interfaces #" << WSAGetLastError << endl;

    }
    else {
        cout << "Initialization socket interfaces success!" << endl;
    }
}


//�������� ������
void sockInit(SOCKET& Sock) {
    Sock = socket(AF_INET, SOCK_STREAM, 0);

    if (Sock == INVALID_SOCKET) {
        cout << "Error initialization socket #" << WSAGetLastError();
        closesocket(Sock);
        WSACleanup();
    }
    else {
        cout << "Socket initialization is OK" << endl;
    }
}


/*------------------------------C�����------------------------------*/

//�������� �� �������� ������ � ������� (���� IP-����� (������)/���� (������)
void ipPortBind(int erStat, sockaddr_in& info, in_addr& ip_to_num, SOCKET& sock) {
    ZeroMemory(&info, sizeof(info));

    info.sin_family = AF_INET;
    info.sin_addr = ip_to_num;
    info.sin_port = htons(PORT_NUM); //�������������� ����� ����� � ���������� ���

    erStat = bind(sock, (sockaddr*)&info, sizeof(info));

    if (erStat != 0) {
        cout << "Error bind socket to server info#" << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
    }
    else {
        cout << "Binding socket to server info is OK" << endl;
    }
}

void listenPort(int erStat, SOCKET& ServSock) {
    erStat = listen(ServSock, SOMAXCONN); //�����, ����� �����������
    if (erStat != 0) {
        cout << "Error listen #" << WSAGetLastError() << endl;
        closesocket(ServSock);
        WSACleanup();
    }
    else {
        cout << "Listen..." << endl;
    }
}

void acceptConn(sockaddr_in& clientInfo, SOCKET& ClientConn, SOCKET& ServSock) {
    int client_info_size = sizeof(clientInfo);
    ClientConn = accept(ServSock, (sockaddr*)&clientInfo, &client_info_size);

    if (ClientConn == INVALID_SOCKET) {
        cout << "Client detected, but can't connect to a client #" << WSAGetLastError() << endl;
        closesocket(ServSock);
        WSACleanup();
    }
    else {
        cout << "Client connection is success" << endl;
        char clientIP[22];

        inet_ntop(AF_INET, &clientInfo.sin_addr, clientIP, INET_ADDRSTRLEN);

        cout << "Client connected with IP address " << clientIP << endl;
    }
}

/*------------------------------������------------------------------*/

//������������� � ����� ������� �� ������� �������
void ipPortConnect(int erStat, sockaddr_in& servInfo, in_addr& ip_to_num, SOCKET& ClientSock) {
    ZeroMemory(&servInfo, sizeof(servInfo));

    //������� ������ �������
    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(PORT_NUM);

    erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

    if (erStat != 0) {
        cout << "Connection to Server is FAILED. Error # " << WSAGetLastError() << endl;
        closesocket(ClientSock);
        WSACleanup();
    }
    else
        cout << "Connection established SUCCESSFULLY. Ready to send a message to Server" << endl;
}






//case 3: //�������� ����� ��� ���������� 
//
//    serverResponse(&ClientSock, recvBuff, packetSize); //��������� ��������� � ������
//
//    /*----------------------------�������� ��������� �������----------------------------*/
//    int numb;
//    cout << "Your number: ";
//    cin >> numb;
//    sendNumbMessage(&ClientSock, numb, packetSize);
//    if (packetSize == SOCKET_ERROR)
//        flag = false; //��������� ����������
//    else {
//        /*----------------------------�������� ��������� �� �������----------------------------*/
//        serverResponse(&ClientSock, recvBuff, packetSize);
//        if (packetSize == SOCKET_ERROR)
//            flag = false; //��������� ����������
//        else
//            cout << "Menu - 0" << endl;
//    }
//    break;
//
//case 4: //������ � ��������
//
//    serverResponse(&ClientSock, recvBuff, packetSize); //��������� ��������� � ������
//
//    /*----------------------------�������� ��������� �������----------------------------*/
//    cout << "Your number: ";
//    cin >> numb;
//    sendNumbMessage(&ClientSock, numb, packetSize);
//    if (numb == 1) {
//        if (packetSize == SOCKET_ERROR)
//            flag = false; //��������� ����������
//        else {
//            /*----------------------------�������� ��������� �� �������----------------------------*/
//            cout << "We read the signal and calculate its characteristics\nPlease wait..." << endl;
//            serverResponse(&ClientSock, recvBuff, packetSize);
//            cout << "Menu - 0" << endl;
//        }
//    }
//    else
//
//        /*----------------------------�������� ��������� �� �������----------------------------*/
//        serverResponse(&ClientSock, recvBuff, packetSize);