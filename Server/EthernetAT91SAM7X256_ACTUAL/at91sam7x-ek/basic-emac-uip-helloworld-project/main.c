//#include "uip.h"
//#include "uip_arp.h"
#include "tapdev.h"
//#include "timer.h"
//#include "hello-world.h"
//#include "pio/pio.h"
//#include "time.h"
//#include "stdio.h"


//-----------------------------------------------------------------------------
//         Local Define
//-----------------------------------------------------------------------------

/// uIP buffer : The ETH header (буфео заголовка)
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

void uip_log(char *m)
{
    TRACE_INFO("-uIP- %s\n\r", m);
}

		
//Инициализция задачи и прослушка порта
static void app_init(void)
{
    printf("P: APP Init ... ");
    printf("send-X2-numb\n\r");
    listen_port(); //Прослушка порта на входящие соединения
}

int main(void){
	
	uip_ipaddr_t ipaddr; //Переменная для хранения IP-адреса
	struct timer periodic_timer, arp_timer;//Таймеры
	uint8_t i; //Переменная-счетчик

	// Инициализация системных устройств
	
	//Инициализация виртуального сетевого интерфейса tapdew (информация о проекта, MAC-
	//адрес устройства, IP-хоста, роутера, маска
	tapdev_init(); 
	clock_init(); //Инициализация таймера
	timer_set(&periodic_timer, CLOCK_SECOND / 2); //Интервал периодического таймера - пол секунды
	timer_set(&arp_timer, CLOCK_SECOND * 10); //Интервал ARP таймера - 10 секунд
	
	// Иницализируем стек uIP
	uip_init();

	// Задаем статический IP для платы и для хоста (используя переменную ipaddr)
	uip_ipaddr(ipaddr, HostIpAddress[0], HostIpAddress[1],
										 HostIpAddress[2], HostIpAddress[3]);
	uip_sethostaddr(ipaddr); 

	// Задаем адрес шлюза (используя переменную ipaddr)
	uip_ipaddr(ipaddr, RoutIpAddress[0], RoutIpAddress[1],
										 RoutIpAddress[2], RoutIpAddress[3]);
	uip_setdraddr(ipaddr);
	
	// Задаем маску сети (используя переменную ipaddr)
	uip_ipaddr(ipaddr, NetMask[0], NetMask[1], NetMask[2], NetMask[3]);
	uip_setnetmask(ipaddr);
	uip_setethaddr(MacAddress); //Устанавливаем MAC-адрес платы
	
	//Вызываем инициализацию приложения и прослушку порта
	app_init();
	
	while(1) {
		uip_len = tapdev_read(); 
		if(uip_len > 0) {// Обработка данных при получении (при uip_len > 0 - данные есть)
				if(BUF->type == htons(UIP_ETHTYPE_IP)) { //Если пакеты типа ip, то обрабатываются они
						uip_arp_ipin(); //Обрабатывает входящий IP-пакет
						uip_input(); //Обрабатывает входящий IP-пакет и передает его в приложение
						// Обработка данных при получении (при uip_len > 0)
						if(uip_len > 0) {
								uip_arp_out();
								tapdev_send(); //Отправляет данные через виртуальный сетевой интерфейс
						}
				} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) { //Если пакеты типа ARP, то обрабатываются они
					
						/*Функцию uip_arp_arpin() следует вызывать, когда пакет ARP получен драйвером Ethernet.
						Эта функция также предполагает, что кадр Ethernet присутствует в буфере uip_buf. Когда функция uip_arp_arpin() возвращает значение,
						содержимое буфера uip_buf должно быть отправлено по Ethernet, если переменная uip_len больше 0.*/
					
						uip_arp_arpin();
						// Если с помощью функции выше получили данные - обработка данных при получении (при uip_len > 0 - данные есть)
						if(uip_len > 0) {
								tapdev_send(); //Отправляем данные
						}
				}
				//Если сработал таймер, то обрабатывается каждое соединение
		} else if(timer_expired(&periodic_timer)) {
				timer_reset(&periodic_timer);
				for(i = 0; i < UIP_CONNS; i++) {
						uip_periodic(i);
						// Если с помощью функции выше получили данные за периоды обработки соединений - обработка данных при получении (при uip_len > 0 - данные есть)
						if(uip_len > 0) {
							uip_arp_out();
							tapdev_send();
						}
				}

				//Вызов функции таймера ARP каждые 10 секунд
				if(timer_expired(&arp_timer)) {
						timer_reset(&arp_timer);
						uip_arp_timer();
				}
		}

		// Display Statistics
		if ( USART_IsDataAvailable((AT91S_USART *)AT91C_BASE_DBGU) ) {

				EmacStats    stats;

				DBGU_GetChar();
				EMAC_GetStatistics(&stats, 1);
				printf("=== EMAC Statistics ===\n\r");
				printf(" .tx_packets = %d\n\r", stats.tx_packets);
				printf(" .tx_comp = %d\n\r", stats.tx_comp);
				printf(" .tx_errors = %d\n\r", stats.tx_errors);
				printf(" .collisions = %d\n\r", stats.collisions);
				printf(" .tx_exausts = %d\n\r", stats.tx_exausts);
				printf(" .tx_underruns = %d\n\r", stats.tx_underruns);
				printf(" .rx_packets = %d\n\r", stats.rx_packets);
				printf(" .rx_eof = %d\n\r", stats.rx_eof);
				printf(" .rx_ovrs = %d\n\r", stats.rx_ovrs);
				printf(" .rx_bnas = %d\n\r", stats.rx_bnas);
		}
	}
  return 0;
}


