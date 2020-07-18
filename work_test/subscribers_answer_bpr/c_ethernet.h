#ifndef C_ETHERNET
#define C_ETHERNET

#include <pthread.h>
#include <signal.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <linux/sockios.h>
#include <errno.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <string.h>
#include <sys/ioctl.h>
#include "globals.h"

#define MAX_ARP_DATA_LEN LEN_BUF
#define HEADER_ARP_LEN 14 // длинна ARP заголовка 
#define MAC_ADDR_LEN 6    // длинна MAC адреса
#define HEADER_PROTO_LEN 4 //  заголовка протокола

//#define TRUE = 1
//#define FALSE = 0

class cEthernet;
struct param
{
	unsigned int par;
	cEthernet* p;
};

struct ARP_HEADER
{   //заголовок ARP пакета (заголовок 1)
	unsigned char  DstMac[MAC_ADDR_LEN];
	unsigned char  SrcMac[MAC_ADDR_LEN];
    unsigned short type; // тип Ethernet кадра
};

struct PROTO_HEADER_COMMAND
{// то что пришло от АРМ
    unsigned char adrByte;      // адрес абонента
    unsigned char comandByte;   // командный байт
    unsigned short N;           // кол-во значимых данных в пакете
};

struct PROTO_HEADER_ANSWER
{// то что отправиться в АРМ
    unsigned char adrByte;      // адрес абонента
    unsigned char otvByte;      // ответный байт
    unsigned short N;           // кол-во значимых данных в пакете
};

struct COUNTERS
{
    unsigned int tx;	//счетчик принятых пакетов(успешный и ошибочных)
    unsigned int rx;	//счетчик успешно принятых пакетов
    unsigned int rx_err;	//счетчик пакетов, принятых с ошибкой
};

#define LEN_SYSTEM_INFO 4

class cEthernet
{
private:
    	int m_nTh;
	param m_param; 
	char m_nameDev[11]; 
    	int m_isSuccess; // 1 - успешна инициализация, 0 - неуспешна
	pthread_t m_thread_id;
    	pthread_attr_t m_attr_thread;
	unsigned char m_readBytes[LEN_BUF];
	unsigned char m_writeBytes[LEN_BUF];
	unsigned char m_macAddr[MAC_ADDR_LEN];
	unsigned char m_systemInfo[LEN_SYSTEM_INFO];

	struct sockaddr_in ADR;
	int m_sock;
	int m_sock2;
	pthread_mutex_t m_lock_r;
	pthread_mutex_t m_lock_w;

	ARP_HEADER m_arpH;
    	PROTO_HEADER_COMMAND m_protoCommandH;
    	PROTO_HEADER_ANSWER m_protoAnswerH;

	int m_lenSysInfo;

    	//COUNTERS m_cnt;

	unsigned char m_adr; // адрес абонента считанные из устройства
    	struct sockaddr_ll m_socket_address;
	struct ifreq m_ifr;
	pthread_mutexattr_t mattr;

    	unsigned char m_regim;
    	int m_replaceRegim;

	void createThread();
    	//int setPriorityThread();
    	int setAttributsThread();
	int task(void*);
	int createSocket(char *dev_name);
	int Read(unsigned char*, int);
    	int Write(unsigned char*, int*);
	int getMac(char*); 
	void setParamForSend();
    	unsigned char readAdr();
	int defSinx(unsigned char adrByte);

public:
	cEthernet();
	cEthernet(const char*); 
    	void readEth(unsigned char*,unsigned short*);
	void writeEth(unsigned char*, unsigned short);
    	int isSuccessInitObj();
    	void setAdr(unsigned char);
	void setDiagInfoForArm(bool);
	void setDiagByte(unsigned char diag = 0x86);
	void SetSock2(int h);
	int GetSock2();

public: static void* threadFunc(void*);   
	~cEthernet();
};

#endif
