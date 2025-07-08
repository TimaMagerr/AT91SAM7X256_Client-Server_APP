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


//Функция принятия сообщения
void recMessage(SOCKET* sock, vector<char>& buffer, short& packetSize) {
    //cout << "Waiting message from server...\n";
    packetSize = recv(*sock, buffer.data(), buffer.size(), 0);
    if (packetSize == SOCKET_ERROR) {
        cout << "Recv failed: Error#" << WSAGetLastError() << endl;
        closesocket(*sock);
        WSACleanup();
    }
    //else
        //cout << "Сlient recv message!\n";
}

void serverResponse(SOCKET* sock, vector<char>& buffer, short& packetSize) {
    recMessage(sock, buffer, packetSize);
    //cout << "Server response:\n" << buffer.data() << endl;
    //memset(buffer.data(), 0, buffer.size()); //Очищаем буфер
}

void sendNumbMessage(SOCKET* sock, int numb, int packetSize) {
    stringstream sNumb;
    sNumb << numb << endl; //создаем строку с разделителем \n
    string stringNumb = sNumb.str();
    //cout << stringNumb;
    packetSize = send(*sock, stringNumb.c_str(), stringNumb.length(), 0);

    if (packetSize == SOCKET_ERROR) {
        cout << "Send failed: Error#" << WSAGetLastError() << endl;
        closesocket(*sock);
        WSACleanup();
    }
    else {
        cout << "Число отправлено!\n";
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
        cout << endl << "Выбор отправлен" << endl;
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
        cout << endl << "Выбор получен " << endl;
    }
}


// Функция для преобразования вектора double в вектор char
vector<char> doubleToCharVector(const vector<double>& doubles) {
    vector<char> charVector;
    for (const double& d : doubles) {
        // Преобразуем каждое значение double в байты типа char
        //const char* bytes = reinterpret_cast<const char*>(&d);
        const char* bytes = (const char*)(&d);
        // Добавляем байты в вектор char
        charVector.insert(charVector.end(), bytes, bytes + sizeof(double));
    }
    return charVector;
}

// Функция для преобразования вектора int в вектор char
vector<char> intToCharVector(const vector<int>& doubles) {
    vector<char> charVector;
    for (const int& d : doubles) {
        // Преобразуем каждое значение double в байты типа char
        //const char* bytes = reinterpret_cast<const char*>(&d);
        const char* bytes = (const char*)(&d);
        // Добавляем байты в вектор char
        charVector.insert(charVector.end(), bytes, bytes + sizeof(int));
    }
    return charVector;
}

// Функция для преобразования вектора char в вектор double
vector<double> charToDoubleVector(const vector<char>& chars) {
    vector<double> doubleVector;
    size_t numDoubles = chars.size() / sizeof(double);
    for (size_t i = 0; i < numDoubles; ++i) {
        double d;
        // Копируем байты из вектора char в переменную типа double
        memcpy(&d, &chars[i * sizeof(double)], sizeof(double));
        doubleVector.push_back(d);
    }
    return doubleVector;
}

// Функция для преобразования вектора char в вектор int
vector<int> charToIntVector(const vector<char>& chars) {
    vector<int> intVector;
    size_t numInt = chars.size() / sizeof(int);
    for (size_t i = 0; i < numInt; ++i) {
        int d;
        // Копируем байты из вектора char в переменную типа double
        memcpy(&d, &chars[i * sizeof(int)], sizeof(int));
        intVector.push_back(d);
    }
    return intVector;
}

//Функция подсчета среднего арифметического и чисел, что больше ср.ар.
template <typename T>
vector<double> avgAndAboveAvg(vector<T>& numbers) {
    cout << "Подсчет среднего арифметического и кол-ва чисел, больше него..." << endl;
    double sum = 0; //Сумма чисел
    int countNumb = 0; //Кол-во чисел

    for (int i = 0; i < BUFF_SIZE; i++) {
        if (numbers[i] == 0)
            break;
        sum += numbers[i];
        countNumb++;
    }
    double avg = round(sum / countNumb * pow(10, precision)) / pow(10, precision); ////Среднее значение округляем до precision знаков после запятой

    int countAbove = 0;//Кол-во чисел, больших среднего арифметического
    for (int i = 0; i < BUFF_SIZE; i++) {
        if (numbers[i] > avg)
            countAbove++;
    }

    vector <double> calculate(BUFF_SIZE); //Вектор для хранения среднего ариф. и кол-ва чисел, что больше него
    calculate.at(0) = avg;//1-ое число - среднее
    calculate.at(1) = countAbove;//2-ое число - кол-во чисел больше среднего

    std::cout << "Значения добавлены в вектор в соответствующем порядке (среднее и кол-во чисел больше среднего)" << endl;

    return calculate;
}

