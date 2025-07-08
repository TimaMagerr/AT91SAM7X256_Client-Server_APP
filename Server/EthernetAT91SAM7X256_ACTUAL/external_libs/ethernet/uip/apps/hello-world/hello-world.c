#include "hello-world.h"
#include "uip.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include <stdbool.h>
#include "tapdev.h" //Хранит MAC-адрес
#include "timer.h"
#include <stdint.h>


#define PORT1 1000
#define startPIN 28 //C этого пина начинается массив портов
#define COUNT_PINS 3 //Кол-во пинов

/*****Индикатор подключения*****/
//Задаем определение PIN29 и PIN30: Маска, адрес, ID контроллера, тип ножки, атрибуты	
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

//Установка состояния пина
void setPinState(Pin *pinConfigs, int pinNumber, int state, struct ethernet_state *s);

//Обработка сигнала и получение его характеристик
//static int SignalTask(struct pt *pt, char *staticBuffer, struct sData *data, int time, Pin *pinConfigs, int pinNumber, bool *flag);
//Работа с сигналом без протосокета
signalData SignalTask(struct ethernet_state *s, int time, Pin *pinConfigs, int pinNumber);
static int fib(struct pt *pt, int max, int* res, bool *flag); 

void listen_port(void)
{
  /* Прослушка TCP-порта (1000-ого)  */
  uip_listen(HTONS(PORT1));
}

// Функция для разделения строки на три части
void parse_message(struct ethernet_state *s) {
	char *token;

	// Разделяем строку по символу ';'
	token = strtok(s->inputBuffer, ";"); 
	if (token != NULL) {
			strcpy(s->port_letter, token); // Копируем букву порта
	}

	token = strtok(NULL, ";"); 
	if (token != NULL) {
			strcpy(s->port_number, token); // Копируем номер порта
	}

	token = strtok(NULL, ";");
	if (token != NULL) {
			strcpy(s->output_state, token); // Копируем состояние выхода
	}
}

// Функция для управления состоянием пина
void setPinState(Pin *pinConfigs, int pinNumber, int state, struct ethernet_state *s) {
	Pin *pin = &pinConfigs[pinNumber-startPIN]; // Получение ссылки на структуру пина
	// Изменение типа пина в зависимости от состояния
	if (state == 0) {
			pin->type = PIO_OUTPUT_0; // Выходной сигнал
	} else if (state == 1) {
			pin->type = PIO_OUTPUT_1; // Выходной сигнал
	} else if (state == 2) {
			pin->type = PIO_INPUT; // Входной сигнал
	}

	memset(s->sendBuffer, 0, sizeof(s->sendBuffer));
	if(PIO_Configure(pin, 1) == 1)//Настраиваем пин
		strncpy(s->sendBuffer, "Configure success! Great!", sizeof(s->sendBuffer)); 
	else 
		strncpy(s->sendBuffer, "Configure failed :(", sizeof(s->sendBuffer)); 
}

void clientPinSettings(struct ethernet_state *s){
	//Очищаем буферы 
	memset(s->port_letter, 0, sizeof(s->port_letter)); // Обнуляем весь буфер
	memset(s->port_number, 0, sizeof(s->port_number)); // Обнуляем весь буфер
	memset(s->output_state, 0, sizeof(s->output_state)); // Обнуляем весь буфер

	//Разбиваем сообщение на 3 переменные
	parse_message(s);
	
	int pinNumb = atoi(s->port_number); //Переводим символ номера порта в число 
	int outputState = atoi(s->output_state); //Переводим символ номера состояния в число
	
	//Проверяем, порт A или порт В
	if(s->port_letter[0] == 'A'){
		setPinState(pinConfigsA, pinNumb, outputState, s); //и корректируем PIN с дальнейшей конфигурацией
	}
	else if(s->port_letter[0] == 'B'){
		setPinState(pinConfigsB, pinNumb, outputState, s);
	}
}

