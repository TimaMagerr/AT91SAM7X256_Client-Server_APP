#include "hello-world.h"
#include "uip.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <stdbool.h>
#include "tapdev.h" //������ MAC-�����
#include "timer.h"
#include <stdint.h>


#define PORT1 1000
#define startPIN 28 //C ����� ���� ���������� ������ ������
#define COUNT_PINS 3 //���-�� �����

/*****��������� �����������*****/
//������ ����������� PIN29 � PIN30: �����, �����, ID �����������, ��� �����, ��������	
#define PINB_29_OUTPUT {1 << 29, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
#define PINB_30_INPUT {1 << 30, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_INPUT, PIO_PULLUP | PIO_DEGLITCH}

static const Pin pinPB29 = PINB_29_OUTPUT;
static const Pin pinPB30 = PINB_30_INPUT;


static Pin pinConfigsA[COUNT_PINS] = {
    {1 << 28, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}, 
    {1 << 29, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}, 
		{1 << 30, AT91C_BASE_PIOA, AT91C_ID_PIOA, PIO_OUTPUT_0, PIO_DEFAULT}
};

static Pin pinConfigsB[COUNT_PINS] = {
    {1 << 28, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}, 
    {1 << 29, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}, 
		{1 << 30, AT91C_BASE_PIOB, AT91C_ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT}
};

//��������� ��������� ����
void setPinState(Pin *pinConfigs, int pinNumber, int state, struct ethernet_state *s);

//��������� ������� � ��������� ��� �������������
//static int SignalTask(struct pt *pt, char *staticBuffer, struct sData *data, int time, Pin *pinConfigs, int pinNumber, bool *flag);
//������ � �������� ��� �����������
signalData SignalTask(struct ethernet_state *s, int time, Pin *pinConfigs, int pinNumber);
static int fib(struct pt *pt, int max, int* res, bool *flag); 

void listen_port(void)
{
  /* ��������� TCP-����� (1000-���)  */
  uip_listen(HTONS(PORT1));
}

// ������� ��� ���������� ������ �� ��� �����
void parse_message(struct ethernet_state *s) {
	char *token;

	// ��������� ������ �� ������� ';'
	token = strtok(s->inputBuffer, ";"); 
	if (token != NULL) {
			strcpy(s->port_letter, token); // �������� ����� �����
	}

	token = strtok(NULL, ";"); 
	if (token != NULL) {
			strcpy(s->port_number, token); // �������� ����� �����
	}

	token = strtok(NULL, ";");
	if (token != NULL) {
			strcpy(s->output_state, token); // �������� ��������� ������
	}
}

// ������� ��� ���������� ���������� ����
void setPinState(Pin *pinConfigs, int pinNumber, int state, struct ethernet_state *s) {
	Pin *pin = &pinConfigs[pinNumber-startPIN]; // ��������� ������ �� ��������� ����
	// ��������� ���� ���� � ����������� �� ���������
	if (state == 0) {
			pin->type = PIO_OUTPUT_0; // �������� ������
	} else if (state == 1) {
			pin->type = PIO_OUTPUT_1; // �������� ������
	} else if (state == 2) {
			pin->type = PIO_INPUT; // ������� ������
	}

	memset(s->sendBuffer, 0, sizeof(s->sendBuffer));
	if(PIO_Configure(pin, 1) == 1)//����������� ���
		strncpy(s->sendBuffer, "Configure success! Great!", sizeof(s->sendBuffer)); 
	else 
		strncpy(s->sendBuffer, "Configure failed :(", sizeof(s->sendBuffer)); 
}

void clientPinSettings(struct ethernet_state *s){
	//������� ������ 
	memset(s->port_letter, 0, sizeof(s->port_letter)); // �������� ���� �����
	memset(s->port_number, 0, sizeof(s->port_number)); // �������� ���� �����
	memset(s->output_state, 0, sizeof(s->output_state)); // �������� ���� �����

	//��������� ��������� �� 3 ����������
	parse_message(s);
	
	int pinNumb = atoi(s->port_number); //��������� ������ ������ ����� � ����� 
	int outputState = atoi(s->output_state); //��������� ������ ������ ��������� � �����
	
	//���������, ���� A ��� ���� �
	if(s->port_letter[0] == 'A'){
		setPinState(pinConfigsA, pinNumb, outputState, s); //� ������������ PIN � ���������� �������������
	}
	else if(s->port_letter[0] == 'B'){
		setPinState(pinConfigsB, pinNumb, outputState, s);
	}
}

