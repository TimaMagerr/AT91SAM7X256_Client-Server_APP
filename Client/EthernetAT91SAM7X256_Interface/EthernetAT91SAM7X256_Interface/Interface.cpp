#include "Interface.h"
#include <Windows.h>
#include "parameters.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	EthernetAT91SAM7X256Interface::Interface form;
	Application::Run(% form);
}

System::Void EthernetAT91SAM7X256Interface::Interface::close_conn_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning == true) {
		close_conn(m_ClientSock); //Закрываем соединение и рушим поток
		connection_status_label->Text = "Connection is broken !";
		connection_status_label->ForeColor = Color::Red;
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::open_conn_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	clientConnThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &EthernetAT91SAM7X256Interface::Interface::open_conn));
	clientConnThread->Start();

}

System::Void EthernetAT91SAM7X256Interface::Interface::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	close_conn(m_ClientSock); //Закрываем соединение и рушим поток
	Application::Exit();
}

System::Void EthernetAT91SAM7X256Interface::Interface::button_info_board_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		infoFromServer(&client, m_packet_size, 1, info_board); //Состояние 1 - для МК - это отправка сведений о плате
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
	
}

System::Void EthernetAT91SAM7X256Interface::Interface::button_info_date_compilation_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		infoFromServer(&client, m_packet_size, 2, info_board);//Состояние 2 - для МК - это отправка сведений о дате компиляции
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::send_number_to_increase_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		int number = static_cast<int>(number_to_increase->Value); //Считываем число с селектора чисел
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 3, m_packet_size); //Переходим в состояние 3
		infoFromServer(&client, m_packet_size, number, number_task_label);//Состояние 3 - для МК - это отправка удвоенного числа
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");

}

System::Void EthernetAT91SAM7X256Interface::Interface::информацияОПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Данная программа предназначена для работы с МК AT91SAM7X256 по ETHERNET подключению.\n"
	"Есть возможность получить информацию о плате и проекте, произвести рассчет удвоенного числа, также возможно конфигурировать"
	" ножки и получать характеристику сигнала (вместе с графиком).","Информация");
}

System::Void EthernetAT91SAM7X256Interface::Interface::create_chart_button_Click(System::Object^ sender, System::EventArgs^ e)
{
	UpdateChart(time, data_dots);
}

System::Void EthernetAT91SAM7X256Interface::Interface::read_signalPA_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		/*actionWaitingThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &EthernetAT91SAM7X256Interface::Interface::ShowWaitingAnimation));
		actionWaitingThread->Start();*/
		//label_data_signal->Text = "Waiting...";
		signalProcessThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadA));
		signalProcessThread->Start();
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::read_signalPB_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		/*actionWaitingThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &EthernetAT91SAM7X256Interface::Interface::ShowWaitingAnimation));
		actionWaitingThread->Start();*/
		//label_data_signal->Text = "Waiting...";
		signalProcessThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadB));
		signalProcessThread->Start();
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}


System::Void EthernetAT91SAM7X256Interface::Interface::set_PB28_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 5, m_packet_size); //Переходим в состояние 5
		radio_button_set(radioButtonB28_I_New, radioButtonB28_O_0_New, radioButtonB28_O_1_New,
			radioButtonB28_I, radioButtonB28_O_0, radioButtonB28_O_1,
			"B;28;2\n", "B;28;0\n", "B;28;1\n");//Состояние 5 - для МК - это конфигурация пинов
		recMessageBox(&client, m_packet_size);
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::set_PB29_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 5, m_packet_size); //Переходим в состояние 5
		radio_button_set(radioButtonB29_I_New, radioButtonB29_O_0_New, radioButtonB29_O_1_New,
			radioButtonB29_I, radioButtonB29_O_0, radioButtonB29_O_1,
			"B;29;2\n", "B;29;0\n", "B;29;1\n");//Состояние 5 - для МК - это конфигурация пинов
		recMessageBox(&client, m_packet_size);
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::set_PB30_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 5, m_packet_size); //Переходим в состояние 5
		radio_button_set(radioButtonB30_I_New, radioButtonB30_O_0_New, radioButtonB30_O_1_New,
			radioButtonB30_I, radioButtonB30_O_0, radioButtonB30_O_1,
			"B;30;2\n", "B;30;0\n", "B;30;1\n");//Состояние 5 - для МК - это конфигурация пинов
		recMessageBox(&client, m_packet_size);
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}



System::Void EthernetAT91SAM7X256Interface::Interface::set_PA28_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 5, m_packet_size); //Переходим в состояние 5
		radio_button_set(radioButton28A_I_New, radioButton28A_O_0_New, radioButton28A_O_1_New,
			radioButton28A_I, radioButton28A_O_0, radioButton28A_O_1,
			"A;28;2\n", "A;28;0\n", "A;28;1\n");//Состояние 5 - для МК - это конфигурация пинов
		recMessageBox(&client, m_packet_size);
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::set_PA29_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 5, m_packet_size); //Переходим в состояние 5
		radio_button_set(radioButton29A_I_New, radioButton29A_O_0_New, radioButton29A_O_1_New,
			radioButton29A_I, radioButton29A_O_0, radioButton29A_O_1,
			"A;29;2\n", "A;29;0\n", "A;29;1\n");//Состояние 5 - для МК - это конфигурация пинов
		recMessageBox(&client, m_packet_size);
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}

System::Void EthernetAT91SAM7X256Interface::Interface::set_PA30_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (clientRunning) {
		SOCKET client = m_ClientSock;
		sendNumbMessage(&client, 5, m_packet_size); //Переходим в состояние 5
		radio_button_set(radioButton30A_I_New, radioButton30A_O_0_New, radioButton30A_O_1_New,
			radioButton30A_I, radioButton30A_O_0, radioButton30A_O_1,
			"A;30;2\n", "A;30;0\n", "A;30;1\n");//Состояние 5 - для МК - это конфигурация пинов
		recMessageBox(&client, m_packet_size);
	}
	else
		MessageBox::Show("Connection is not created!", "Attention!");
}






