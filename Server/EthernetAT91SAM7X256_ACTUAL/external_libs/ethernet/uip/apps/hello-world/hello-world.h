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


//Структура, хранящая список состояний (подключение, подтверждение подключения, принятое число) 
typedef struct ethernet_state{
	struct psock p, p1;
	char sockBuffer[256];
	char inputBuffer[256]; //Буффер для принятия
	char sendBuffer[256]; //Буффер для отправки
	
	//Переменные для хранения:
	char port_letter[2]; //Буква порта
	char port_number[5]; //Номер порта
	char output_state[5]; //Состояние порта (0 - выход 0, 1 - выход 1, 2 - вход)
	
	enum {SUCCESS_CONNECT, NEUTRAL, INFO_BOARD, INFO_DATE, DOUBLE_NUMB, SIGNAL_INFO, PIN_CONF, CLOSE_CONNECT} state;
}uip_tcp_appstate_t;

//Структура, хранящая характеристики сигнала
typedef struct sData{
	float period; //Период
	float period_sum; //Все периоды
	float period_count; //Кол-во периодов
	float period_avg; //Период средний
	float frequency; //Частота
	float frequency_sum; //Частоты все
	float frequency_avg; //Частота средняя
	float duty_cycle; //Скважность
	float fill_factor; //Коэффициент заполнения
	uint8_t pulse_count; //Кол-во импульсов
	float pulse_duration; //Длительность импульса
	float pulse_duration_max; //Длительность импульса максимальная
	float pulse_duration_min; //Длительность импульса минимальная
	float pulse_duration_avg; //Длительность импульса
} signalData;


//Прослушка порта
void listen_port(void);

//Разбиение входящего сообщения на 3 при нахождении разделителя
void parse_message(struct ethernet_state *s);
	
//Отправка характеристик сигнала
void dataSendSignalTask(struct ethernet_state *s, int portNumber, signalData data);

//Создаем прямоугольный сигнал на выходной ножке
int rectangleSignal(struct timer *timer);

//Можем выводить информацию о проекте с платой и дате компиляции
void infoAbout(struct ethernet_state *s, char* message); //Обычный uip

//Переводим полученные символьные данные в число
int charToInt(struct ethernet_state *s);

//Просто принимаем символьное сообщение
void recvMessage(struct ethernet_state *s);

//Удваиваем полученное число и отправляем обратно
void doubleNumber(struct ethernet_state *s); //Обычный uip

void clientPinSettings(struct ethernet_state *s);

static int defaultConfigurePins(struct ethernet_state *s);

static int handle_connection(struct ethernet_state *s);

void doubleNumbSock(struct ethernet_state *s);

static int selectorSock(struct ethernet_state *s, char* message_board, char* message_project);

//Основная функция uip
void selectApp();

//Здесь определяется основная функция вызова для взаимодействия клиент-сервер
#ifndef UIP_APPCALL
#define UIP_APPCALL selectApp
#endif /* UIP_APPCALL */


#endif /* __HELLO_WORLD_H__ */
/** @} */
/** @} */