static int defaultConfigurePins(struct ethernet_state *s){
	//������������� ���� �� ��������� �� ����� � 0
	int i;
	PSOCK_BEGIN(&s->p);	
	for(i = 0; i < COUNT_PINS; i++){
		setPinState(pinConfigsA, startPIN+i, 0, s);
		setPinState(pinConfigsB, startPIN+i, 0, s);
	}

	if(PIO_Configure(pinConfigsA, COUNT_PINS) == 1 && PIO_Configure(pinConfigsB, COUNT_PINS) == 1
		&& (s->state == CLOSE_CONNECT || s->state == SUCCESS_CONNECT))
		PSOCK_SEND_STR(&s->p, "Welcome! PINs are configured in the starting positions!");
	else
		PSOCK_SEND_STR(&s->p, "Welcome! PINs are not configured in the starting positions!");
	PSOCK_CLOSE(&s->p);
	PSOCK_END(&s->p);
}

static int fib(struct pt *pt, int max, int* res, bool *flag) {
	static int a,b;
	PT_BEGIN(pt);
	a=0;b=1;
	while (a<max) {
		*res=a;
		PT_YIELD(pt);
		b+=a;
		a=b-a;
	}
	*flag = false;
	PT_WAIT_WHILE(pt,1);
	PT_END(pt);
}


signalData SignalTask(struct ethernet_state *s, int time, Pin *pinConfigs, int pinNumber){
	/* ���������� ��� ������ ������������� ������� */
	uint16_t start_rising_edge_time = 0; //����� ������������� ������������ ������ (��)
	uint16_t end_falling_edge_time = 0; //����� ��������� ���������� ������ (��)
	uint16_t current_time = 0; //������� ����� (��)
	uint16_t start_pulse_t = 0; //������ ��������
	uint16_t end_pulse_t = 0; //����� ��������
	uint8_t current_front_condition = 0; //������� ��������� ������ (1 ��� 0)
	uint8_t new_front_condition; //����� ��������� ������ (1 ��� 0)
	uint8_t count_front_condition = 0; //������� ��������� �������
	
	struct timer calcTime; //������ ��� �������� ������� � ������� �������
	signalData data = {0}; //������� ��������� ��� �������� �������������� �������
	timer_set(&calcTime, CLOCK_SECOND * time); //��������� ����� �����
	
	while(1){
		/*�������� �������������� �������*/
		//rectangleSignal(&delay_timer);
		
		//��������� ��������� ������� � ������ �������, �������
		new_front_condition = PIO_Get(&pinConfigs[pinNumber-startPIN]); //�������� ��������� �������
		//current_time = clock_time(); //��������� ������� �����
		
		//C�������� ������ ����� PB30
		if(current_front_condition == 0 && new_front_condition == 1 ){ //����������� ����� 0 __/ 1
			start_pulse_t = clock_time(); //��������� ������ ��������
			count_front_condition++;
			if(count_front_condition % 2 == 0){ //���� �������� ��� ���� ����������� ����� - ������ ������
				end_falling_edge_time = clock_time(); //��������� �����
				count_front_condition = 1; //����� ������� ����������� �����
				data.period = (float)(end_falling_edge_time - start_rising_edge_time)/1000.0; //������ ���� �������� ��� �������� �������� (�� -> c)
				if(data.period != 0.0){
					data.frequency = 1.0/data.period; //������ ���� ������ ��� �������� ������� (��)
					data.period_sum += data.period; //��������� ������ � ������ �������� ��������
					data.frequency_sum += data.frequency; //��������� ������� � ������ �������� ������
				}
				else
					printf("Period = 0\n");
			}
			start_rising_edge_time = clock_time(); //��������� ����� ������ ������� �������
			current_front_condition = 1; //������� ������
		}
			else if (current_front_condition == 1 && new_front_condition == 0){ //���������� ����� 1 \__ 0
				end_pulse_t = clock_time(); //��������� ����� ��������
				data.pulse_duration = (end_pulse_t - start_pulse_t)/1000.0; //�������� ������������ �������� (��->�)
				data.pulse_count++; //��������� �������
				current_front_condition = 0; //������ ������
		}	
		if(data.period != 0 && data.pulse_duration != 0){
			data.duty_cycle = data.period / data.pulse_duration; //������������ ����������
			data.fill_factor = 1.0/data.duty_cycle; //������������ �����. ����������
		}
		if (timer_expired(&calcTime))
			break; //��������� ������� �� ��������� �������
	}
	data.period_avg = data.period_sum /(float)data.pulse_count; //������� ������
	data.frequency_avg = data.frequency_sum / (float)data.pulse_count; //������� �������
}

