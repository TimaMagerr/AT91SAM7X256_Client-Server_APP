#pragma once

#include "libraries.h"
#include "parameters.h"


namespace EthernetAT91SAM7X256Interface {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;


	/// <summary>
	/// Сводка для Interface
	/// </summary>
	public ref class Interface : public System::Windows::Forms::Form
	{
	private:
		List<int>^ time; //Прошедшее время считывания сигнала
		List<int>^ data_dots; //Данные для графика
	private: System::Windows::Forms::Button^ create_chart_button;
	private: System::Windows::Forms::Label^ label11;

	private: System::Windows::Forms::NumericUpDown^ numericUpDown_time;
	public:
		Interface(void)
		{
			InitializeComponent();
			time = gcnew List<int>(); 
			data_dots = gcnew List<int>(); 
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Interface()
		{
			if (components)
			{
				delete components;

			}
		}

	public: bool sendFlag = false; //Флажок отправки
	public: static bool clientRunning = false; //Флаг контроля соединения клиента

	public:	static SOCKET m_ClientSock; //Сокет подключения клиента
	private:
		int erStat = 0;//Переменная под обработку ошибок

	private: System::Threading::Thread^ clientConnThread; //Поток для создания соединения
	private: System::Threading::Thread^ actionWaitingThread; //Поток для создания соединения
	private: System::Threading::Thread^ signalProcessThread; //Поток для создания соединения
	private: short int m_packet_size = 0; //Отслеживает ошибки при отправке и принятии сообщений
	private: static bool stopWaiting = true; // Флаг остановки


	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ выходToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ информацияОПрограммеToolStripMenuItem;
	private: System::Windows::Forms::Button^ open_conn_button;
	private: System::Windows::Forms::Button^ close_conn_button;
	private: System::Windows::Forms::Label^ connection_status_label;
	private: System::Windows::Forms::GroupBox^ groupBox_conn_label;


	private: System::Windows::Forms::GroupBox^ groupBox2;



	private: System::Windows::Forms::Label^ info_board;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::Button^ button_info_date_compilation;
	private: System::Windows::Forms::Button^ button_info_board;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::NumericUpDown^ number_to_increase;

	private: System::Windows::Forms::Button^ send_number_to_increase;
	private: System::Windows::Forms::Label^ number_task_label;

	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label_PINA30;
	private: System::Windows::Forms::Label^ label_PINA29;
	private: System::Windows::Forms::Label^ label_PINA28;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ set_PA30;

	private: System::Windows::Forms::Button^ set_PA29;

	private: System::Windows::Forms::Button^ set_PA28;


	private: System::Windows::Forms::GroupBox^ groupBox11;
	private: System::Windows::Forms::RadioButton^ radioButton30A_I_New;
	private: System::Windows::Forms::RadioButton^ radioButton30A_O_1_New;


	private: System::Windows::Forms::RadioButton^ radioButton30A_O_0_New;

	private: System::Windows::Forms::GroupBox^ groupBox10;
private: System::Windows::Forms::RadioButton^ radioButton30A_I;
private: System::Windows::Forms::RadioButton^ radioButton30A_O_1;


private: System::Windows::Forms::RadioButton^ radioButton30A_O_0;

	private: System::Windows::Forms::GroupBox^ groupBox9;
private: System::Windows::Forms::RadioButton^ radioButton29A_I_New;
private: System::Windows::Forms::RadioButton^ radioButton29A_O_1_New;


private: System::Windows::Forms::RadioButton^ radioButton29A_O_0_New;


	private: System::Windows::Forms::GroupBox^ groupBox8;
private: System::Windows::Forms::RadioButton^ radioButton29A_I;
private: System::Windows::Forms::RadioButton^ radioButton29A_O_1;


private: System::Windows::Forms::RadioButton^ radioButton29A_O_0;

	private: System::Windows::Forms::GroupBox^ groupBox7;
private: System::Windows::Forms::RadioButton^ radioButton28A_I_New;
private: System::Windows::Forms::RadioButton^ radioButton28A_O_1_New;


private: System::Windows::Forms::RadioButton^ radioButton28A_O_0_New;


	private: System::Windows::Forms::GroupBox^ groupBox6;
private: System::Windows::Forms::RadioButton^ radioButton28A_I;
private: System::Windows::Forms::RadioButton^ radioButton28A_O_1;


private: System::Windows::Forms::RadioButton^ radioButton28A_O_0;


private: System::Windows::Forms::GroupBox^ groupBox12;
private: System::Windows::Forms::GroupBox^ groupBox13;
private: System::Windows::Forms::RadioButton^ radioButtonB30_I_New;
private: System::Windows::Forms::RadioButton^ radioButtonB30_O_1_New;
private: System::Windows::Forms::RadioButton^ radioButtonB30_O_0_New;
private: System::Windows::Forms::GroupBox^ groupBox14;
private: System::Windows::Forms::RadioButton^ radioButtonB30_I;
private: System::Windows::Forms::RadioButton^ radioButtonB30_O_1;
private: System::Windows::Forms::RadioButton^ radioButtonB30_O_0;
private: System::Windows::Forms::GroupBox^ groupBox15;
private: System::Windows::Forms::RadioButton^ radioButtonB29_I_New;
private: System::Windows::Forms::RadioButton^ radioButtonB29_O_1_New;
private: System::Windows::Forms::RadioButton^ radioButtonB29_O_0_New;
private: System::Windows::Forms::GroupBox^ groupBox16;
private: System::Windows::Forms::RadioButton^ radioButtonB29_I;
private: System::Windows::Forms::RadioButton^ radioButtonB29_O_1;
private: System::Windows::Forms::RadioButton^ radioButtonB29_O_0;
private: System::Windows::Forms::GroupBox^ groupBox17;
private: System::Windows::Forms::RadioButton^ radioButtonB28_I_New;
private: System::Windows::Forms::RadioButton^ radioButtonB28_O_1_New;
private: System::Windows::Forms::RadioButton^ radioButtonB28_O_0_New;
private: System::Windows::Forms::GroupBox^ groupBox18;
private: System::Windows::Forms::RadioButton^ radioButtonB28_I;
private: System::Windows::Forms::RadioButton^ radioButtonB28_O_1;
private: System::Windows::Forms::RadioButton^ radioButtonB28_O_0;


private: System::Windows::Forms::Button^ set_PB30;

private: System::Windows::Forms::Button^ set_PB29;

private: System::Windows::Forms::Button^ set_PB28;


private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::Label^ label7;
private: System::Windows::Forms::Label^ label10;

private: System::Windows::Forms::Label^ label12;
private: System::Windows::Forms::GroupBox^ groupBox1;
private: System::Windows::Forms::Button^ button3;
private: System::Windows::Forms::Label^ label_data_signal;

private: System::Windows::Forms::Button^ read_signalPB;
private: System::Windows::Forms::Button^ read_signalPA;
private: System::Windows::Forms::Label^ label_PB;
private: System::Windows::Forms::NumericUpDown^ numericUpDownPB;
private: System::Windows::Forms::Label^ label_PA;
private: System::Windows::Forms::NumericUpDown^ numericUpDownPA;
private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->выходToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->информацияОПрограммеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->open_conn_button = (gcnew System::Windows::Forms::Button());
			this->close_conn_button = (gcnew System::Windows::Forms::Button());
			this->connection_status_label = (gcnew System::Windows::Forms::Label());
			this->groupBox_conn_label = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox11 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton30A_I_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton30A_O_1_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton30A_O_0_New = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox10 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton30A_I = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton30A_O_1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton30A_O_0 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton29A_I_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton29A_O_1_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton29A_O_0_New = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton29A_I = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton29A_O_1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton29A_O_0 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton28A_I_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton28A_O_1_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton28A_O_0_New = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton28A_I = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton28A_O_1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton28A_O_0 = (gcnew System::Windows::Forms::RadioButton());
			this->set_PA30 = (gcnew System::Windows::Forms::Button());
			this->set_PA29 = (gcnew System::Windows::Forms::Button());
			this->set_PA28 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label_PINA30 = (gcnew System::Windows::Forms::Label());
			this->label_PINA29 = (gcnew System::Windows::Forms::Label());
			this->label_PINA28 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->info_board = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->button_info_date_compilation = (gcnew System::Windows::Forms::Button());
			this->button_info_board = (gcnew System::Windows::Forms::Button());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->number_to_increase = (gcnew System::Windows::Forms::NumericUpDown());
			this->send_number_to_increase = (gcnew System::Windows::Forms::Button());
			this->number_task_label = (gcnew System::Windows::Forms::Label());
			this->groupBox12 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox13 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonB30_I_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB30_O_1_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB30_O_0_New = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox14 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonB30_I = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB30_O_1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB30_O_0 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox15 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonB29_I_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB29_O_1_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB29_O_0_New = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox16 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonB29_I = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB29_O_1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB29_O_0 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox17 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonB28_I_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB28_O_1_New = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB28_O_0_New = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox18 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButtonB28_I = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB28_O_1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButtonB28_O_0 = (gcnew System::Windows::Forms::RadioButton());
			this->set_PB30 = (gcnew System::Windows::Forms::Button());
			this->set_PB29 = (gcnew System::Windows::Forms::Button());
			this->set_PB28 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->create_chart_button = (gcnew System::Windows::Forms::Button());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown_time = (gcnew System::Windows::Forms::NumericUpDown());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label_data_signal = (gcnew System::Windows::Forms::Label());
			this->read_signalPB = (gcnew System::Windows::Forms::Button());
			this->read_signalPA = (gcnew System::Windows::Forms::Button());
			this->label_PB = (gcnew System::Windows::Forms::Label());
			this->numericUpDownPB = (gcnew System::Windows::Forms::NumericUpDown());
			this->label_PA = (gcnew System::Windows::Forms::Label());
			this->numericUpDownPA = (gcnew System::Windows::Forms::NumericUpDown());
			this->menuStrip1->SuspendLayout();
			this->groupBox_conn_label->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox11->SuspendLayout();
			this->groupBox10->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->number_to_increase))->BeginInit();
			this->groupBox12->SuspendLayout();
			this->groupBox13->SuspendLayout();
			this->groupBox14->SuspendLayout();
			this->groupBox15->SuspendLayout();
			this->groupBox16->SuspendLayout();
			this->groupBox17->SuspendLayout();
			this->groupBox18->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_time))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownPB))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownPA))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->выходToolStripMenuItem,
					this->информацияОПрограммеToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1522, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// выходToolStripMenuItem
			// 
			this->выходToolStripMenuItem->Name = L"выходToolStripMenuItem";
			this->выходToolStripMenuItem->Size = System::Drawing::Size(54, 20);
			this->выходToolStripMenuItem->Text = L"Выход";
			this->выходToolStripMenuItem->Click += gcnew System::EventHandler(this, &Interface::выходToolStripMenuItem_Click);
			// 
			// информацияОПрограммеToolStripMenuItem
			// 
			this->информацияОПрограммеToolStripMenuItem->Name = L"информацияОПрограммеToolStripMenuItem";
			this->информацияОПрограммеToolStripMenuItem->Size = System::Drawing::Size(169, 20);
			this->информацияОПрограммеToolStripMenuItem->Text = L"Информация о программе";
			this->информацияОПрограммеToolStripMenuItem->Click += gcnew System::EventHandler(this, &Interface::информацияОПрограммеToolStripMenuItem_Click);
			// 
			// open_conn_button
			// 
			this->open_conn_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->open_conn_button->ForeColor = System::Drawing::Color::DarkGreen;
			this->open_conn_button->Location = System::Drawing::Point(39, 202);
			this->open_conn_button->Name = L"open_conn_button";
			this->open_conn_button->Size = System::Drawing::Size(148, 67);
			this->open_conn_button->TabIndex = 1;
			this->open_conn_button->Text = L"Подключение к серверу";
			this->open_conn_button->UseVisualStyleBackColor = true;
			this->open_conn_button->Click += gcnew System::EventHandler(this, &Interface::open_conn_button_Click);
			// 
			// close_conn_button
			// 
			this->close_conn_button->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->close_conn_button->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->close_conn_button->Location = System::Drawing::Point(193, 202);
			this->close_conn_button->Name = L"close_conn_button";
			this->close_conn_button->Size = System::Drawing::Size(145, 67);
			this->close_conn_button->TabIndex = 2;
			this->close_conn_button->Text = L"Разорвать соединение";
			this->close_conn_button->UseVisualStyleBackColor = true;
			this->close_conn_button->Click += gcnew System::EventHandler(this, &Interface::close_conn_button_Click);
			// 
			// connection_status_label
			// 
			this->connection_status_label->BackColor = System::Drawing::SystemColors::Control;
			this->connection_status_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->connection_status_label->ForeColor = System::Drawing::Color::Black;
			this->connection_status_label->Location = System::Drawing::Point(40, 27);
			this->connection_status_label->Name = L"connection_status_label";
			this->connection_status_label->Size = System::Drawing::Size(298, 169);
			this->connection_status_label->TabIndex = 3;
			// 
			// groupBox_conn_label
			// 
			this->groupBox_conn_label->Controls->Add(this->connection_status_label);
			this->groupBox_conn_label->Controls->Add(this->close_conn_button);
			this->groupBox_conn_label->Controls->Add(this->open_conn_button);
			this->groupBox_conn_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox_conn_label->ForeColor = System::Drawing::Color::Black;
			this->groupBox_conn_label->Location = System::Drawing::Point(22, 45);
			this->groupBox_conn_label->Name = L"groupBox_conn_label";
			this->groupBox_conn_label->Size = System::Drawing::Size(377, 287);
			this->groupBox_conn_label->TabIndex = 4;
			this->groupBox_conn_label->TabStop = false;
			this->groupBox_conn_label->Text = L"Информация о подключении";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->groupBox11);
			this->groupBox2->Controls->Add(this->groupBox10);
			this->groupBox2->Controls->Add(this->groupBox9);
			this->groupBox2->Controls->Add(this->groupBox8);
			this->groupBox2->Controls->Add(this->groupBox7);
			this->groupBox2->Controls->Add(this->groupBox6);
			this->groupBox2->Controls->Add(this->set_PA30);
			this->groupBox2->Controls->Add(this->set_PA29);
			this->groupBox2->Controls->Add(this->set_PA28);
			this->groupBox2->Controls->Add(this->label9);
			this->groupBox2->Controls->Add(this->label8);
			this->groupBox2->Controls->Add(this->label_PINA30);
			this->groupBox2->Controls->Add(this->label_PINA29);
			this->groupBox2->Controls->Add(this->label_PINA28);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox2->ForeColor = System::Drawing::Color::Black;
			this->groupBox2->Location = System::Drawing::Point(22, 338);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(377, 287);
			this->groupBox2->TabIndex = 15;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Конфигурация портов PA";
			// 
			// groupBox11
			// 
			this->groupBox11->Controls->Add(this->radioButton30A_I_New);
			this->groupBox11->Controls->Add(this->radioButton30A_O_1_New);
			this->groupBox11->Controls->Add(this->radioButton30A_O_0_New);
			this->groupBox11->Location = System::Drawing::Point(161, 200);
			this->groupBox11->Name = L"groupBox11";
			this->groupBox11->Size = System::Drawing::Size(93, 72);
			this->groupBox11->TabIndex = 61;
			this->groupBox11->TabStop = false;
			// 
			// radioButton30A_I_New
			// 
			this->radioButton30A_I_New->AutoSize = true;
			this->radioButton30A_I_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton30A_I_New->Location = System::Drawing::Point(5, 14);
			this->radioButton30A_I_New->Name = L"radioButton30A_I_New";
			this->radioButton30A_I_New->Size = System::Drawing::Size(60, 20);
			this->radioButton30A_I_New->TabIndex = 7;
			this->radioButton30A_I_New->TabStop = true;
			this->radioButton30A_I_New->Text = L"вход";
			this->radioButton30A_I_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton30A_I_New->UseVisualStyleBackColor = true;
			// 
			// radioButton30A_O_1_New
			// 
			this->radioButton30A_O_1_New->AutoSize = true;
			this->radioButton30A_O_1_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton30A_O_1_New->Location = System::Drawing::Point(5, 46);
			this->radioButton30A_O_1_New->Name = L"radioButton30A_O_1_New";
			this->radioButton30A_O_1_New->Size = System::Drawing::Size(82, 20);
			this->radioButton30A_O_1_New->TabIndex = 9;
			this->radioButton30A_O_1_New->TabStop = true;
			this->radioButton30A_O_1_New->Text = L"выход 1";
			this->radioButton30A_O_1_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton30A_O_1_New->UseVisualStyleBackColor = true;
			// 
			// radioButton30A_O_0_New
			// 
			this->radioButton30A_O_0_New->AutoSize = true;
			this->radioButton30A_O_0_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton30A_O_0_New->Location = System::Drawing::Point(5, 29);
			this->radioButton30A_O_0_New->Name = L"radioButton30A_O_0_New";
			this->radioButton30A_O_0_New->Size = System::Drawing::Size(82, 20);
			this->radioButton30A_O_0_New->TabIndex = 8;
			this->radioButton30A_O_0_New->TabStop = true;
			this->radioButton30A_O_0_New->Text = L"выход 0";
			this->radioButton30A_O_0_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton30A_O_0_New->UseVisualStyleBackColor = true;
			// 
			// groupBox10
			// 
			this->groupBox10->Controls->Add(this->radioButton30A_I);
			this->groupBox10->Controls->Add(this->radioButton30A_O_1);
			this->groupBox10->Controls->Add(this->radioButton30A_O_0);
			this->groupBox10->Location = System::Drawing::Point(61, 200);
			this->groupBox10->Name = L"groupBox10";
			this->groupBox10->Size = System::Drawing::Size(93, 72);
			this->groupBox10->TabIndex = 60;
			this->groupBox10->TabStop = false;
			// 
			// radioButton30A_I
			// 
			this->radioButton30A_I->AutoSize = true;
			this->radioButton30A_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton30A_I->Location = System::Drawing::Point(5, 14);
			this->radioButton30A_I->Name = L"radioButton30A_I";
			this->radioButton30A_I->Size = System::Drawing::Size(60, 20);
			this->radioButton30A_I->TabIndex = 7;
			this->radioButton30A_I->TabStop = true;
			this->radioButton30A_I->Text = L"вход";
			this->radioButton30A_I->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton30A_I->UseVisualStyleBackColor = true;
			// 
			// radioButton30A_O_1
			// 
			this->radioButton30A_O_1->AutoSize = true;
			this->radioButton30A_O_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton30A_O_1->Location = System::Drawing::Point(5, 46);
			this->radioButton30A_O_1->Name = L"radioButton30A_O_1";
			this->radioButton30A_O_1->Size = System::Drawing::Size(82, 20);
			this->radioButton30A_O_1->TabIndex = 9;
			this->radioButton30A_O_1->TabStop = true;
			this->radioButton30A_O_1->Text = L"выход 1";
			this->radioButton30A_O_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton30A_O_1->UseVisualStyleBackColor = true;
			// 
			// radioButton30A_O_0
			// 
			this->radioButton30A_O_0->AutoSize = true;
			this->radioButton30A_O_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton30A_O_0->Location = System::Drawing::Point(5, 29);
			this->radioButton30A_O_0->Name = L"radioButton30A_O_0";
			this->radioButton30A_O_0->Size = System::Drawing::Size(82, 20);
			this->radioButton30A_O_0->TabIndex = 8;
			this->radioButton30A_O_0->TabStop = true;
			this->radioButton30A_O_0->Text = L"выход 0";
			this->radioButton30A_O_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton30A_O_0->UseVisualStyleBackColor = true;
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->radioButton29A_I_New);
			this->groupBox9->Controls->Add(this->radioButton29A_O_1_New);
			this->groupBox9->Controls->Add(this->radioButton29A_O_0_New);
			this->groupBox9->Location = System::Drawing::Point(167, 128);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(93, 72);
			this->groupBox9->TabIndex = 60;
			this->groupBox9->TabStop = false;
			// 
			// radioButton29A_I_New
			// 
			this->radioButton29A_I_New->AutoSize = true;
			this->radioButton29A_I_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton29A_I_New->Location = System::Drawing::Point(5, 14);
			this->radioButton29A_I_New->Name = L"radioButton29A_I_New";
			this->radioButton29A_I_New->Size = System::Drawing::Size(60, 20);
			this->radioButton29A_I_New->TabIndex = 7;
			this->radioButton29A_I_New->TabStop = true;
			this->radioButton29A_I_New->Text = L"вход";
			this->radioButton29A_I_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton29A_I_New->UseVisualStyleBackColor = true;
			// 
			// radioButton29A_O_1_New
			// 
			this->radioButton29A_O_1_New->AutoSize = true;
			this->radioButton29A_O_1_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton29A_O_1_New->Location = System::Drawing::Point(5, 46);
			this->radioButton29A_O_1_New->Name = L"radioButton29A_O_1_New";
			this->radioButton29A_O_1_New->Size = System::Drawing::Size(82, 20);
			this->radioButton29A_O_1_New->TabIndex = 9;
			this->radioButton29A_O_1_New->TabStop = true;
			this->radioButton29A_O_1_New->Text = L"выход 1";
			this->radioButton29A_O_1_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton29A_O_1_New->UseVisualStyleBackColor = true;
			// 
			// radioButton29A_O_0_New
			// 
			this->radioButton29A_O_0_New->AutoSize = true;
			this->radioButton29A_O_0_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton29A_O_0_New->Location = System::Drawing::Point(5, 29);
			this->radioButton29A_O_0_New->Name = L"radioButton29A_O_0_New";
			this->radioButton29A_O_0_New->Size = System::Drawing::Size(82, 20);
			this->radioButton29A_O_0_New->TabIndex = 8;
			this->radioButton29A_O_0_New->TabStop = true;
			this->radioButton29A_O_0_New->Text = L"выход 0";
			this->radioButton29A_O_0_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton29A_O_0_New->UseVisualStyleBackColor = true;
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->radioButton29A_I);
			this->groupBox8->Controls->Add(this->radioButton29A_O_1);
			this->groupBox8->Controls->Add(this->radioButton29A_O_0);
			this->groupBox8->Location = System::Drawing::Point(61, 128);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(93, 72);
			this->groupBox8->TabIndex = 59;
			this->groupBox8->TabStop = false;
			// 
			// radioButton29A_I
			// 
			this->radioButton29A_I->AutoSize = true;
			this->radioButton29A_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton29A_I->Location = System::Drawing::Point(5, 14);
			this->radioButton29A_I->Name = L"radioButton29A_I";
			this->radioButton29A_I->Size = System::Drawing::Size(60, 20);
			this->radioButton29A_I->TabIndex = 7;
			this->radioButton29A_I->TabStop = true;
			this->radioButton29A_I->Text = L"вход";
			this->radioButton29A_I->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton29A_I->UseVisualStyleBackColor = true;
			// 
			// radioButton29A_O_1
			// 
			this->radioButton29A_O_1->AutoSize = true;
			this->radioButton29A_O_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton29A_O_1->Location = System::Drawing::Point(5, 46);
			this->radioButton29A_O_1->Name = L"radioButton29A_O_1";
			this->radioButton29A_O_1->Size = System::Drawing::Size(82, 20);
			this->radioButton29A_O_1->TabIndex = 9;
			this->radioButton29A_O_1->TabStop = true;
			this->radioButton29A_O_1->Text = L"выход 1";
			this->radioButton29A_O_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton29A_O_1->UseVisualStyleBackColor = true;
			// 
			// radioButton29A_O_0
			// 
			this->radioButton29A_O_0->AutoSize = true;
			this->radioButton29A_O_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton29A_O_0->Location = System::Drawing::Point(5, 29);
			this->radioButton29A_O_0->Name = L"radioButton29A_O_0";
			this->radioButton29A_O_0->Size = System::Drawing::Size(82, 20);
			this->radioButton29A_O_0->TabIndex = 8;
			this->radioButton29A_O_0->TabStop = true;
			this->radioButton29A_O_0->Text = L"выход 0";
			this->radioButton29A_O_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton29A_O_0->UseVisualStyleBackColor = true;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->radioButton28A_I_New);
			this->groupBox7->Controls->Add(this->radioButton28A_O_1_New);
			this->groupBox7->Controls->Add(this->radioButton28A_O_0_New);
			this->groupBox7->Location = System::Drawing::Point(167, 56);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(93, 72);
			this->groupBox7->TabIndex = 58;
			this->groupBox7->TabStop = false;
			// 
			// radioButton28A_I_New
			// 
			this->radioButton28A_I_New->AutoSize = true;
			this->radioButton28A_I_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton28A_I_New->Location = System::Drawing::Point(5, 14);
			this->radioButton28A_I_New->Name = L"radioButton28A_I_New";
			this->radioButton28A_I_New->Size = System::Drawing::Size(60, 20);
			this->radioButton28A_I_New->TabIndex = 7;
			this->radioButton28A_I_New->TabStop = true;
			this->radioButton28A_I_New->Text = L"вход";
			this->radioButton28A_I_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton28A_I_New->UseVisualStyleBackColor = true;
			// 
			// radioButton28A_O_1_New
			// 
			this->radioButton28A_O_1_New->AutoSize = true;
			this->radioButton28A_O_1_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton28A_O_1_New->Location = System::Drawing::Point(5, 46);
			this->radioButton28A_O_1_New->Name = L"radioButton28A_O_1_New";
			this->radioButton28A_O_1_New->Size = System::Drawing::Size(82, 20);
			this->radioButton28A_O_1_New->TabIndex = 9;
			this->radioButton28A_O_1_New->TabStop = true;
			this->radioButton28A_O_1_New->Text = L"выход 1";
			this->radioButton28A_O_1_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton28A_O_1_New->UseVisualStyleBackColor = true;
			// 
			// radioButton28A_O_0_New
			// 
			this->radioButton28A_O_0_New->AutoSize = true;
			this->radioButton28A_O_0_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton28A_O_0_New->Location = System::Drawing::Point(5, 29);
			this->radioButton28A_O_0_New->Name = L"radioButton28A_O_0_New";
			this->radioButton28A_O_0_New->Size = System::Drawing::Size(82, 20);
			this->radioButton28A_O_0_New->TabIndex = 8;
			this->radioButton28A_O_0_New->TabStop = true;
			this->radioButton28A_O_0_New->Text = L"выход 0";
			this->radioButton28A_O_0_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton28A_O_0_New->UseVisualStyleBackColor = true;
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->radioButton28A_I);
			this->groupBox6->Controls->Add(this->radioButton28A_O_1);
			this->groupBox6->Controls->Add(this->radioButton28A_O_0);
			this->groupBox6->Location = System::Drawing::Point(61, 56);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(93, 72);
			this->groupBox6->TabIndex = 57;
			this->groupBox6->TabStop = false;
			// 
			// radioButton28A_I
			// 
			this->radioButton28A_I->AutoSize = true;
			this->radioButton28A_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton28A_I->Location = System::Drawing::Point(5, 14);
			this->radioButton28A_I->Name = L"radioButton28A_I";
			this->radioButton28A_I->Size = System::Drawing::Size(60, 20);
			this->radioButton28A_I->TabIndex = 7;
			this->radioButton28A_I->TabStop = true;
			this->radioButton28A_I->Text = L"вход";
			this->radioButton28A_I->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton28A_I->UseVisualStyleBackColor = true;
			// 
			// radioButton28A_O_1
			// 
			this->radioButton28A_O_1->AutoSize = true;
			this->radioButton28A_O_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton28A_O_1->Location = System::Drawing::Point(5, 46);
			this->radioButton28A_O_1->Name = L"radioButton28A_O_1";
			this->radioButton28A_O_1->Size = System::Drawing::Size(82, 20);
			this->radioButton28A_O_1->TabIndex = 9;
			this->radioButton28A_O_1->TabStop = true;
			this->radioButton28A_O_1->Text = L"выход 1";
			this->radioButton28A_O_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton28A_O_1->UseVisualStyleBackColor = true;
			// 
			// radioButton28A_O_0
			// 
			this->radioButton28A_O_0->AutoSize = true;
			this->radioButton28A_O_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton28A_O_0->Location = System::Drawing::Point(5, 29);
			this->radioButton28A_O_0->Name = L"radioButton28A_O_0";
			this->radioButton28A_O_0->Size = System::Drawing::Size(82, 20);
			this->radioButton28A_O_0->TabIndex = 8;
			this->radioButton28A_O_0->TabStop = true;
			this->radioButton28A_O_0->Text = L"выход 0";
			this->radioButton28A_O_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButton28A_O_0->UseVisualStyleBackColor = true;
			// 
			// set_PA30
			// 
			this->set_PA30->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->set_PA30->Location = System::Drawing::Point(266, 222);
			this->set_PA30->Name = L"set_PA30";
			this->set_PA30->Size = System::Drawing::Size(94, 32);
			this->set_PA30->TabIndex = 43;
			this->set_PA30->Text = L"Задать";
			this->set_PA30->UseVisualStyleBackColor = true;
			this->set_PA30->Click += gcnew System::EventHandler(this, &Interface::set_PA30_Click);
			// 
			// set_PA29
			// 
			this->set_PA29->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->set_PA29->Location = System::Drawing::Point(266, 150);
			this->set_PA29->Name = L"set_PA29";
			this->set_PA29->Size = System::Drawing::Size(94, 32);
			this->set_PA29->TabIndex = 42;
			this->set_PA29->Text = L"Задать";
			this->set_PA29->UseVisualStyleBackColor = true;
			this->set_PA29->Click += gcnew System::EventHandler(this, &Interface::set_PA29_Click);
			// 
			// set_PA28
			// 
			this->set_PA28->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->set_PA28->Location = System::Drawing::Point(266, 78);
			this->set_PA28->Name = L"set_PA28";
			this->set_PA28->Size = System::Drawing::Size(94, 32);
			this->set_PA28->TabIndex = 41;
			this->set_PA28->Text = L"Задать";
			this->set_PA28->UseVisualStyleBackColor = true;
			this->set_PA28->Click += gcnew System::EventHandler(this, &Interface::set_PA28_Click);
			// 
			// label9
			// 
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(154, 25);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(118, 36);
			this->label9->TabIndex = 6;
			this->label9->Text = L"Настроить состояние";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label8
			// 
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(53, 25);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(101, 36);
			this->label8->TabIndex = 5;
			this->label8->Text = L"Текущее состояние";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_PINA30
			// 
			this->label_PINA30->AutoSize = true;
			this->label_PINA30->Location = System::Drawing::Point(15, 228);
			this->label_PINA30->Name = L"label_PINA30";
			this->label_PINA30->Size = System::Drawing::Size(29, 20);
			this->label_PINA30->TabIndex = 4;
			this->label_PINA30->Text = L"30";
			// 
			// label_PINA29
			// 
			this->label_PINA29->AutoSize = true;
			this->label_PINA29->Location = System::Drawing::Point(15, 156);
			this->label_PINA29->Name = L"label_PINA29";
			this->label_PINA29->Size = System::Drawing::Size(29, 20);
			this->label_PINA29->TabIndex = 3;
			this->label_PINA29->Text = L"29";
			// 
			// label_PINA28
			// 
			this->label_PINA28->AutoSize = true;
			this->label_PINA28->Location = System::Drawing::Point(15, 85);
			this->label_PINA28->Name = L"label_PINA28";
			this->label_PINA28->Size = System::Drawing::Size(29, 20);
			this->label_PINA28->TabIndex = 2;
			this->label_PINA28->Text = L"28";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 32);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(25, 20);
			this->label2->TabIndex = 0;
			this->label2->Text = L"№";
			// 
			// info_board
			// 
			this->info_board->BackColor = System::Drawing::SystemColors::Control;
			this->info_board->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->info_board->ForeColor = System::Drawing::Color::Black;
			this->info_board->Location = System::Drawing::Point(37, 27);
			this->info_board->Name = L"info_board";
			this->info_board->Size = System::Drawing::Size(299, 176);
			this->info_board->TabIndex = 7;
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->button_info_date_compilation);
			this->groupBox4->Controls->Add(this->button_info_board);
			this->groupBox4->Controls->Add(this->info_board);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox4->ForeColor = System::Drawing::Color::Black;
			this->groupBox4->Location = System::Drawing::Point(405, 45);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(378, 287);
			this->groupBox4->TabIndex = 10;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Информация о плате и проекте";
			// 
			// button_info_date_compilation
			// 
			this->button_info_date_compilation->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button_info_date_compilation->ForeColor = System::Drawing::Color::Black;
			this->button_info_date_compilation->Location = System::Drawing::Point(191, 206);
			this->button_info_date_compilation->Name = L"button_info_date_compilation";
			this->button_info_date_compilation->Size = System::Drawing::Size(145, 67);
			this->button_info_date_compilation->TabIndex = 4;
			this->button_info_date_compilation->Text = L"Получить информацию о дате компиляции";
			this->button_info_date_compilation->UseVisualStyleBackColor = true;
			this->button_info_date_compilation->Click += gcnew System::EventHandler(this, &Interface::button_info_date_compilation_Click);
			// 
			// button_info_board
			// 
			this->button_info_board->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_info_board->ForeColor = System::Drawing::Color::Black;
			this->button_info_board->Location = System::Drawing::Point(37, 206);
			this->button_info_board->Name = L"button_info_board";
			this->button_info_board->Size = System::Drawing::Size(148, 67);
			this->button_info_board->TabIndex = 4;
			this->button_info_board->Text = L"Получить информацию о плате";
			this->button_info_board->UseVisualStyleBackColor = true;
			this->button_info_board->Click += gcnew System::EventHandler(this, &Interface::button_info_board_Click);
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->label4);
			this->groupBox5->Controls->Add(this->label1);
			this->groupBox5->Controls->Add(this->number_to_increase);
			this->groupBox5->Controls->Add(this->send_number_to_increase);
			this->groupBox5->Controls->Add(this->number_task_label);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox5->ForeColor = System::Drawing::Color::Black;
			this->groupBox5->Location = System::Drawing::Point(1349, 45);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(161, 158);
			this->groupBox5->TabIndex = 11;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Удвоение числа";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(13, 106);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(138, 16);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Удвоенное число";
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(17, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(134, 21);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Исходное число";
			// 
			// number_to_increase
			// 
			this->number_to_increase->Location = System::Drawing::Point(21, 43);
			this->number_to_increase->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000000, 0, 0, 0 });
			this->number_to_increase->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3000000, 0, 0, System::Int32::MinValue });
			this->number_to_increase->Name = L"number_to_increase";
			this->number_to_increase->Size = System::Drawing::Size(120, 26);
			this->number_to_increase->TabIndex = 8;
			// 
			// send_number_to_increase
			// 
			this->send_number_to_increase->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->send_number_to_increase->ForeColor = System::Drawing::Color::Black;
			this->send_number_to_increase->Location = System::Drawing::Point(34, 75);
			this->send_number_to_increase->Name = L"send_number_to_increase";
			this->send_number_to_increase->Size = System::Drawing::Size(96, 28);
			this->send_number_to_increase->TabIndex = 4;
			this->send_number_to_increase->Text = L"Отправить";
			this->send_number_to_increase->UseVisualStyleBackColor = true;
			this->send_number_to_increase->Click += gcnew System::EventHandler(this, &Interface::send_number_to_increase_Click);
			// 
			// number_task_label
			// 
			this->number_task_label->BackColor = System::Drawing::SystemColors::Control;
			this->number_task_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->number_task_label->ForeColor = System::Drawing::Color::Black;
			this->number_task_label->Location = System::Drawing::Point(21, 120);
			this->number_task_label->Name = L"number_task_label";
			this->number_task_label->Size = System::Drawing::Size(120, 26);
			this->number_task_label->TabIndex = 7;
			// 
			// groupBox12
			// 
			this->groupBox12->Controls->Add(this->groupBox13);
			this->groupBox12->Controls->Add(this->groupBox14);
			this->groupBox12->Controls->Add(this->groupBox15);
			this->groupBox12->Controls->Add(this->groupBox16);
			this->groupBox12->Controls->Add(this->groupBox17);
			this->groupBox12->Controls->Add(this->groupBox18);
			this->groupBox12->Controls->Add(this->set_PB30);
			this->groupBox12->Controls->Add(this->set_PB29);
			this->groupBox12->Controls->Add(this->set_PB28);
			this->groupBox12->Controls->Add(this->label3);
			this->groupBox12->Controls->Add(this->label5);
			this->groupBox12->Controls->Add(this->label6);
			this->groupBox12->Controls->Add(this->label7);
			this->groupBox12->Controls->Add(this->label10);
			this->groupBox12->Controls->Add(this->label12);
			this->groupBox12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox12->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->groupBox12->Location = System::Drawing::Point(406, 338);
			this->groupBox12->Name = L"groupBox12";
			this->groupBox12->Size = System::Drawing::Size(377, 287);
			this->groupBox12->TabIndex = 16;
			this->groupBox12->TabStop = false;
			this->groupBox12->Text = L"Конфигурация портов PB";
			// 
			// groupBox13
			// 
			this->groupBox13->Controls->Add(this->radioButtonB30_I_New);
			this->groupBox13->Controls->Add(this->radioButtonB30_O_1_New);
			this->groupBox13->Controls->Add(this->radioButtonB30_O_0_New);
			this->groupBox13->Location = System::Drawing::Point(162, 200);
			this->groupBox13->Name = L"groupBox13";
			this->groupBox13->Size = System::Drawing::Size(93, 72);
			this->groupBox13->TabIndex = 61;
			this->groupBox13->TabStop = false;
			// 
			// radioButtonB30_I_New
			// 
			this->radioButtonB30_I_New->AutoSize = true;
			this->radioButtonB30_I_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB30_I_New->Location = System::Drawing::Point(5, 14);
			this->radioButtonB30_I_New->Name = L"radioButtonB30_I_New";
			this->radioButtonB30_I_New->Size = System::Drawing::Size(60, 20);
			this->radioButtonB30_I_New->TabIndex = 7;
			this->radioButtonB30_I_New->TabStop = true;
			this->radioButtonB30_I_New->Text = L"вход";
			this->radioButtonB30_I_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB30_I_New->UseVisualStyleBackColor = true;
			// 
			// radioButtonB30_O_1_New
			// 
			this->radioButtonB30_O_1_New->AutoSize = true;
			this->radioButtonB30_O_1_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB30_O_1_New->Location = System::Drawing::Point(5, 46);
			this->radioButtonB30_O_1_New->Name = L"radioButtonB30_O_1_New";
			this->radioButtonB30_O_1_New->Size = System::Drawing::Size(82, 20);
			this->radioButtonB30_O_1_New->TabIndex = 9;
			this->radioButtonB30_O_1_New->TabStop = true;
			this->radioButtonB30_O_1_New->Text = L"выход 1";
			this->radioButtonB30_O_1_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB30_O_1_New->UseVisualStyleBackColor = true;
			// 
			// radioButtonB30_O_0_New
			// 
			this->radioButtonB30_O_0_New->AutoSize = true;
			this->radioButtonB30_O_0_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB30_O_0_New->Location = System::Drawing::Point(5, 29);
			this->radioButtonB30_O_0_New->Name = L"radioButtonB30_O_0_New";
			this->radioButtonB30_O_0_New->Size = System::Drawing::Size(82, 20);
			this->radioButtonB30_O_0_New->TabIndex = 8;
			this->radioButtonB30_O_0_New->TabStop = true;
			this->radioButtonB30_O_0_New->Text = L"выход 0";
			this->radioButtonB30_O_0_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB30_O_0_New->UseVisualStyleBackColor = true;
			// 
			// groupBox14
			// 
			this->groupBox14->Controls->Add(this->radioButtonB30_I);
			this->groupBox14->Controls->Add(this->radioButtonB30_O_1);
			this->groupBox14->Controls->Add(this->radioButtonB30_O_0);
			this->groupBox14->Location = System::Drawing::Point(56, 200);
			this->groupBox14->Name = L"groupBox14";
			this->groupBox14->Size = System::Drawing::Size(93, 72);
			this->groupBox14->TabIndex = 60;
			this->groupBox14->TabStop = false;
			// 
			// radioButtonB30_I
			// 
			this->radioButtonB30_I->AutoSize = true;
			this->radioButtonB30_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB30_I->Location = System::Drawing::Point(5, 14);
			this->radioButtonB30_I->Name = L"radioButtonB30_I";
			this->radioButtonB30_I->Size = System::Drawing::Size(60, 20);
			this->radioButtonB30_I->TabIndex = 7;
			this->radioButtonB30_I->TabStop = true;
			this->radioButtonB30_I->Text = L"вход";
			this->radioButtonB30_I->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB30_I->UseVisualStyleBackColor = true;
			// 
			// radioButtonB30_O_1
			// 
			this->radioButtonB30_O_1->AutoSize = true;
			this->radioButtonB30_O_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB30_O_1->Location = System::Drawing::Point(5, 46);
			this->radioButtonB30_O_1->Name = L"radioButtonB30_O_1";
			this->radioButtonB30_O_1->Size = System::Drawing::Size(82, 20);
			this->radioButtonB30_O_1->TabIndex = 9;
			this->radioButtonB30_O_1->TabStop = true;
			this->radioButtonB30_O_1->Text = L"выход 1";
			this->radioButtonB30_O_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB30_O_1->UseVisualStyleBackColor = true;
			// 
			// radioButtonB30_O_0
			// 
			this->radioButtonB30_O_0->AutoSize = true;
			this->radioButtonB30_O_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB30_O_0->Location = System::Drawing::Point(5, 29);
			this->radioButtonB30_O_0->Name = L"radioButtonB30_O_0";
			this->radioButtonB30_O_0->Size = System::Drawing::Size(82, 20);
			this->radioButtonB30_O_0->TabIndex = 8;
			this->radioButtonB30_O_0->TabStop = true;
			this->radioButtonB30_O_0->Text = L"выход 0";
			this->radioButtonB30_O_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB30_O_0->UseVisualStyleBackColor = true;
			// 
			// groupBox15
			// 
			this->groupBox15->Controls->Add(this->radioButtonB29_I_New);
			this->groupBox15->Controls->Add(this->radioButtonB29_O_1_New);
			this->groupBox15->Controls->Add(this->radioButtonB29_O_0_New);
			this->groupBox15->Location = System::Drawing::Point(162, 128);
			this->groupBox15->Name = L"groupBox15";
			this->groupBox15->Size = System::Drawing::Size(93, 72);
			this->groupBox15->TabIndex = 60;
			this->groupBox15->TabStop = false;
			// 
			// radioButtonB29_I_New
			// 
			this->radioButtonB29_I_New->AutoSize = true;
			this->radioButtonB29_I_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB29_I_New->Location = System::Drawing::Point(5, 14);
			this->radioButtonB29_I_New->Name = L"radioButtonB29_I_New";
			this->radioButtonB29_I_New->Size = System::Drawing::Size(60, 20);
			this->radioButtonB29_I_New->TabIndex = 7;
			this->radioButtonB29_I_New->TabStop = true;
			this->radioButtonB29_I_New->Text = L"вход";
			this->radioButtonB29_I_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB29_I_New->UseVisualStyleBackColor = true;
			// 
			// radioButtonB29_O_1_New
			// 
			this->radioButtonB29_O_1_New->AutoSize = true;
			this->radioButtonB29_O_1_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB29_O_1_New->Location = System::Drawing::Point(5, 46);
			this->radioButtonB29_O_1_New->Name = L"radioButtonB29_O_1_New";
			this->radioButtonB29_O_1_New->Size = System::Drawing::Size(82, 20);
			this->radioButtonB29_O_1_New->TabIndex = 9;
			this->radioButtonB29_O_1_New->TabStop = true;
			this->radioButtonB29_O_1_New->Text = L"выход 1";
			this->radioButtonB29_O_1_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB29_O_1_New->UseVisualStyleBackColor = true;
			// 
			// radioButtonB29_O_0_New
			// 
			this->radioButtonB29_O_0_New->AutoSize = true;
			this->radioButtonB29_O_0_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB29_O_0_New->Location = System::Drawing::Point(5, 29);
			this->radioButtonB29_O_0_New->Name = L"radioButtonB29_O_0_New";
			this->radioButtonB29_O_0_New->Size = System::Drawing::Size(82, 20);
			this->radioButtonB29_O_0_New->TabIndex = 8;
			this->radioButtonB29_O_0_New->TabStop = true;
			this->radioButtonB29_O_0_New->Text = L"выход 0";
			this->radioButtonB29_O_0_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB29_O_0_New->UseVisualStyleBackColor = true;
			// 
			// groupBox16
			// 
			this->groupBox16->Controls->Add(this->radioButtonB29_I);
			this->groupBox16->Controls->Add(this->radioButtonB29_O_1);
			this->groupBox16->Controls->Add(this->radioButtonB29_O_0);
			this->groupBox16->Location = System::Drawing::Point(56, 128);
			this->groupBox16->Name = L"groupBox16";
			this->groupBox16->Size = System::Drawing::Size(93, 72);
			this->groupBox16->TabIndex = 59;
			this->groupBox16->TabStop = false;
			// 
			// radioButtonB29_I
			// 
			this->radioButtonB29_I->AutoSize = true;
			this->radioButtonB29_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB29_I->Location = System::Drawing::Point(5, 14);
			this->radioButtonB29_I->Name = L"radioButtonB29_I";
			this->radioButtonB29_I->Size = System::Drawing::Size(60, 20);
			this->radioButtonB29_I->TabIndex = 7;
			this->radioButtonB29_I->TabStop = true;
			this->radioButtonB29_I->Text = L"вход";
			this->radioButtonB29_I->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB29_I->UseVisualStyleBackColor = true;
			// 
			// radioButtonB29_O_1
			// 
			this->radioButtonB29_O_1->AutoSize = true;
			this->radioButtonB29_O_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB29_O_1->Location = System::Drawing::Point(5, 46);
			this->radioButtonB29_O_1->Name = L"radioButtonB29_O_1";
			this->radioButtonB29_O_1->Size = System::Drawing::Size(82, 20);
			this->radioButtonB29_O_1->TabIndex = 9;
			this->radioButtonB29_O_1->TabStop = true;
			this->radioButtonB29_O_1->Text = L"выход 1";
			this->radioButtonB29_O_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB29_O_1->UseVisualStyleBackColor = true;
			// 
			// radioButtonB29_O_0
			// 
			this->radioButtonB29_O_0->AutoSize = true;
			this->radioButtonB29_O_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB29_O_0->Location = System::Drawing::Point(5, 29);
			this->radioButtonB29_O_0->Name = L"radioButtonB29_O_0";
			this->radioButtonB29_O_0->Size = System::Drawing::Size(82, 20);
			this->radioButtonB29_O_0->TabIndex = 8;
			this->radioButtonB29_O_0->TabStop = true;
			this->radioButtonB29_O_0->Text = L"выход 0";
			this->radioButtonB29_O_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB29_O_0->UseVisualStyleBackColor = true;
			// 
			// groupBox17
			// 
			this->groupBox17->Controls->Add(this->radioButtonB28_I_New);
			this->groupBox17->Controls->Add(this->radioButtonB28_O_1_New);
			this->groupBox17->Controls->Add(this->radioButtonB28_O_0_New);
			this->groupBox17->Location = System::Drawing::Point(162, 56);
			this->groupBox17->Name = L"groupBox17";
			this->groupBox17->Size = System::Drawing::Size(93, 72);
			this->groupBox17->TabIndex = 58;
			this->groupBox17->TabStop = false;
			// 
			// radioButtonB28_I_New
			// 
			this->radioButtonB28_I_New->AutoSize = true;
			this->radioButtonB28_I_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB28_I_New->Location = System::Drawing::Point(5, 14);
			this->radioButtonB28_I_New->Name = L"radioButtonB28_I_New";
			this->radioButtonB28_I_New->Size = System::Drawing::Size(60, 20);
			this->radioButtonB28_I_New->TabIndex = 7;
			this->radioButtonB28_I_New->TabStop = true;
			this->radioButtonB28_I_New->Text = L"вход";
			this->radioButtonB28_I_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB28_I_New->UseVisualStyleBackColor = true;
			// 
			// radioButtonB28_O_1_New
			// 
			this->radioButtonB28_O_1_New->AutoSize = true;
			this->radioButtonB28_O_1_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB28_O_1_New->Location = System::Drawing::Point(5, 46);
			this->radioButtonB28_O_1_New->Name = L"radioButtonB28_O_1_New";
			this->radioButtonB28_O_1_New->Size = System::Drawing::Size(82, 20);
			this->radioButtonB28_O_1_New->TabIndex = 9;
			this->radioButtonB28_O_1_New->TabStop = true;
			this->radioButtonB28_O_1_New->Text = L"выход 1";
			this->radioButtonB28_O_1_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB28_O_1_New->UseVisualStyleBackColor = true;
			// 
			// radioButtonB28_O_0_New
			// 
			this->radioButtonB28_O_0_New->AutoSize = true;
			this->radioButtonB28_O_0_New->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButtonB28_O_0_New->Location = System::Drawing::Point(5, 29);
			this->radioButtonB28_O_0_New->Name = L"radioButtonB28_O_0_New";
			this->radioButtonB28_O_0_New->Size = System::Drawing::Size(82, 20);
			this->radioButtonB28_O_0_New->TabIndex = 8;
			this->radioButtonB28_O_0_New->TabStop = true;
			this->radioButtonB28_O_0_New->Text = L"выход 0";
			this->radioButtonB28_O_0_New->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB28_O_0_New->UseVisualStyleBackColor = true;
			// 
			// groupBox18
			// 
			this->groupBox18->Controls->Add(this->radioButtonB28_I);
			this->groupBox18->Controls->Add(this->radioButtonB28_O_1);
			this->groupBox18->Controls->Add(this->radioButtonB28_O_0);
			this->groupBox18->Location = System::Drawing::Point(56, 56);
			this->groupBox18->Name = L"groupBox18";
			this->groupBox18->Size = System::Drawing::Size(93, 72);
			this->groupBox18->TabIndex = 57;
			this->groupBox18->TabStop = false;
			// 
			// radioButtonB28_I
			// 
			this->radioButtonB28_I->AutoSize = true;
			this->radioButtonB28_I->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB28_I->Location = System::Drawing::Point(5, 14);
			this->radioButtonB28_I->Name = L"radioButtonB28_I";
			this->radioButtonB28_I->Size = System::Drawing::Size(60, 20);
			this->radioButtonB28_I->TabIndex = 7;
			this->radioButtonB28_I->TabStop = true;
			this->radioButtonB28_I->Text = L"вход";
			this->radioButtonB28_I->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB28_I->UseVisualStyleBackColor = true;
			// 
			// radioButtonB28_O_1
			// 
			this->radioButtonB28_O_1->AutoSize = true;
			this->radioButtonB28_O_1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB28_O_1->Location = System::Drawing::Point(5, 46);
			this->radioButtonB28_O_1->Name = L"radioButtonB28_O_1";
			this->radioButtonB28_O_1->Size = System::Drawing::Size(82, 20);
			this->radioButtonB28_O_1->TabIndex = 9;
			this->radioButtonB28_O_1->TabStop = true;
			this->radioButtonB28_O_1->Text = L"выход 1";
			this->radioButtonB28_O_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB28_O_1->UseVisualStyleBackColor = true;
			// 
			// radioButtonB28_O_0
			// 
			this->radioButtonB28_O_0->AutoSize = true;
			this->radioButtonB28_O_0->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButtonB28_O_0->Location = System::Drawing::Point(5, 29);
			this->radioButtonB28_O_0->Name = L"radioButtonB28_O_0";
			this->radioButtonB28_O_0->Size = System::Drawing::Size(82, 20);
			this->radioButtonB28_O_0->TabIndex = 8;
			this->radioButtonB28_O_0->TabStop = true;
			this->radioButtonB28_O_0->Text = L"выход 0";
			this->radioButtonB28_O_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->radioButtonB28_O_0->UseVisualStyleBackColor = true;
			// 
			// set_PB30
			// 
			this->set_PB30->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->set_PB30->Location = System::Drawing::Point(261, 222);
			this->set_PB30->Name = L"set_PB30";
			this->set_PB30->Size = System::Drawing::Size(94, 32);
			this->set_PB30->TabIndex = 43;
			this->set_PB30->Text = L"Задать";
			this->set_PB30->UseVisualStyleBackColor = true;
			this->set_PB30->Click += gcnew System::EventHandler(this, &Interface::set_PB30_Click);
			// 
			// set_PB29
			// 
			this->set_PB29->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->set_PB29->Location = System::Drawing::Point(261, 151);
			this->set_PB29->Name = L"set_PB29";
			this->set_PB29->Size = System::Drawing::Size(94, 32);
			this->set_PB29->TabIndex = 42;
			this->set_PB29->Text = L"Задать";
			this->set_PB29->UseVisualStyleBackColor = true;
			this->set_PB29->Click += gcnew System::EventHandler(this, &Interface::set_PB29_Click);
			// 
			// set_PB28
			// 
			this->set_PB28->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->set_PB28->Location = System::Drawing::Point(261, 78);
			this->set_PB28->Name = L"set_PB28";
			this->set_PB28->Size = System::Drawing::Size(94, 32);
			this->set_PB28->TabIndex = 41;
			this->set_PB28->Text = L"Задать";
			this->set_PB28->UseVisualStyleBackColor = true;
			this->set_PB28->Click += gcnew System::EventHandler(this, &Interface::set_PB28_Click);
			// 
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(154, 25);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(118, 36);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Настроить состояние";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(53, 25);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(101, 36);
			this->label5->TabIndex = 5;
			this->label5->Text = L"Текущее состояние";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 229);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(29, 20);
			this->label6->TabIndex = 4;
			this->label6->Text = L"30";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(10, 157);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(29, 20);
			this->label7->TabIndex = 3;
			this->label7->Text = L"29";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(10, 85);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(29, 20);
			this->label10->TabIndex = 2;
			this->label10->Text = L"28";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(15, 32);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(25, 20);
			this->label12->TabIndex = 0;
			this->label12->Text = L"№";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->create_chart_button);
			this->groupBox1->Controls->Add(this->label11);
			this->groupBox1->Controls->Add(this->numericUpDown_time);
			this->groupBox1->Controls->Add(this->chart1);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->label_data_signal);
			this->groupBox1->Controls->Add(this->read_signalPB);
			this->groupBox1->Controls->Add(this->read_signalPA);
			this->groupBox1->Controls->Add(this->label_PB);
			this->groupBox1->Controls->Add(this->numericUpDownPB);
			this->groupBox1->Controls->Add(this->label_PA);
			this->groupBox1->Controls->Add(this->numericUpDownPA);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->groupBox1->ForeColor = System::Drawing::Color::Black;
			this->groupBox1->Location = System::Drawing::Point(789, 45);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(554, 580);
			this->groupBox1->TabIndex = 17;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Считывание сигнала";
			// 
			// create_chart_button
			// 
			this->create_chart_button->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->create_chart_button->Location = System::Drawing::Point(138, 186);
			this->create_chart_button->Name = L"create_chart_button";
			this->create_chart_button->Size = System::Drawing::Size(115, 52);
			this->create_chart_button->TabIndex = 14;
			this->create_chart_button->Text = L"Построить график";
			this->create_chart_button->UseVisualStyleBackColor = true;
			this->create_chart_button->Click += gcnew System::EventHandler(this, &Interface::create_chart_button_Click);
			// 
			// label11
			// 
			this->label11->Location = System::Drawing::Point(357, 16);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(165, 28);
			this->label11->TabIndex = 13;
			this->label11->Text = L"Время замера, с";
			this->label11->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// numericUpDown_time
			// 
			this->numericUpDown_time->Location = System::Drawing::Point(415, 47);
			this->numericUpDown_time->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
			this->numericUpDown_time->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->numericUpDown_time->Name = L"numericUpDown_time";
			this->numericUpDown_time->Size = System::Drawing::Size(53, 26);
			this->numericUpDown_time->TabIndex = 12;
			this->numericUpDown_time->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(6, 247);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(542, 327);
			this->chart1->TabIndex = 10;
			this->chart1->Text = L"chart1";
			// 
			// button3
			// 
			this->button3->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button3->Location = System::Drawing::Point(6, 186);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(115, 52);
			this->button3->TabIndex = 9;
			this->button3->Text = L"Сохранить в файл";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// label_data_signal
			// 
			this->label_data_signal->BackColor = System::Drawing::SystemColors::Control;
			this->label_data_signal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_data_signal->ForeColor = System::Drawing::Color::Black;
			this->label_data_signal->Location = System::Drawing::Point(6, 22);
			this->label_data_signal->Name = L"label_data_signal";
			this->label_data_signal->Size = System::Drawing::Size(247, 161);
			this->label_data_signal->TabIndex = 8;
			// 
			// read_signalPB
			// 
			this->read_signalPB->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->read_signalPB->Location = System::Drawing::Point(260, 148);
			this->read_signalPB->Name = L"read_signalPB";
			this->read_signalPB->Size = System::Drawing::Size(94, 35);
			this->read_signalPB->TabIndex = 5;
			this->read_signalPB->Text = L"Считать";
			this->read_signalPB->UseVisualStyleBackColor = true;
			this->read_signalPB->Click += gcnew System::EventHandler(this, &Interface::read_signalPB_Click);
			// 
			// read_signalPA
			// 
			this->read_signalPA->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->read_signalPA->Location = System::Drawing::Point(260, 57);
			this->read_signalPA->Name = L"read_signalPA";
			this->read_signalPA->Size = System::Drawing::Size(94, 35);
			this->read_signalPA->TabIndex = 4;
			this->read_signalPA->Text = L"Считать";
			this->read_signalPA->UseVisualStyleBackColor = true;
			this->read_signalPA->Click += gcnew System::EventHandler(this, &Interface::read_signalPA_Click);
			// 
			// label_PB
			// 
			this->label_PB->AutoSize = true;
			this->label_PB->Location = System::Drawing::Point(259, 115);
			this->label_PB->Name = L"label_PB";
			this->label_PB->Size = System::Drawing::Size(32, 20);
			this->label_PB->TabIndex = 3;
			this->label_PB->Text = L"PB";
			// 
			// numericUpDownPB
			// 
			this->numericUpDownPB->Location = System::Drawing::Point(297, 113);
			this->numericUpDownPB->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->numericUpDownPB->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 28, 0, 0, 0 });
			this->numericUpDownPB->Name = L"numericUpDownPB";
			this->numericUpDownPB->Size = System::Drawing::Size(57, 26);
			this->numericUpDownPB->TabIndex = 2;
			this->numericUpDownPB->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 28, 0, 0, 0 });
			// 
			// label_PA
			// 
			this->label_PA->AutoSize = true;
			this->label_PA->Location = System::Drawing::Point(256, 24);
			this->label_PA->Name = L"label_PA";
			this->label_PA->Size = System::Drawing::Size(32, 20);
			this->label_PA->TabIndex = 1;
			this->label_PA->Text = L"PA";
			// 
			// numericUpDownPA
			// 
			this->numericUpDownPA->Location = System::Drawing::Point(294, 22);
			this->numericUpDownPA->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 30, 0, 0, 0 });
			this->numericUpDownPA->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 28, 0, 0, 0 });
			this->numericUpDownPA->Name = L"numericUpDownPA";
			this->numericUpDownPA->Size = System::Drawing::Size(57, 26);
			this->numericUpDownPA->TabIndex = 0;
			this->numericUpDownPA->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 28, 0, 0, 0 });
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(1522, 709);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->groupBox12);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox_conn_label);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Interface";
			this->Text = L"INTERFACE AT91SAM7X256";
			this->Load += gcnew System::EventHandler(this, &Interface::Interface_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox_conn_label->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox11->ResumeLayout(false);
			this->groupBox11->PerformLayout();
			this->groupBox10->ResumeLayout(false);
			this->groupBox10->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->number_to_increase))->EndInit();
			this->groupBox12->ResumeLayout(false);
			this->groupBox12->PerformLayout();
			this->groupBox13->ResumeLayout(false);
			this->groupBox13->PerformLayout();
			this->groupBox14->ResumeLayout(false);
			this->groupBox14->PerformLayout();
			this->groupBox15->ResumeLayout(false);
			this->groupBox15->PerformLayout();
			this->groupBox16->ResumeLayout(false);
			this->groupBox16->PerformLayout();
			this->groupBox17->ResumeLayout(false);
			this->groupBox17->PerformLayout();
			this->groupBox18->ResumeLayout(false);
			this->groupBox18->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown_time))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownPB))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDownPA))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//Функции инициализации сокета и работы с подключением
	private: System::Void EthernetAT91SAM7X256Interface::Interface::ipInit(int erStat, in_addr& ip_to_num); //Инициализация IP-адреса
	private: System::Void EthernetAT91SAM7X256Interface::Interface::sockInterfaces(int erStat, WSADATA& wsdata);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::sockInit(SOCKET& Sock);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::ipPortConnect(int erStat, sockaddr_in& servInfo, in_addr& ip_to_num, SOCKET& ClientSock);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::open_conn();
	private: System::Void EthernetAT91SAM7X256Interface::Interface::close_conn(SOCKET ClientConn);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::UpdateChart(List<int>^ time, List<int>^ data_dots);

	//Поточные функции обновления лейблов
	private: System::Void EthernetAT91SAM7X256Interface::Interface::AppendLabel(System::Windows::Forms::Label^ label, System::String^ text);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::UpdateLabel(System::Windows::Forms::Label^ label, System::String^ text);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::threadAbort(System::Threading::Thread^ thread);
	
	//Кнопки
	private: System::Void close_conn_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void open_conn_button_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_info_board_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void set_PA28_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void set_PA29_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void set_PA30_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void set_PB28_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void set_PB29_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void set_PB30_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void read_signalPB_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void read_signalPA_Click(System::Object^ sender, System::EventArgs^ e);

	//Функции обмена данными
	private: System::Void EthernetAT91SAM7X256Interface::Interface::sendNumbMessage(SOCKET* sock, int numb, short int packetSize);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::recMessageLabel(SOCKET* sock, short int packetSize, Label^ label);
	private: System::String^ EthernetAT91SAM7X256Interface::Interface::recMessageBox(SOCKET* sock, short int packetSize);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::infoFromServer(SOCKET* sock, short int packet_size, short int state, Label^ label);
	private: System::Void button_info_date_compilation_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void send_number_to_increase_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::sendCharMessage(String^ message, short int packetSize);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::radio_button_set(RadioButton^ r_Input_New, RadioButton^ r_Output_0_New, RadioButton^ r_Output_1_New,
																					 RadioButton^ r_Input_Cur, RadioButton^ r_Output_0_Cur, RadioButton^ r_Output_1_Cur,
																					 String^ message1, String^ message2, String^ message3);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::ShowWaitingAnimation();
	private: System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPin(String^ letter, int number, int time, RadioButton^ radioButton);
	private: System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadA();
	private: System::Void EthernetAT91SAM7X256Interface::Interface::signalProcessPinThreadB();
	private: System::Void EthernetAT91SAM7X256Interface::Interface::chartData();
	private: System::Void информацияОПрограммеToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void create_chart_button_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void Interface_Load(System::Object^ sender, System::EventArgs^ e) {
}
};
}