static int defaultConfigurePins(struct ethernet_state *s){
	//Конфигурируем ПИНы по умолчанию на выход с 0
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
	/* Переменные для замера характеристик сигнала */
	uint16_t start_rising_edge_time = 0; //Время возникновения нарастающего фронта (мс)
	uint16_t end_falling_edge_time = 0; //Время окончания спадающего фронта (мс)
	uint16_t current_time = 0; //Текущее время (мс)
	uint16_t start_pulse_t = 0; //Начало импульса
	uint16_t end_pulse_t = 0; //Конец импульса
	uint8_t current_front_condition = 0; //Текущее состояние фронта (1 или 0)
	uint8_t new_front_condition; //Новое состояние фронта (1 или 0)
	uint8_t count_front_condition = 0; //Счетчик состояний фронтов
	
	struct timer calcTime; //Таймер для создания сигнала и времени расчета
	signalData data = {0}; //Создаем структуру для хранения характеристики сигнала
	timer_set(&calcTime, CLOCK_SECOND * time); //Расчетное время цикла
	
	while(1){
		/*Создание прямоугольного сигнала*/
		//rectangleSignal(&delay_timer);
		
		//Изменение состояния сигнала и расчет периода, частоты
		new_front_condition = PIO_Get(&pinConfigs[pinNumber-startPIN]); //Получаем состояние сигнала
		//current_time = clock_time(); //Фиксируем текущее время
		
		//Cчитываем статус ножки PB30
		if(current_front_condition == 0 && new_front_condition == 1 ){ //Нарастающий фронт 0 __/ 1
			start_pulse_t = clock_time(); //Фиксируем начало импульса
			count_front_condition++;
			if(count_front_condition % 2 == 0){ //Если получили еще один нарастающий фронт - прошел период
				end_falling_edge_time = clock_time(); //Фиксируем время
				count_front_condition = 1; //Имеем текущий нарастающий фронт
				data.period = (float)(end_falling_edge_time - start_rising_edge_time)/1000.0; //Расчет всех периодов для подсчета среднего (мс -> c)
				if(data.period != 0.0){
					data.frequency = 1.0/data.period; //Расчет всех частот для подсчета средней (Гц)
					data.period_sum += data.period; //Добавляем период к общему подсчету периодов
					data.frequency_sum += data.frequency; //Добавляем частоту к общему подсчету частот
				}
				else
					printf("Period = 0\n");
			}
			start_rising_edge_time = clock_time(); //Фиксируем время начала отсчета периода
			current_front_condition = 1; //Высокий сигнал
		}
			else if (current_front_condition == 1 && new_front_condition == 0){ //Понижающий фронт 1 \__ 0
				end_pulse_t = clock_time(); //Фиксируем конец импульса
				data.pulse_duration = (end_pulse_t - start_pulse_t)/1000.0; //Замеряем длительность импульса (мс->с)
				data.pulse_count++; //Добавляем импульс
				current_front_condition = 0; //Низкий сигнал
		}	
		if(data.period != 0 && data.pulse_duration != 0){
			data.duty_cycle = data.period / data.pulse_duration; //Рассчитываем скважность
			data.fill_factor = 1.0/data.duty_cycle; //Рассчитываем коэфф. заполнения
		}
		if (timer_expired(&calcTime))
			break; //Завершаем функцию по окончании таймера
	}
	data.period_avg = data.period_sum /(float)data.pulse_count; //Средний период
	data.frequency_avg = data.frequency_sum / (float)data.pulse_count; //Средняя частота
}

void dataSendSignalTask(struct ethernet_state *s, int portNumber, signalData data){
	memset(s->sendBuffer, 0, sizeof(s->sendBuffer)); // Обнуляем весь буфер
	snprintf(s->sendBuffer, sizeof(s->sendBuffer),"period: %f s\nperiod_avg: %f s\nfrequency: %f Hz\nfrequency_avg: %f Hz\n"
					"duty cycle: %f s\nfill factor: %f s\n"
					"pulse count: %d\npulse duration: %f s\n",
					data.period, data.period_avg, data.frequency, data.frequency_avg,
					data.duty_cycle, data.fill_factor,
					data.pulse_count, data.pulse_duration); //Переводим данные в символы
	//uip_send(s->sendBuffer, strlen(s->sendBuffer)); //Отправляем данные
}