void dataSendSignalTask(struct ethernet_state *s, int portNumber, signalData data){
	memset(s->sendBuffer, 0, sizeof(s->sendBuffer)); // �������� ���� �����
	snprintf(s->sendBuffer, sizeof(s->sendBuffer),"period: %f s\nperiod_avg: %f s\nfrequency: %f Hz\nfrequency_avg: %f Hz\n"
					"duty cycle: %f s\nfill factor: %f s\n"
					"pulse count: %d\npulse duration: %f s\n",
					data.period, data.period_avg, data.frequency, data.frequency_avg,
					data.duty_cycle, data.fill_factor,
					data.pulse_count, data.pulse_duration); //��������� ������ � �������
	//uip_send(s->sendBuffer, strlen(s->sendBuffer)); //���������� ������
}


int rectangleSignal(struct timer *timer){
	if(timer_expired(timer)){
		//���� ���������� ������� ������
		if(PIO_Get(&pinPB29) == 1){
			PIO_Clear(&pinPB29); //������ ������
			printf("PB29: Low - %d\n", PIO_Get(&pinPB29));
		} else{ //���� ������, �� �������� - ������ �������
			PIO_Set(&pinPB29);
			printf("PB29: High - %d\n", PIO_Get(&pinPB29));
		}
		timer_reset(timer);
	}
	return PIO_Get(&pinPB29);
}

//���������� � ������� � �����
void infoAbout(struct ethernet_state *s, char message[]){
	
	uip_send(message, strlen(message));
}

int charToInt(struct ethernet_state *s){
	//������� ����� ��� ����������� �����
	memset(s->inputBuffer, 0, sizeof(s->inputBuffer)); // �������� ���� �����
	//��������� ������
	char *data = (char*)uip_appdata; //data ��������� �� �������������� ������
	int len = uip_datalen(); //���������� ���������� ����� ��� ��������
	strncpy(s->inputBuffer, data, len); //�������� ������ � ����� received_number
	int number = atoi(s->inputBuffer); //��������� ������� � �����
	return number;
}

void recvMessage(struct ethernet_state *s){
	//������� ����� ��� ����������� �����
	memset(s->inputBuffer, 0, sizeof(s->inputBuffer)); // �������� ���� �����
	//��������� ������
	char *data = (char*)uip_appdata; //data ��������� �� �������������� ������
	int len = uip_datalen(); //���������� ���������� ����� ��� ��������
	strncpy(s->inputBuffer, data, len); //�������� ������ � ����� 
	//printf("%s", s->inputBuffer);
}

//��������� �����, ��������� � ���������� ������� 
void doubleNumber(struct ethernet_state *s){
	int number = charToInt(s);
	//������ � ������
	int doubleNumber = number * 2; //����������� ���������� �������� � ��� ����
	char response[10];
	sprintf(response, "%d", doubleNumber); //�������� ����� � ���������� ������
	uip_send(response, strlen(response)); //���������� �����
	printf("Send data\n");
}


//��������� �����, ��������� � ���������� ������� 
void doubleNumbSock(struct ethernet_state *s){
	int number = 0;
	//������ � ������
	number = atoi(s->sockBuffer) * 2; //����������� ���������� �������� � ��� ����
	memset(s->sendBuffer, 0, sizeof(s->sendBuffer));
	snprintf(s->sendBuffer, sizeof(s->sendBuffer), "%d", number); //�������� ����� � ���������� ������
}