//Функция заполнения вектора дробных чисел
vector<double> listDoubleNumbers(vector<double>& numbers) {
    std::cout << "Введите кол-во чисел для подсчета среднего арифметического" << endl;
    int countNumb = 0;
    cin >> countNumb;
    cout << "Заполнить числа рандомно - 1;\nЗаполнить вручную - 2" << endl;
    int choice;
    cin >> choice;
    while ((choice != 1) && (choice != 2)) {
        cout << "Некорректный ввод. Повторите попытку" << endl;
        cin >> choice;
    }
    switch (choice) {
        //Random
    case 1: {
        cout << "Введите верхнюю границу для чисел" << endl;
        int max;
        cin >> max;
        for (int i = 0; i < countNumb; i++) {
            numbers[i] = round((double)rand() / RAND_MAX * max * pow(10, precision)) / pow(10, precision);
            //numbers[i] = (double)rand() / RAND_MAX * max;
        }
        break;
    }
    case 2: {
        cout << "Введите числа" << endl;

        for (int i = 0; i < countNumb; i++) {
            double numb;
            cin >> numb;
            numbers[i] = numb;
        }
    }
    }
    cout << "Введенные числа:" << endl;
    for (int i = 0; i < countNumb; i++) {
        cout << numbers[i] << "; ";
    }
    cout << endl;
    //this_thread::sleep_for(chrono::milliseconds(20000));
    return numbers;
}

//Функция заполнения вектора целых чисел
vector<int> listIntNumbers(vector<int>& numbers) {
    cout << "Введите кол-во чисел для подсчета среднего арифметического" << endl;
    int countNumb = 0;
    cin >> countNumb;
    cout << "Заполнить числа рандомно - 1;\nЗаполнить вручную - 2" << endl;
    int choice;
    cin >> choice;
    while ((choice != 1) && (choice != 2)) {
        cout << "Некорректный ввод. Повторите попытку" << endl;
        cin >> choice;
    }
    switch (choice) {
        //Random
    case 1: {
        cout << "Введите верхнюю и нижнюю границу для чисел (max / low)" << endl;
        int max, low;
        cin >> max;
        cin >> low;
        for (int i = 0; i < countNumb; i++) {
            numbers.push_back(rand() % (max - low) + low);
        }
        break;
    }
    case 2: {
        cout << "Введите числа" << endl;

        for (int i = 0; i < countNumb; i++) {
            int numb;
            cin >> numb;
            numbers.push_back(numb);
        }
    }
    }
    cout << "Введенные числа:" << endl;
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
    vector<char> recvBuff(BUFF_SIZE * sizeof(double));//Буффер для принятия сообщений
    vector<char> sendBuff(BUFF_SIZE * sizeof(double));//Буффер для отправки сообщений
    short packet_size = 0;
    char choice;
    bool flag = true;
    while (flag) {

        //Заполнение вектора числами
        vector<double> sourceData(BUFF_SIZE);
        sourceData = listDoubleNumbers(sourceData);
        //cout << "Размер вектора double " << sourceData.size() << endl;

        // Преобразуем вектор double в вектор char и создаем отправной буфер
        cout << "===========Конвертируем побайтово вектор double --> char перед отправкой===========" << endl;
        sendBuff = doubleToCharVector(sourceData);
        //cout << "Размер вектора char " << sendBuff.size() << endl;

        //Отправляем данные 
        packet_size = send(*(socket), sendBuff.data(), sendBuff.size(), 0);

        //Обработка ошибки
        if (packet_size == SOCKET_ERROR) {
            cout << endl << "Не получается отправить данные на сервер. Ошибка# " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            //break;
        }
        else {
            cout << endl << "===========Пользователь отправил данные на обработку...===========" << endl;
        }

        //Принимаем данные в символьном виде
        packet_size = recv(*(socket), recvBuff.data(), recvBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            cout << endl << "Невозможно получить обработанные данные с сервера. Ошибка# " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            //break;
        }
        else {

            //Конвертируем полученный вектор char обратно в double
            cout << "Размер вектора char " << recvBuff.size() << endl;
            cout << "===========Конвертируем побайтово вектор char --> double перед получением===========" << endl;
            calculateData = charToDoubleVector(recvBuff);
            cout << endl << "Данные успешно обработаны и получены" << endl;
            //cout << "Размер вектора double " << calculateData.size() << endl;
            cout << "Актуальные данные по расчету:" << endl;
            printVec(calculateData);
            //this_thread::sleep_for(chrono::milliseconds(20000));
        }

        cout << "Произвести рассчет данных? (y/n) ";
        cin >> choice;
        if (choice == 'n')
            flag = false;
        else {
            singleSend(socket, choice);
        }
    }
}