int rectangleSignal(struct timer *timer){
	if(timer_expired(timer)){
		//Если установлен высокий сигнал
		if(PIO_Get(&pinPB29) == 1){
			PIO_Clear(&pinPB29); //Ставим низкий
			printf("PB29: Low - %d\n", PIO_Get(&pinPB29));
		} else{ //Если низкий, то наоборот - ставим высокий
			PIO_Set(&pinPB29);
			printf("PB29: High - %d\n", PIO_Get(&pinPB29));
		}
		timer_reset(timer);
	}
	return PIO_Get(&pinPB29);
}

//Информация о проекте и плате
void infoAbout(struct ethernet_state *s, char message[]){
	
	uip_send(message, strlen(message));
}

int charToInt(struct ethernet_state *s){
	//Очищаем буфер под принимаемое число
	memset(s->inputBuffer, 0, sizeof(s->inputBuffer)); // Обнуляем весь буфер
	//Принимаем данные
	char *data = (char*)uip_appdata; //data указывает на действительные данные
	int len = uip_datalen(); //Определяем переменную длины для удобства
	strncpy(s->inputBuffer, data, len); //Копируем данные в буфер received_number
	int number = atoi(s->inputBuffer); //Переводим символы в число
	return number;
}

void recvMessage(struct ethernet_state *s){
	//Очищаем буфер под принимаемое число
	memset(s->inputBuffer, 0, sizeof(s->inputBuffer)); // Обнуляем весь буфер
	//Принимаем данные
	char *data = (char*)uip_appdata; //data указывает на действительные данные
	int len = uip_datalen(); //Определяем переменную длины для удобства
	strncpy(s->inputBuffer, data, len); //Копируем данные в буфер 
	//printf("%s", s->inputBuffer);
}

//Принимаем число, удваиваем и отправляем обратно 
void doubleNumber(struct ethernet_state *s){
	int number = charToInt(s);
	//Работа с числом
	int doubleNumber = number * 2; //Увеличиваем полученное значение в два раза
	char response[10];
	sprintf(response, "%d", doubleNumber); //Помещаем число в символьный массив
	uip_send(response, strlen(response)); //Отправляем число
	printf("Send data\n");
}


//Принимаем число, удваиваем и отправляем обратно 
void doubleNumbSock(struct ethernet_state *s){
	int number = 0;
	//Работа с числом
	number = atoi(s->sockBuffer) * 2; //Увеличиваем полученное значение в два раза
	memset(s->sendBuffer, 0, sizeof(s->sendBuffer));
	snprintf(s->sendBuffer, sizeof(s->sendBuffer), "%d", number); //Помещаем число в символьный массив
}


