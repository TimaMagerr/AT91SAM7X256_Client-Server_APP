/**
 * \addtogroup apps
 * @{
 */

/**
 * \defgroup helloworld Hello, world
 * @{
 *
 * A small example showing how to write applications with
 * \ref psock "protosockets".
 */

/**
 * \file
 *         Header file for an example of how to write uIP applications
 *         with protosockets.
 * \author
 *         Adam Dunkels <adam@sics.se>
 */

#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

/* Since this file will be included by uip.h, we cannot include uip.h
   here. But we might need to include uipopt.h if we need the u8_t and
   u16_t datatypes. */
#include "uipopt.h"
#include "pt.h"
#include "timer.h"
#include "psock.h"
#include <stdint.h>


//���������, �������� ������ ��������� (�����������, ������������� �����������, �������� �����) 
typedef struct ethernet_state{
	struct psock p, p1;
	char sockBuffer[256];
	char inputBuffer[256]; //������ ��� ��������
	char sendBuffer[256]; //������ ��� ��������
	
	//���������� ��� ��������:
	char port_letter[2]; //����� �����
	char port_number[5]; //����� �����
	char output_state[5]; //��������� ����� (0 - ����� 0, 1 - ����� 1, 2 - ����)
	
	enum {SUCCESS_CONNECT, NEUTRAL, INFO_BOARD, INFO_DATE, DOUBLE_NUMB, SIGNAL_INFO, PIN_CONF, CLOSE_CONNECT} state;
}uip_tcp_appstate_t;

//���������, �������� �������������� �������
typedef struct sData{
	float period; //������
	float period_sum; //��� �������
	float period_count; //���-�� ��������
	float period_avg; //������ �������
	float frequency; //�������
	float frequency_sum; //������� ���
	float frequency_avg; //������� �������
	float duty_cycle; //����������
	float fill_factor; //����������� ����������
	uint8_t pulse_count; //���-�� ���������
	float pulse_duration; //������������ ��������
	float pulse_duration_max; //������������ �������� ������������
	float pulse_duration_min; //������������ �������� �����������
	float pulse_duration_avg; //������������ ��������
} signalData;


//��������� �����
void listen_port(void);

//��������� ��������� ��������� �� 3 ��� ���������� �����������
void parse_message(struct ethernet_state *s);
	
//�������� ������������� �������
void dataSendSignalTask(struct ethernet_state *s, int portNumber, signalData data);

//������� ������������� ������ �� �������� �����
int rectangleSignal(struct timer *timer);

//����� �������� ���������� � ������� � ������ � ���� ����������
void infoAbout(struct ethernet_state *s, char* message); //������� uip

//��������� ���������� ���������� ������ � �����
int charToInt(struct ethernet_state *s);

//������ ��������� ���������� ���������
void recvMessage(struct ethernet_state *s);

//��������� ���������� ����� � ���������� �������
void doubleNumber(struct ethernet_state *s); //������� uip

void clientPinSettings(struct ethernet_state *s);

static int defaultConfigurePins(struct ethernet_state *s);

static int handle_connection(struct ethernet_state *s);

void doubleNumbSock(struct ethernet_state *s);

static int selectorSock(struct ethernet_state *s, char* message_board, char* message_project);

//�������� ������� uip
void selectApp();

//����� ������������ �������� ������� ������ ��� �������������� ������-������
#ifndef UIP_APPCALL
#define UIP_APPCALL selectApp
#endif /* UIP_APPCALL */


#endif /* __HELLO_WORLD_H__ */
/** @} */
/** @} */
