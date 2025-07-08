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

/// uIP buffer : The ETH header (����� ���������)
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

void uip_log(char *m)
{
    TRACE_INFO("-uIP- %s\n\r", m);
}

		
//������������ ������ � ��������� �����
static void app_init(void)
{
    printf("P: APP Init ... ");
    printf("send-X2-numb\n\r");
    listen_port(); //��������� ����� �� �������� ����������
}

int main(void){
	
	uip_ipaddr_t ipaddr; //���������� ��� �������� IP-������
	struct timer periodic_timer, arp_timer;//�������
	uint8_t i; //����������-�������

	// ������������� ��������� ���������
	
	//������������� ������������ �������� ���������� tapdew (���������� � �������, MAC-
	//����� ����������, IP-�����, �������, �����
	tapdev_init(); 
	clock_init(); //������������� �������
	timer_set(&periodic_timer, CLOCK_SECOND / 2); //�������� �������������� ������� - ��� �������
	timer_set(&arp_timer, CLOCK_SECOND * 10); //�������� ARP ������� - 10 ������
	
	// ������������� ���� uIP
	uip_init();

	// ������ ����������� IP ��� ����� � ��� ����� (��������� ���������� ipaddr)
	uip_ipaddr(ipaddr, HostIpAddress[0], HostIpAddress[1],
										 HostIpAddress[2], HostIpAddress[3]);
	uip_sethostaddr(ipaddr); 

	// ������ ����� ����� (��������� ���������� ipaddr)
	uip_ipaddr(ipaddr, RoutIpAddress[0], RoutIpAddress[1],
										 RoutIpAddress[2], RoutIpAddress[3]);
	uip_setdraddr(ipaddr);
	
	// ������ ����� ���� (��������� ���������� ipaddr)
	uip_ipaddr(ipaddr, NetMask[0], NetMask[1], NetMask[2], NetMask[3]);
	uip_setnetmask(ipaddr);
	uip_setethaddr(MacAddress); //������������� MAC-����� �����
	
	//�������� ������������� ���������� � ��������� �����
	app_init();
	
	while(1) {
		uip_len = tapdev_read(); 
		if(uip_len > 0) {// ��������� ������ ��� ��������� (��� uip_len > 0 - ������ ����)
				if(BUF->type == htons(UIP_ETHTYPE_IP)) { //���� ������ ���� ip, �� �������������� ���
						uip_arp_ipin(); //������������ �������� IP-�����
						uip_input(); //������������ �������� IP-����� � �������� ��� � ����������
						// ��������� ������ ��� ��������� (��� uip_len > 0)
						if(uip_len > 0) {
								uip_arp_out();
								tapdev_send(); //���������� ������ ����� ����������� ������� ���������
						}
				} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) { //���� ������ ���� ARP, �� �������������� ���
					
						/*������� uip_arp_arpin() ������� ��������, ����� ����� ARP ������� ��������� Ethernet.
						��� ������� ����� ������������, ��� ���� Ethernet ������������ � ������ uip_buf. ����� ������� uip_arp_arpin() ���������� ��������,
						���������� ������ uip_buf ������ ���� ���������� �� Ethernet, ���� ���������� uip_len ������ 0.*/
					
						uip_arp_arpin();
						// ���� � ������� ������� ���� �������� ������ - ��������� ������ ��� ��������� (��� uip_len > 0 - ������ ����)
						if(uip_len > 0) {
								tapdev_send(); //���������� ������
						}
				}
				//���� �������� ������, �� �������������� ������ ����������
		} else if(timer_expired(&periodic_timer)) {
				timer_reset(&periodic_timer);
				for(i = 0; i < UIP_CONNS; i++) {
						uip_periodic(i);
						// ���� � ������� ������� ���� �������� ������ �� ������� ��������� ���������� - ��������� ������ ��� ��������� (��� uip_len > 0 - ������ ����)
						if(uip_len > 0) {
							uip_arp_out();
							tapdev_send();
						}
				}

				//����� ������� ������� ARP ������ 10 ������
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