static int selectorSock(struct ethernet_state *s, char* message_board, char* message_project) {
	PSOCK_BEGIN(&s->p);
	int client_state = 0; //��������� ������
	s->state = NEUTRAL; //����������� ���������
	while(1) {
		//�������� ������
		memset(s->sockBuffer, 0, sizeof(s->sockBuffer));
		if (client_state == 0) {
			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			client_state = atoi(s->sockBuffer);
		}
		
		//���� �������� � ��������� ���������
		if(client_state == 1){ //�������� ��������� � �����
			s->state = INFO_BOARD;
			
			strncpy(s->sendBuffer, message_board, sizeof(s->sendBuffer));
			PSOCK_SEND_STR(&s->p, s->sendBuffer); //������� ������ ���������� � ����� � �������
			
			s->state = NEUTRAL;
			client_state = 0;
		} 
		else if(client_state == 2){ //�������� ��������� � ���� �������
			s->state = INFO_DATE;
			
			PSOCK_SEND_STR(&s->p, message_project); //������� ������ ���������� � ����� � �������
			
			s->state = NEUTRAL;
			client_state = 0;
		}
		else if(client_state == 3){ //��������� ���������� ����� � ���������� �������
			s->state = DOUBLE_NUMB;
			
			memset(s->sockBuffer, 0, sizeof(s->sockBuffer));
			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			doubleNumbSock(s);
			PSOCK_SEND_STR(&s->p, s->sendBuffer);
			
			s->state = NEUTRAL;
			client_state = 0;
		}
		else if(client_state == 4){ //������ � ��������
			s->state = SIGNAL_INFO;
			
			memset(s->sockBuffer, 0, sizeof(s->sockBuffer));
			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			strncpy(s->inputBuffer, s->sockBuffer, sizeof(s->inputBuffer)); //�������� ������ � �����

			//������� ������ 
			memset(s->port_letter, 0, sizeof(s->port_letter)); // �������� ���� �����
			memset(s->port_number, 0, sizeof(s->port_number)); // �������� ���� �����
			memset(s->output_state, 0, sizeof(s->output_state)); // �������� ���� �����
			
			//��������� ��������� �� 3 ����������
			parse_message(s);
			
			int pinNumb = atoi(s->port_number); //��������� ������ ������ ����� � ����� 
			int time = atoi(s->output_state); //� ������ ������ �������� ����� ����� ������� ������� ;
			
			memset(s->sendBuffer, 0, sizeof(s->sendBuffer));
			/*
			snprintf(s->sendBuffer, sizeof(s->sendBuffer), "%s;%d;%d", s->port_letter, pinNumb, time);
			PSOCK_SEND_STR(&s->p, "Che");*/
			
			signalData data = {0};
			
			if(s->port_letter[0] == 'A'){
				data = SignalTask(s, time, pinConfigsA, pinNumb);
				dataSendSignalTask(s, pinNumb, data);
				PSOCK_SEND_STR(&s->p, s->sendBuffer);
			}
			else if(s->port_letter[0] == 'B'){
				data = SignalTask(s, time, pinConfigsB, pinNumb);
				dataSendSignalTask(s, pinNumb, data);
				PSOCK_SEND_STR(&s->p, s->sendBuffer);
			}
			
			s->state = NEUTRAL;
			client_state = 0;
		}
		else if(client_state == 5){ //������������ �����
			s->state = PIN_CONF;

			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			strncpy(s->inputBuffer, s->sockBuffer, sizeof(s->inputBuffer)); //�������� ������ � �����
			
			clientPinSettings(s); //������� ������������ ����
			
			PSOCK_SEND_STR(&s->p, s->sendBuffer);//���������� ��������� ��������� ����
			
			s->state = NEUTRAL;
			client_state = 0;
		}
		else{
			PSOCK_SEND_STR(&s->p, s->sockBuffer);
			client_state = 0;
		}
	}
	
	PSOCK_CLOSE(&s->p);
	PSOCK_END(&s->p);
}

void selectApp(){
	
	//������-��������
	char *Selector =
		"1. Find out the status of the device (what kind of device, etc.)\n"
		"2. Info about date\n"
		"3. Calculation (double value)\n"
		"4. Info about signal\n";
	/*����� ��������� �����, ������� ���������� ����� �� � ����������� ������
		��������������� ������ (� ������� 10 �, ��������), ����� ����� �������,
		��� ������ ������*/
	
	
	//��������� ��� ������� ������ � ���������
	char message_board[256];
	snprintf(message_board, sizeof(message_board),
	//����������� ��� ��������� � ���� ����������
	"-- EMAC uIP Project %s --\n\r" 
	"-- BOARD: %s\n\r"
	" - MAC %02x:%02x:%02x:%02x:%02x:%02x\n\n" 
	"Frequency of generator: %d",
	SOFTPACK_VERSION, 
	BOARD_NAME, 
	MacAddress.addr[0], MacAddress.addr[1], MacAddress.addr[2],
	MacAddress.addr[3], MacAddress.addr[4], MacAddress.addr[5],
	BOARD_MAINOSC);
	
	//��������� ��� ������� ������ � ���������
	char message_project[256];
	snprintf(message_project, sizeof(message_project),
	"-- Compiled: %s %s --",
	__DATE__, __TIME__);
	
	//��������� ��� �������� ������ � ���������
	char* stateNumb = "State 3: calculation";
	
	//��������� ��� ���������� ������ � ���������
	char* stateSignal = "State 4: signal";
	
	//������� ��������� ��������� ��� �������� ��������� �����������
	struct ethernet_state *s = &(uip_conn->appstate);
	
	//������������� ���� � ���������� �� ��������� �������
	if(uip_connected()) {
		PSOCK_INIT(&s->p, s->sockBuffer, sizeof(s->sockBuffer));	
		printf("Client connection success\n");
		//�������� ��������
		Pin Led_Conn_Indicator = LED_IND_ON;
		PIO_Configure(&Led_Conn_Indicator, 1);
		
		s->state = SUCCESS_CONNECT; //����������� ���������
		defaultConfigurePins(s);
	} 
	
	selectorSock(s, message_board, message_project);
}