void ServerData(SOCKET* socket) {
    vector<char> recvBuff(BUFF_SIZE * sizeof(double));//Буффер для принятия сообщений
    vector<char> sendBuff(BUFF_SIZE * sizeof(double));//Буффер для отправки сообщений
    short packet_size = 0;
    char choice; //Выбор пользователя, который мы получили
    while (true) {

        //Принятие сообщения сервером
        packet_size = recv(*(socket), recvBuff.data(), recvBuff.size(), 0); //Зацикливание на этом этапе, ибо я получаю данные, которые сервер обработал
        if (packet_size == SOCKET_ERROR) {
            cout << endl << "Не вышло получить данные от клиента. Ошибка# " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            break;
        }
        else {
            cout << "=================Сервер принял данные на обработку=================" << endl;
        }
        cout << "Размер вектора char " << recvBuff.size() << endl;

        cout << endl << "=============Преобразуем данные char --> double...=============" << endl;
        vector<double> calculate(BUFF_SIZE);
        calculate = charToDoubleVector(recvBuff);//Буффер для решения задачи
        cout << "Размер вектора double" << calculate.size() << endl;
        printVec(calculate);

        cout << endl << "=============Обрабатываем данные...=============" << endl;
        calculate = avgAndAboveAvg(calculate);
        printVec(calculate);

        cout << endl << "=============Делаем преобразование в char перед отправкой...=============" << endl;
        sendBuff = doubleToCharVector(calculate);
        cout << "Размер вектора char " << sendBuff.size() << endl;

        //Отправка обработанного сервером сообщения от клиента
        packet_size = send(*(socket), sendBuff.data(), sendBuff.size(), 0);

        if (packet_size == SOCKET_ERROR) {
            cout << endl << "Не можем отправить сообщение клиенту. Ошибка # " << WSAGetLastError() << endl;
            closesocket(*(socket));
            WSACleanup();
            break;
        }
        else {
            cout << "Данные успешно обработаны и отправлены клиенту" << endl;
        }

        cout << "Ждем выбор пользователя..." << endl;
    }
}

/*------------------------------Сервер и клиент------------------------------*/

//Инициализация IP в битовом представлении
void ipInit(int erStat, in_addr& ip_to_num) {
    //Задаем сетевой адрес
    erStat = inet_pton(AF_INET, SERVER_IP, &ip_to_num); //Функция перевода в битовое число(Cемейство IPv4, ip-шник, указатель на структуру)

    //При возврате значения меньше единицы - ошибка
    if (erStat <= 0) {
        cout << "Error in IP translation" << endl;
    }
    else {
        cout << "IP init is OK!" << endl;
    }
}

//Создание сокетных интерфейсов для дальнейшей работы
void sockInterfaces(int erStat, WSADATA& wsdata) {
    erStat = WSAStartup(MAKEWORD(2, 2), &wsdata); //Запуск программного интерфейса сокетов

    if (erStat != 0) {
        cout << "Error initialization socket interfaces #" << WSAGetLastError << endl;

    }
    else {
        cout << "Initialization socket interfaces success!" << endl;
    }
}


//Создание сокета
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


/*------------------------------Cервер------------------------------*/

//Проверка на привязку сокета к серверу (пара IP-адрес (клиент)/Порт (сервер)
void ipPortBind(int erStat, sockaddr_in& info, in_addr& ip_to_num, SOCKET& sock) {
    ZeroMemory(&info, sizeof(info));

    info.sin_family = AF_INET;
    info.sin_addr = ip_to_num;
    info.sin_port = htons(PORT_NUM); //Идентифицирует номер порта в побайтовый код

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
    erStat = listen(ServSock, SOMAXCONN); //Сокет, число подключений
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

/*------------------------------Клиент------------------------------*/

//Присоединение к порту сервера со стороны клиента
void ipPortConnect(int erStat, sockaddr_in& servInfo, in_addr& ip_to_num, SOCKET& ClientSock) {
    ZeroMemory(&servInfo, sizeof(servInfo));

    //Задание адреса сервера
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






//case 3: //Отправка числа для увеличения 
//
//    serverResponse(&ClientSock, recvBuff, packetSize); //Принимаем сообщение о выборе
//
//    /*----------------------------Отправка сообщения серверу----------------------------*/
//    int numb;
//    cout << "Your number: ";
//    cin >> numb;
//    sendNumbMessage(&ClientSock, numb, packetSize);
//    if (packetSize == SOCKET_ERROR)
//        flag = false; //Закрываем соединение
//    else {
//        /*----------------------------Принятие сообщения от сервера----------------------------*/
//        serverResponse(&ClientSock, recvBuff, packetSize);
//        if (packetSize == SOCKET_ERROR)
//            flag = false; //Закрываем соединение
//        else
//            cout << "Menu - 0" << endl;
//    }
//    break;
//
//case 4: //Работа с сигналом
//
//    serverResponse(&ClientSock, recvBuff, packetSize); //Принимаем сообщение о выборе
//
//    /*----------------------------Отправка сообщения серверу----------------------------*/
//    cout << "Your number: ";
//    cin >> numb;
//    sendNumbMessage(&ClientSock, numb, packetSize);
//    if (numb == 1) {
//        if (packetSize == SOCKET_ERROR)
//            flag = false; //Закрываем соединение
//        else {
//            /*----------------------------Принятие сообщения от сервера----------------------------*/
//            cout << "We read the signal and calculate its characteristics\nPlease wait..." << endl;
//            serverResponse(&ClientSock, recvBuff, packetSize);
//            cout << "Menu - 0" << endl;
//        }
//    }
//    else
//
//        /*----------------------------Принятие сообщения от сервера----------------------------*/
//        serverResponse(&ClientSock, recvBuff, packetSize);