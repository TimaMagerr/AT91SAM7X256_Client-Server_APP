#include "Interface.h"
#include "libraries.h"
#include "functions.h"
#include "parameters.h"


/*************************************************������� ����������� � ������ � ��������**************************************************/
System::Void EthernetAT91SAM7X256Interface::Interface::ipInit(int erStat, in_addr& ip_to_num)
{
    //������ ������� �����
    erStat = inet_pton(AF_INET, SERVER_IP, &ip_to_num); //������� �������� � ������� �����(C�������� IPv4, ip-����, ��������� �� ���������)

    //��� �������� �������� ������ ������� - ������
    if (erStat <= 0) {
        // ������� ��������� �� ������
        connection_status_label->Text += "Error in IP translation\n";
        connection_status_label->ForeColor = Color::Red;
    }
    else {
        // ������� ��������� �� �������� �������������
        connection_status_label->Text += "IP init is OK!\n";
        connection_status_label->ForeColor = Color::Green;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::sockInterfaces(int erStat, WSADATA& wsdata)
{
    erStat = WSAStartup(MAKEWORD(2, 2), &wsdata); //������ ������������ ���������� �������

    if (erStat != 0) {
        // ����������� ������������� ������ � ������
        std::string errorMsg = "Error initialization socket interfaces #" + std::to_string(WSAGetLastError());

        // ����������� ������ � System::String � ����������� �������� �� ����� ������
        System::String^ errorMessage = gcnew System::String((errorMsg + "\n").c_str());

        // ������������� ����� � ������� Label
        connection_status_label->Text += errorMessage;
        connection_status_label->ForeColor = Color::Red;
    }
    else {

        // ������������� ����� � ������� Label
        connection_status_label->Text += "Initialization socket interfaces success!\n";
        connection_status_label->ForeColor = Color::Green;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::sockInit(SOCKET& Sock)
{
    Sock = socket(AF_INET, SOCK_STREAM, 0);

    if (Sock == INVALID_SOCKET) {
        // ����������� ������������� ������ � ������
        std::string errorMsg = "Error initialization socket #" + std::to_string(WSAGetLastError());

        // ����������� ������ � System::String � ����������� �������� �� ����� ������
        System::String^ errorMessage = gcnew System::String((errorMsg + "\n").c_str());

        // ������������� ����� � ������� Label
        connection_status_label->Text = errorMessage;
        connection_status_label->ForeColor = Color::Red;

        // ��������� ����� � ����������� �������
        closesocket(Sock);
        WSACleanup();
    }
    else {
        // ������������� ����� � ������� Label � ����������� �������� �� ����� ������
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
        // ����������� ������������� ������ � ������
        std::string errorMess = "Connection to Server is FAILED. Error # " + std::to_string(WSAGetLastError());

        //������ ����������� � ����������� String^
        System::String^ errorMessage = gcnew System::String((errorMess + '\n').c_str());

        //������� � Label
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
        // ������ ��� �������, ������� ���������
        MessageBox::Show("Client created the connection!", "Attention!");
        return;
    }

    //������ ������ ������
    connection_status_label->Text = "";

    connection_status_label->Text = "==============Client==============\n";

    //���������� ������ ������������ ������ � ����
    in_addr ip_to_num;
    ipInit(erStat, ip_to_num);

    // ������������� WinSock
    WSADATA wsData;
    sockInterfaces(erStat, wsData);

    // ������������� ������
    SOCKET ClientSock;
    sockInit(ClientSock);

    m_ClientSock = ClientSock;

    // ������������� � �������
    sockaddr_in servInfo;
    ipPortConnect(erStat, servInfo, ip_to_num, ClientSock);

    //��������� ��������� � ������������ �����
    String^ recvMessage = recMessageBox(&ClientSock, m_packet_size); //�������� ���������
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
    clientRunning = true; //���������� �����������
}

System::Void EthernetAT91SAM7X256Interface::Interface::close_conn(SOCKET ClientConn)
{
    sendNumbMessage(&ClientConn, 0, m_packet_size); //������������� ���� �� ���������
    threadAbort(clientConnThread); //��������� ����� ����������� ����������
    threadAbort(signalProcessThread); //��������� ����� ���������� ������� � �����
    closesocket(ClientConn);
    WSACleanup();
    clientRunning = false; //������ �� �������

}

/****************************************************������� ���������� � ���������� ������� *****************************************************/
System::Void EthernetAT91SAM7X256Interface::Interface::AppendLabel(System::Windows::Forms::Label^ label, System::String^ text)
{
    if (label->InvokeRequired) {
        // ���� ����� �� ������� ������, ���������� ����� Invoke ��� ����������� ������� � �������� ����������
        label->Invoke(gcnew Action<System::Windows::Forms::Label^, System::String^>(this, &EthernetAT91SAM7X256Interface::Interface::AppendLabel), label, text);
    }
    else {
        // ��������� ����� � �������� ������ � �������� Label
        label->Text += text;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::UpdateLabel(System::Windows::Forms::Label^ label, System::String^ text)
{
    if (label->InvokeRequired) {
        // ���� ����� �� ������� ������, ���������� ����� Invoke ��� ����������� ������� � �������� ����������
        label->Invoke(gcnew Action<System::Windows::Forms::Label^, System::String^>(this, &EthernetAT91SAM7X256Interface::Interface::UpdateLabel), label, text);
    }
    else {
        // ��������� ����� � �������� Label
        label->Text = text;
    }
}

/**********************������� ����������� ������, ���� �� ����������************************/
System::Void EthernetAT91SAM7X256Interface::Interface::threadAbort(System::Threading::Thread^ thread) {
    if (thread != nullptr && thread->IsAlive)
        thread->Abort();
}

/******************************************************������� ������ �������**********************************************************/
System::Void EthernetAT91SAM7X256Interface::Interface::sendNumbMessage(SOCKET* sock, int numb, short int packetSize) {
    stringstream sNumb;
    sNumb << numb << endl; //������� ������ � ������������ \n
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

    // ������� �������� ����������
    msclr::interop::marshal_context context;

    // ����������� System::String^ � char* 
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

//������� �������� ���������
System::Void EthernetAT91SAM7X256Interface::Interface::recMessageLabel(SOCKET* sock, short int packetSize, Label^ label) {
    char buffer_recv[BUFF_SIZE]; // ����� ��� �������� ������
    memset(buffer_recv, 0, sizeof(buffer_recv)); //������� ������ ����� ��������� ������
    packetSize = recv(*sock, buffer_recv, sizeof(buffer_recv), 0); // ���������� sizeof
    if (packetSize == SOCKET_ERROR) {
        std::string error = "Error# " + std::to_string(WSAGetLastError());
        String^ errorMessage = gcnew System::String(error.c_str());
        MessageBox::Show(errorMessage, "Attention!");
    }
    else {
        // �������������� ������� char � ������ .NET
        MessageBox::Show("Data successfully received!", "Attention!");
        String^ receivedString = gcnew String(buffer_recv, 0, sizeof(buffer_recv)); // ���������� packetSize
        UpdateLabel(label, receivedString);
        label->ForeColor = Color::Black;
    }
}

//������� �������� ���������
System::String^ EthernetAT91SAM7X256Interface::Interface::recMessageBox(SOCKET* sock, short int packetSize) {
    char buffer_recv[BUFF_SIZE]; // ����� ��� �������� ������
    memset(buffer_recv, 0, sizeof(buffer_recv)); //������� ������ ����� ��������� ������
    packetSize = recv(*sock, buffer_recv, sizeof(buffer_recv), 0); // ���������� sizeof
    if (packetSize == SOCKET_ERROR) {
        std::string error = "Error# " + std::to_string(WSAGetLastError());
        String^ errorMessage = gcnew System::String(error.c_str());
        MessageBox::Show(errorMessage, "Attention!");
        close_conn(*sock);
        return errorMessage;
    }
    else {
        // �������������� ������� char � ������ .NET
        String^ receivedString = gcnew String(buffer_recv, 0, sizeof(buffer_recv)); // ���������� packetSize
        MessageBox::Show(receivedString, "Attention!"); //������� ���������, ��� ��� ����
        return receivedString;
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::infoFromServer(SOCKET* sock, short int packet_size, short int state, Label^ label) {
    //state �������� �� ����������, ��� �� ��������
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
        r_Input_Cur->Enabled = false, r_Output_0_Cur->Enabled = false, r_Output_1_Cur->Enabled = false; //������ ������ �����������
    }
    else if (r_Output_0_New->Checked) {
        sendCharMessage(message2, m_packet_size);
        r_Output_0_Cur->Checked = true;
        r_Input_Cur->Enabled = false, r_Output_0_Cur->Enabled = false, r_Output_1_Cur->Enabled = false; //������ ������ �����������
    }
    else if (r_Output_1_New->Checked) {
        sendCharMessage(message3, m_packet_size);
        r_Output_1_Cur->Checked = true;
        r_Input_Cur->Enabled = false, r_Output_0_Cur->Enabled = false, r_Output_1_Cur->Enabled = false; //������ ������ �����������    
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

        // ��������� ����� label_data_signal
        text+= "."; //��������� �����
        String^ action_text = gcnew System::String(text.c_str());

        UpdateLabel(label_data_signal, action_text);

        // ����������� ���������� �����
        dotCount += 1;

        // ����� � 0.5 �������
        System::Threading::Thread::Sleep(500);
        if(dotCount == 3)
            // ���������� text ��� ��������� ��������
            text = "Waiting";
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPin(String^ letter, int number, int time, RadioButton^ radioButton)
{
    SOCKET client = m_ClientSock;
    if (radioButton->Checked != true) //���� �� ����� ������ ������������ �� ����
    {
        MessageBox::Show("You need to configure this pin as an input", "Attention!");
        stopWaiting = false;
        return;
    }
    else {
        UpdateLabel(label_data_signal, "Waiting...");
        sendNumbMessage(&client, 4, m_packet_size); //��������� � ��������� 4
        sendCharMessage(letter +";" + number + ";" + time + "\n", m_packet_size); //��������� 4 - ��� �� - ��� ������ � ������� ��������
        //chartData();
        //������� ���� ������ ����� ��������� ������, ����� ������� �� label_data_signal, ���� �� ����, ����� ������ � �������� ������� ��������� �� �������� ������
        // ������ ���� ��������:
        // 1. �������������� ���, ��� �������
        // 2. ������������� ��� �� ����������� ��������
        // 3. ������ � ��������, ��� �������� ������
        recMessageLabel(&client, m_packet_size, label_data_signal); //����, ���� ������������ ������ � ������� �� �� �����
        //recMessageLabel(&client, m_packet_size, label_data_signal); //����, ���� ������������ ������ � ������� �� �� �����
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::chartData()
{
    SOCKET client = m_ClientSock;
    int chart_dot_period; //���������� ������ ����� 1 ��� 0
    int chart_time; //���������� ������ ����� ��� ����� ����

    //������� ��������� ��� ����� ������
    time->Clear();
    data_dots->Clear();

    bool flag = true;

    // ������� ����� ��� �������� ������
    char buffer[BUFF_SIZE];

    std::string test;
    while (flag) {
        memset(buffer, 0, sizeof(buffer));
        m_packet_size = recv(client, buffer, sizeof(buffer), 0);

        //����� ����������� � ������
        std::string message(buffer, m_packet_size);

        if (m_packet_size == SOCKET_ERROR) {
            std::string error = "������ ��������� �����# " + std::to_string(WSAGetLastError());
            String^ errorMessage = gcnew System::String((error + '\n').c_str());
            MessageBox::Show(errorMessage, "��������!");
            close_conn(client);
            return; // ���� ��������� ������ ������, ��������� �������
        }
        else if (message.find("END") != std::string::npos) { //��������� ��������� � �������� � ���������� 1 ��� 0
            String^ receivedString = gcnew String(buffer, 0, sizeof(buffer)); // ���������� packetSize
            //UpdateLabel(label_test, receivedString);
            std::string error = "������ �������, ���-�� ��������� ������� ������� � �����: " + std::to_string(time->Count) + "; " + std::to_string(data_dots->Count);
            String^ errorMessage = gcnew System::String(error.c_str());
            MessageBox::Show(errorMessage, "��������!");
        
            flag = false;
        }
        else {
            //���� �����������
            size_t delimeterPos = message.find(';');
            //���� ����������� ������
            if (delimeterPos != std::string::npos) {
                //�������� 1 ��� 0
                String^ receivedString = gcnew String(buffer, 0, sizeof(buffer)); // ���������� packetSize
                //MessageBox::Show(receivedString, "Atention!");
                //UpdateLabel(label_test, receivedString);
                chart_dot_period = std::stod(message.substr(0, delimeterPos));
                data_dots->Add(chart_dot_period); //��������� ����� � ����
                //� ����������� �����
                chart_time = std::stoi(message.substr(delimeterPos + 1));
                time->Add(chart_time); //��������� ����� � ����
            }
            else
                MessageBox::Show("Error", "Attention!");

        }
    }
}

System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadA()
{
    int time = static_cast<int>(numericUpDown_time->Value); //��������� ����� � ��������� �����
    SOCKET client = m_ClientSock;
    short int number = static_cast<int>(numericUpDownPA->Value); //��������� ����� � ��������� ����� PA
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
    int time = static_cast<int>(numericUpDown_time->Value); //��������� ����� � ��������� �����
    SOCKET client = m_ClientSock;
    short int number = static_cast<int>(numericUpDownPB->Value); //��������� ����� � ��������� ����� PA
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
    // �������� �� ������������ ��������� ������
    if ((time->Count != data_dots->Count) || (time->Count == 0 || data_dots->Count == 0))
    {
        MessageBox::Show("���������� ����� ������� � ������ �� ��������� ��� ������ ���!", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return;
    }

    // �������������� ������ �� C++/CLI � ����������� C++
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

    // �������� ����� ��� �������
    System::Windows::Forms::DataVisualization::Charting::Series^ series = gcnew System::Windows::Forms::DataVisualization::Charting::Series();
    series->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;

    for (size_t i = 0; i < std_time.size(); ++i)
    {
        // ���������� ����� � ����������� ������� � �������� ������
        series->Points->AddXY(std_time[i], std_data_dots[i]);
    }

    // ���������� ����� �� ������
    chart1->Series->Clear(); // ������� ���������� �����
    chart1->Series->Add(series);

    // ��������� ���� � �������� ������� (��� �������������)
    chart1->ChartAreas[0]->AxisX->Title = "�����";
    chart1->ChartAreas[0]->AxisY->Title = "������";
    chart1->Titles->Add("������ ������");
}