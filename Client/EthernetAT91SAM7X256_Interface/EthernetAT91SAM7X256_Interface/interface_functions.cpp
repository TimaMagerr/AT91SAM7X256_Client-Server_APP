#include "Interface.h"
#include "libraries.h"
#include "functions.h"
#include "parameters.h"


/*************************************************Функции подключения и работы с сокетами**************************************************/
System::Void EthernetAT91SAM7X256Interface::Interface::ipInit(int erStat, in_addr& ip_to_num)
{
    //Задаем сетевой адрес
    erStat = inet_pton(AF_INET, SERVER_IP, &ip_to_num); //Функция перевода в битовое число(Cемейство IPv4, ip-шник, указатель на структуру)

    //При возврате значения меньше единицы - ошибка
    if (erStat <= 0) {
        // Выводим сообщение об ошибке
        connection_status_label->Text += "Error in IP translation\n";
        connection_status_label->ForeColor = Color::Red;
    }
    else {
        // Выводим сообщение об успешной инициализации
        connection_status_label->Text += "IP init is OK!\n";
        connection_status_label->ForeColor = Color::Green;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::sockInterfaces(int erStat, WSADATA& wsdata)
{
    erStat = WSAStartup(MAKEWORD(2, 2), &wsdata); //Запуск программного интерфейса сокетов

    if (erStat != 0) {
        // Преобразуем идентификатор ошибки в строку
        std::string errorMsg = "Error initialization socket interfaces #" + std::to_string(WSAGetLastError());

        // Преобразуем строку в System::String с добавлением перехода на новую строку
        System::String^ errorMessage = gcnew System::String((errorMsg + "\n").c_str());

        // Устанавливаем текст в элемент Label
        connection_status_label->Text += errorMessage;
        connection_status_label->ForeColor = Color::Red;
    }
    else {

        // Устанавливаем текст в элемент Label
        connection_status_label->Text += "Initialization socket interfaces success!\n";
        connection_status_label->ForeColor = Color::Green;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::sockInit(SOCKET& Sock)
{
    Sock = socket(AF_INET, SOCK_STREAM, 0);

    if (Sock == INVALID_SOCKET) {
        // Преобразуем идентификатор ошибки в строку
        std::string errorMsg = "Error initialization socket #" + std::to_string(WSAGetLastError());

        // Преобразуем строку в System::String с добавлением перехода на новую строку
        System::String^ errorMessage = gcnew System::String((errorMsg + "\n").c_str());

        // Устанавливаем текст в элемент Label
        connection_status_label->Text = errorMessage;
        connection_status_label->ForeColor = Color::Red;

        // Закрываем сокет и освобождаем ресурсы
        closesocket(Sock);
        WSACleanup();
    }
    else {
        // Устанавливаем текст в элемент Label с добавлением перехода на новую строку
        connection_status_label->Text += "Socket initialization is OK\n";
        connection_status_label->ForeColor = Color::Green;
        
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::ipPortConnect(int erStat, sockaddr_in& servInfo, in_addr& ip_to_num, SOCKET& ClientSock)
{
    ZeroMemory(&servInfo, sizeof(servInfo));

    servInfo.sin_family = AF_INET;
    servInfo.sin_addr = ip_to_num;
    servInfo.sin_port = htons(PORT_NUM);

    erStat = connect(ClientSock, (sockaddr*)&servInfo, sizeof(servInfo));

    if (erStat != 0) {
        // Преобразуем идентификатор ошибки в строку
        std::string errorMess = "Connection to Server is FAILED. Error # " + std::to_string(WSAGetLastError());

        //Теперь преобразуем в управляемый String^
        System::String^ errorMessage = gcnew System::String((errorMess + '\n').c_str());

        //Выводим в Label
        connection_status_label->Text += errorMessage;
        connection_status_label->ForeColor = Color::Red;

        closesocket(ClientSock);
        WSACleanup();
        exit(0);
    }
    else {
        connection_status_label->Text += "Connection established SUCCESSFULLY. Ready to work with Server\n";
        connection_status_label->ForeColor = Color::Green;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::open_conn()
{
    if (clientRunning) {
        // Клиент уже запущен, выводим сообщение
        MessageBox::Show("Client created the connection!", "Attention!");
        return;
    }

    //Задаем пустое окошко
    connection_status_label->Text = "";

    connection_status_label->Text = "==============Client==============\n";

    //Стринговый формат передаваемых данных в биты
    in_addr ip_to_num;
    ipInit(erStat, ip_to_num);

    // Инициализация WinSock
    WSADATA wsData;
    sockInterfaces(erStat, wsData);

    // Инициализация сокета
    SOCKET ClientSock;
    sockInit(ClientSock);

    m_ClientSock = ClientSock;

    // Присоединение к серверу
    sockaddr_in servInfo;
    ipPortConnect(erStat, servInfo, ip_to_num, ClientSock);

    //Принимаем сообщение о конфигурации пинов
    String^ recvMessage = recMessageBox(&ClientSock, m_packet_size); //Принятое сообщение
    if (recvMessage->IndexOf("not") == -1) {
        radioButton28A_O_0->Checked = true;
        radioButton29A_O_0->Checked = true;
        radioButton30A_O_0->Checked = true;

        radioButtonB28_O_0->Checked = true;
        radioButtonB29_O_0->Checked = true;
        radioButtonB30_O_0->Checked = true;
    }
    else
        MessageBox::Show("Configure the ports manually!", "Attention");
    clientRunning = true; //Соединение установлено
}

System::Void EthernetAT91SAM7X256Interface::Interface::close_conn(SOCKET ClientConn)
{
    sendNumbMessage(&ClientConn, 0, m_packet_size); //Конфигурируем пины по умолчанию
    threadAbort(clientConnThread); //Завершаем поток клиентского соединения
    threadAbort(signalProcessThread); //Завершаем поток считывания сигнала с ножки
    closesocket(ClientConn);
    WSACleanup();
    clientRunning = false; //Клиент не активен

}

/****************************************************Функции дополнения и обновления лейблов *****************************************************/
System::Void EthernetAT91SAM7X256Interface::Interface::AppendLabel(System::Windows::Forms::Label^ label, System::String^ text)
{
    if (label->InvokeRequired) {
        // Если вызов из другого потока, используем метод Invoke для безопасного доступа к элементу управления
        label->Invoke(gcnew Action<System::Windows::Forms::Label^, System::String^>(this, &EthernetAT91SAM7X256Interface::Interface::AppendLabel), label, text);
    }
    else {
        // Добавляем текст к текущему тексту в элементе Label
        label->Text += text;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::UpdateLabel(System::Windows::Forms::Label^ label, System::String^ text)
{
    if (label->InvokeRequired) {
        // Если вызов из другого потока, используем метод Invoke для безопасного доступа к элементу управления
        label->Invoke(gcnew Action<System::Windows::Forms::Label^, System::String^>(this, &EthernetAT91SAM7X256Interface::Interface::UpdateLabel), label, text);
    }
    else {
        // Обновляем текст в элементе Label
        label->Text = text;
    }
}

/**********************Функция уничтожения потока, если он существует************************/
System::Void EthernetAT91SAM7X256Interface::Interface::threadAbort(System::Threading::Thread^ thread) {
    if (thread != nullptr && thread->IsAlive)
        thread->Abort();
}

/******************************************************Функции обмена данными**********************************************************/
System::Void EthernetAT91SAM7X256Interface::Interface::sendNumbMessage(SOCKET* sock, int numb, short int packetSize) {
    stringstream sNumb;
    sNumb << numb << endl; //создаем строку с разделителем \n
    string stringNumb = sNumb.str();
    packetSize = send(*sock, stringNumb.c_str(), stringNumb.length(), 0);

    if (packetSize == SOCKET_ERROR) {
       close_conn(*sock);
       std::string error = "Send failed: Error#" + std::to_string(WSAGetLastError());
       System::String^ error_message = gcnew System::String((error + '\n').c_str());
    }
    /*else
        MessageBox::Show("The request was successfully send!", "Attention!");*/
}

System::Void EthernetAT91SAM7X256Interface::Interface::sendCharMessage(String^ message, short int packetSize) {

    // Создаем контекст маршалинга
    msclr::interop::marshal_context context;

    // Преобразуем System::String^ в char* 
    const char* buffer = context.marshal_as<const char*>(message);

    packetSize = send(m_ClientSock, buffer, message->Length, 0);

    if (packetSize == SOCKET_ERROR) {
        close_conn(m_ClientSock);
        std::string error = "Send failed: Error#" + std::to_string(WSAGetLastError());
        System::String^ error_message = gcnew System::String((error + '\n').c_str());
        MessageBox::Show(error_message, "Attention!");
    }
   else
        MessageBox::Show("The request was successfully send!", "Attention!");
}

//Функция принятия сообщения
System::Void EthernetAT91SAM7X256Interface::Interface::recMessageLabel(SOCKET* sock, short int packetSize, Label^ label) {
    char buffer_recv[BUFF_SIZE]; // Буфер для принятия данных
    memset(buffer_recv, 0, sizeof(buffer_recv)); //Очистка буфера перед принятием данных
    packetSize = recv(*sock, buffer_recv, sizeof(buffer_recv), 0); // Используем sizeof
    if (packetSize == SOCKET_ERROR) {
        std::string error = "Error# " + std::to_string(WSAGetLastError());
        String^ errorMessage = gcnew System::String(error.c_str());
        MessageBox::Show(errorMessage, "Attention!");
    }
    else {
        // Преобразование массива char в строку .NET
        MessageBox::Show("Data successfully received!", "Attention!");
        String^ receivedString = gcnew String(buffer_recv, 0, sizeof(buffer_recv)); // Используем packetSize
        UpdateLabel(label, receivedString);
        label->ForeColor = Color::Black;
    }
}

//Функция принятия сообщения
System::String^ EthernetAT91SAM7X256Interface::Interface::recMessageBox(SOCKET* sock, short int packetSize) {
    char buffer_recv[BUFF_SIZE]; // Буфер для принятия данных
    memset(buffer_recv, 0, sizeof(buffer_recv)); //Очистка буфера перед принятием данных
    packetSize = recv(*sock, buffer_recv, sizeof(buffer_recv), 0); // Используем sizeof
    if (packetSize == SOCKET_ERROR) {
        std::string error = "Error# " + std::to_string(WSAGetLastError());
        String^ errorMessage = gcnew System::String(error.c_str());
        MessageBox::Show(errorMessage, "Attention!");
        close_conn(*sock);
        return errorMessage;
    }
    else {
        // Преобразование массива char в строку .NET
        String^ receivedString = gcnew String(buffer_recv, 0, sizeof(buffer_recv)); // Используем packetSize
        MessageBox::Show(receivedString, "Attention!"); //Выводим сообщение, что все окей
        return receivedString;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::infoFromServer(SOCKET* sock, short int packet_size, short int state, Label^ label) {
    //state отвечает за информацию, что мы передаем
    sendNumbMessage(sock, state, packet_size);
    recMessageLabel(sock, packet_size, label);
}

System::Void EthernetAT91SAM7X256Interface::Interface::radio_button_set(RadioButton^ r_Input_New, RadioButton^ r_Output_0_New, RadioButton^ r_Output_1_New,
    RadioButton^ r_Input_Cur, RadioButton^ r_Output_0_Cur, RadioButton^ r_Output_1_Cur,
    String^ message1, String^ message2, String^ message3) {

    r_Input_Cur->Enabled = true, r_Output_0_Cur->Enabled = true, r_Output_1_Cur->Enabled = true;

    if (r_Input_New->Checked) {
        sendCharMessage(message1, m_packet_size);
        r_Input_Cur->Checked = true;
        r_Input_Cur->Enabled = false, r_Output_0_Cur->Enabled = false, r_Output_1_Cur->Enabled = false; //Делаем кнопки неактивными
    }
    else if (r_Output_0_New->Checked) {
        sendCharMessage(message2, m_packet_size);
        r_Output_0_Cur->Checked = true;
        r_Input_Cur->Enabled = false, r_Output_0_Cur->Enabled = false, r_Output_1_Cur->Enabled = false; //Делаем кнопки неактивными
    }
    else if (r_Output_1_New->Checked) {
        sendCharMessage(message3, m_packet_size);
        r_Output_1_Cur->Checked = true;
        r_Input_Cur->Enabled = false, r_Output_0_Cur->Enabled = false, r_Output_1_Cur->Enabled = false; //Делаем кнопки неактивными    
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::ShowWaitingAnimation()
{
    string text = "Waiting";
    int dotCount = 0;

    while (true)
    {
        /*std::string error = "Send failed: Error#" + std::to_string(WSAGetLastError());
        System::String^ error_message = gcnew System::String((error + '\n').c_str());*/

        // Обновляем текст label_data_signal
        text+= "."; //Добавляем точку
        String^ action_text = gcnew System::String(text.c_str());

        UpdateLabel(label_data_signal, action_text);

        // Увеличиваем количество точек
        dotCount += 1;

        // Пауза в 0.5 секунды
        System::Threading::Thread::Sleep(500);
        if(dotCount == 3)
            // Сбрасываем text для следующей итерации
            text = "Waiting";
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPin(String^ letter, int number, int time, RadioButton^ radioButton)
{
    SOCKET client = m_ClientSock;
    if (radioButton->Checked != true) //Если не стоит флажок конфигурации на вход
    {
        MessageBox::Show("You need to configure this pin as an input", "Attention!");
        stopWaiting = false;
        return;
    }
    else {
        UpdateLabel(label_data_signal, "Waiting...");
        sendNumbMessage(&client, 4, m_packet_size); //Переходим в состояние 4
        sendCharMessage(letter +";" + number + ";" + time + "\n", m_packet_size); //Состояние 4 - для МК - это работа с входным сигналом
        //chartData();
        //Функция ниже раньше ждала структуру данных, чтобы вывести на label_data_signal, тебе же надо, чтобы данные в реальном времени приходили на тестовое окошко
        // Завтра надо отладить:
        // 1. Конфигурируешь пин, как входной
        // 2. Прикладываешь щуп со ступенчатым сигналом
        // 3. Ловишь и смотришь, как приходят данные
        recMessageLabel(&client, m_packet_size, label_data_signal); //Ждем, пока обработаются данные и выводим их на экран
        //recMessageLabel(&client, m_packet_size, label_data_signal); //Ждем, пока обработаются данные и выводим их на экран
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::chartData()
{
    SOCKET client = m_ClientSock;
    int chart_dot_period; //Переменная хранит точку 1 или 0
    int chart_time; //Переменная хранит время для точки выше

    //Очищаем коллекции для новых данных
    time->Clear();
    data_dots->Clear();

    bool flag = true;

    // Создаем буфер для принятых данных
    char buffer[BUFF_SIZE];

    std::string test;
    while (flag) {
        memset(buffer, 0, sizeof(buffer));
        m_packet_size = recv(client, buffer, sizeof(buffer), 0);

        //Буфер преобразуем в строку
        std::string message(buffer, m_packet_size);

        if (m_packet_size == SOCKET_ERROR) {
            std::string error = "Ошибка получения числа# " + std::to_string(WSAGetLastError());
            String^ errorMessage = gcnew System::String((error + '\n').c_str());
            MessageBox::Show(errorMessage, "Внимание!");
            close_conn(client);
            return; // Если произошла ошибка приема, завершаем функцию
        }
        else if (message.find("END") != std::string::npos) { //Принимаем сообщения с временем и состоянием 1 или 0
            String^ receivedString = gcnew String(buffer, 0, sizeof(buffer)); // Используем packetSize
            //UpdateLabel(label_test, receivedString);
            std::string error = "Данные приняты, кол-во элементов массива времени и точек: " + std::to_string(time->Count) + "; " + std::to_string(data_dots->Count);
            String^ errorMessage = gcnew System::String(error.c_str());
            MessageBox::Show(errorMessage, "Внимание!");
        
            flag = false;
        }
        else {
            //Ищем разделитель
            size_t delimeterPos = message.find(';');
            //Если разделитель найден
            if (delimeterPos != std::string::npos) {
                //получаем 1 или 0
                String^ receivedString = gcnew String(buffer, 0, sizeof(buffer)); // Используем packetSize
                //MessageBox::Show(receivedString, "Atention!");
                //UpdateLabel(label_test, receivedString);
                chart_dot_period = std::stod(message.substr(0, delimeterPos));
                data_dots->Add(chart_dot_period); //добавляем точку в лист
                //и присваиваем время
                chart_time = std::stoi(message.substr(delimeterPos + 1));
                time->Add(chart_time); //добавляем время в лист
            }
            else
                MessageBox::Show("Error", "Attention!");

        }
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadA()
{
    int time = static_cast<int>(numericUpDown_time->Value); //Считываем время с селектора чисел
    SOCKET client = m_ClientSock;
    short int number = static_cast<int>(numericUpDownPA->Value); //Считываем число с селектора пинов PA
    if (number == 28) {
        signalProcessPin("A", 28, time, radioButton28A_I);
        //chartData();
    }
    else if (number == 29) {
        signalProcessPin("A", 29, time, radioButton29A_I);
        //chartData();
    }
    else if (number == 30) {
        //chartData();
        signalProcessPin("A", 30, time, radioButton30A_I);
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadB()
{
    int time = static_cast<int>(numericUpDown_time->Value); //Считываем время с селектора чисел
    SOCKET client = m_ClientSock;
    short int number = static_cast<int>(numericUpDownPB->Value); //Считываем число с селектора пинов PA
    if (number == 28) {
        signalProcessPin("B", 28, time, radioButtonB28_I);
        //chartData();
    }
    else if (number == 29) {
        signalProcessPin("B", 29, time, radioButtonB29_I);
        //chartData();
    }
    else if (number == 30) {

        signalProcessPin("B", 30, time, radioButtonB30_I);
        //chartData();
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::UpdateChart(List<int>^ time, List<int>^ data_dots)
{
    // Проверка на корректность введенных данных
    if ((time->Count != data_dots->Count) || (time->Count == 0 || data_dots->Count == 0))
    {
        MessageBox::Show("Количество точек времени и данных не совпадает или данных нет!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    // Преобразование данных из C++/CLI в стандартный C++
    std::vector<int> std_time;
    for (int i = 0; i < time->Count; ++i)
    {
        std_time.push_back(time[i]);
    }

    std::vector<int> std_data_dots;
    for (int i = 0; i < data_dots->Count; ++i)
    {
        std_data_dots.push_back(data_dots[i]);
    }

    // Создание точек для графика
    System::Windows::Forms::DataVisualization::Charting::Series^ series = gcnew System::Windows::Forms::DataVisualization::Charting::Series();
    series->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;

    for (size_t i = 0; i < std_time.size(); ++i)
    {
        // Добавление точки с координатой времени и значения данных
        series->Points->AddXY(std_time[i], std_data_dots[i]);
    }

    // Добавление серии на график
    chart1->Series->Clear(); // Очистка предыдущих серий
    chart1->Series->Add(series);

    // Настройка осей и названия графика (при необходимости)
    chart1->ChartAreas[0]->AxisX->Title = "Время";
    chart1->ChartAreas[0]->AxisY->Title = "Данные";
    chart1->Titles->Add("График данных");
}