static int selectorSock(struct ethernet_state *s, char* message_board, char* message_project) {
	PSOCK_BEGIN(&s->p);
	int client_state = 0; //Состояние выбора
	s->state = NEUTRAL; //Нейтральное состояние
	while(1) {
		//Принятие данных
		memset(s->sockBuffer, 0, sizeof(s->sockBuffer));
		if (client_state == 0) {
			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			client_state = atoi(s->sockBuffer);
		}
		
		//Блок перехода в различные состояния
		if(client_state == 1){ //Отправка инфомации о плате
			s->state = INFO_BOARD;
			
			strncpy(s->sendBuffer, message_board, sizeof(s->sendBuffer));
			PSOCK_SEND_STR(&s->p, s->sendBuffer); //Функция вывода информации о плате и проекте
			
			s->state = NEUTRAL;
			client_state = 0;
		} 
		else if(client_state == 2){ //Отправка инфомации о дате проекта
			s->state = INFO_DATE;
			
			PSOCK_SEND_STR(&s->p, message_project); //Функция вывода информации о плате и проекте
			
			s->state = NEUTRAL;
			client_state = 0;
		}
		else if(client_state == 3){ //Удваиваем получаемое число и отправляем клиенту
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
		else if(client_state == 4){ //Работа с сигналом
			s->state = SIGNAL_INFO;
			
			memset(s->sockBuffer, 0, sizeof(s->sockBuffer));
			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			strncpy(s->inputBuffer, s->sockBuffer, sizeof(s->inputBuffer)); //Копируем данные в буфер

			//Очищаем буферы 
			memset(s->port_letter, 0, sizeof(s->port_letter)); // Обнуляем весь буфер
			memset(s->port_number, 0, sizeof(s->port_number)); // Обнуляем весь буфер
			memset(s->output_state, 0, sizeof(s->output_state)); // Обнуляем весь буфер
			
			//Разбиваем сообщение на 3 переменные
			parse_message(s);
			
			int pinNumb = atoi(s->port_number); //Переводим символ номера порта в число 
			int time = atoi(s->output_state); //В данном случае получаем время после второго символа ;
			
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
		else if(client_state == 5){ //Конфигурация пинов
			s->state = PIN_CONF;

			PSOCK_WAIT_UNTIL(&s->p, PSOCK_NEWDATA(&s->p));
			if(PSOCK_NEWDATA(&s->p))
				PSOCK_READTO(&s->p, '\n');
			strncpy(s->inputBuffer, s->sockBuffer, sizeof(s->inputBuffer)); //Копируем данные в буфер
			
			clientPinSettings(s); //Функция конфигурации пина
			
			PSOCK_SEND_STR(&s->p, s->sendBuffer);//Отправляем сообщение настройки пина
			
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
	
	//Строка-селектор
	char *Selector =
		"1. Find out the status of the device (what kind of device, etc.)\n"
		"2. Info about date\n"
		"3. Calculation (double value)\n"
		"4. Info about signal\n";
	/*Будет отдельный поток, который активирует ножки МК и анализирует сигнал
		Проанализировав сигнал (в течение 10 с, например), можно будет выбрать,
		что делать дальше*/
	
	
	//Сообщение для первого выбора в селекторе
	char message_board[256];
	snprintf(message_board, sizeof(message_board),
	//Комплектуем все сообщение в одну переменную
	"-- EMAC uIP Project %s --\n\r" 
	"-- BOARD: %s\n\r"
	" - MAC %02x:%02x:%02x:%02x:%02x:%02x\n\n" 
	"Frequency of generator: %d",
	SOFTPACK_VERSION, 
	BOARD_NAME, 
	MacAddress.addr[0], MacAddress.addr[1], MacAddress.addr[2],
	MacAddress.addr[3], MacAddress.addr[4], MacAddress.addr[5],
	BOARD_MAINOSC);
	
	//Сообщение для второго выбора в селекторе
	char message_project[256];
	snprintf(message_project, sizeof(message_project),
	"-- Compiled: %s %s --",
	__DATE__, __TIME__);
	
	//Сообщение для третьего выбора в селекторе
	char* stateNumb = "State 3: calculation";
	
	//Сообщение для четвертого выбора в селекторе
	char* stateSignal = "State 4: signal";
	
	//Создаем экземпляр структуры для хранения состояний подключения
	struct ethernet_state *s = &(uip_conn->appstate);
	
	//Конфигурируем пины и отправляем их состояние клиенту
	if(uip_connected()) {
		PSOCK_INIT(&s->p, s->sockBuffer, sizeof(s->sockBuffer));	
		printf("Client connection success\n");
		//Включаем лампочку
		Pin Led_Conn_Indicator = LED_IND_ON;
		PIO_Configure(&Led_Conn_Indicator, 1);
		
		s->state = SUCCESS_CONNECT; //Подключение произошло
		defaultConfigurePins(s);
	} 
	
	selectorSock(s, message_board, message_project);
}
