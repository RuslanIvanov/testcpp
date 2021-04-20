#ifndef C_ETHERNETM
#define C_ETHERNETM

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
#include <sys/types.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <signal.h>

#define LEN_BUF_ETHERNET 	1500
#define HEADER_ARP_LEN 		14  //длинна ARP заголовка 
#define MAC_ADDR_LEN 		6   //длинна MAC адреса
#define HEADER_PROTO_LEN 	4   //заголовка протокола
#define MAX_SUB 32

#define LEN_SYSTEM_INFO (4)

class cEthernetM;
struct param
{
	unsigned int par;
	int s;
	cEthernetM* p;
};

struct ARP_HEADER // не верно - иметь в виду ETH_HEADER
{   //заголовок ARP пакета (заголовок 1)
	unsigned char  DstMac[MAC_ADDR_LEN];
	unsigned char  SrcMac[MAC_ADDR_LEN];
    	unsigned short type; // тип Ethernet кадра
};

struct PROTO_HEADER_COMMAND
{// то что отправляется
    	unsigned char adrByte;      // адрес абонента
    	unsigned char comandByte;   // командный байт
    	unsigned int N;           // кол-во значимых данных в пакете
};

struct PROTO_HEADER_ANSWER
{// то что пришло
    	unsigned char adrByte;      // адрес абонента
    	unsigned char otvByte;      // ответный байт
   	unsigned int N;           // кол-во значимых данных в пакете
};

struct STATE_ETH
{
    	unsigned char counter_failure_tx; //счетчик сбоев передачи пакетов (не отправлены, нет сети)
    	unsigned char counter_failure_rx; //счетчик сбоев приема пакетов (не приняты по dT)
    	bool bError_rx;	//ошибка приема
	bool bError_tx;	//ошибка передачи
	int  error;	//номер ошибки
};

typedef struct //
{// frame id struct
	unsigned char	src,		// source address
	lan;				// outcoming lan (1/2)
	unsigned short	val;		// transaction id
}RAW_FRAME_ID;	


typedef	struct
{	// frame header
	RAW_FRAME_ID	id;	// frame id
	unsigned char	dst, 	// destination address (A)
	cmd; 			// command (K)
	unsigned short	len; 	// following data block length
}RAW_FRAME_HEADER, *PRAW_FRAME_HEADER;	


class cEthernetM
{
private:
    	int m_nTh;
	int m_indexObj;

	param m_param;//for thread

	char m_nameDev[11]; 
    	int  m_isSuccess; // 1 (TRUE) - успешна инициализация, 0 (FALSE) - неуспешна

	pthread_t m_thread_id;
    	pthread_attr_t m_attr_thread;
	unsigned char m_readBytes[LEN_BUF_ETHERNET];
	unsigned char m_writeBytes[LEN_BUF_ETHERNET];
	unsigned char m_macAddr[MAC_ADDR_LEN];
	unsigned char m_systemInfo[LEN_SYSTEM_INFO];

	struct sockaddr_in ADR;
	int m_sock;
	pthread_mutex_t m_lock_r;
	pthread_mutex_t m_lock_w;

	ARP_HEADER m_arpH;
    	PROTO_HEADER_COMMAND m_protoCommandH;
   	PROTO_HEADER_ANSWER m_protoAnswerH;

	static int m_lenSysInfo;

//------------------------------
	struct timeval m_tVal;
	//fd_set m_rdfs;
//------------------------------

    	STATE_ETH m_state_eth;

	unsigned char m_adr; //собственный адрес абонента
	unsigned char m_oper; // операция с абонетом
	
	unsigned char MASK_ADDR;
	unsigned char MASK_STATE;
    	struct sockaddr_ll m_socket_address;
    	struct ifreq m_ifr;
    	pthread_mutexattr_t mattr;

	void createThread();
    	//int setPriorityThread();
   	int setAttributsThread(int _PRIO_TH_ETH = 0,int _POLICY = SCHED_OTHER);
	int task(void*);
	void readFromMemberMass(unsigned char*, int*);
    	void writeInMemberMass(unsigned char*, int);
//socket----------------------------------------
	int  createSocket(char *dev_name);
	int  Read(unsigned char*, int);  // работа с внутренним масивом
    	int  Write(unsigned char*, int*);// работа с внутренним масивом
	int  getMac(char*);
    	void setParamForSend();
    	unsigned char readAdr();
    	int  defSinx(unsigned char adrByte, unsigned char otvByte);
//--------------------------------------------
//static:
	static int m_countObj;
	//struct timeval m_tVal;
	const static int maxObj = 6;
	static struct param  m_sockets[cEthernetM::maxObj];// for select
	static fd_set m_rdfs;
	static int m_maxfd;

	static int  m_fd_timer;
	static char m_filename[BUFSIZ];

public:
	cEthernetM();
	cEthernetM(const char*, unsigned short type =  ETHERNET_TYPE_SAKSD); 
	cEthernetM* getObj(int index);

    	int  isSuccessInitObj();
    	void setAdr(unsigned char);
	void setOper(unsigned char);

	void setDiagInfo(unsigned char* pBuf);
	void getDiagInfo(unsigned char* pBuf);
	void setDiagInfo(unsigned char addr, unsigned char lan);
	unsigned char getDiagInfo();

        static void usageDiagInfo(bool=true);
	bool isConnectEth();

	int writeEth(int addr,unsigned char comByte, unsigned char* pBuf, int len);
	int readEth (unsigned char* addr,unsigned char* answByte, unsigned char* pBuf, const unsigned int maxLen, int* pRecvLen);
	int readEthOnce(unsigned char* addr,unsigned char* answByte,unsigned char* pBuf, const unsigned int maxLen, int* pRecvLen,struct timeval* tVal);

	int getIndex() {return m_indexObj;}
	void clear();
	void waitTimer(struct timeval* ptv=NULL);

public: 
	static void* threadFunc(void*); 
	static int  waitData(struct timeval* tVal,struct param*); 
	static int  getPeriod(int);
	static void setPeriod(int,int period);
	static bool waitTimerTick(int);
	static int  initTimer(char* name);
	static void delTimer(int);
	static void startTimer(int);
	static int  getCountObj(){ return m_countObj;}
	static void stopTimer(int);
	static bool isTimer(int fd) { return (fd == m_fd_timer); };
	static void resetTimer(int);

	static RAW_FRAME_ID frm[MAX_SUB];

//errors:
	static const int ERROR_ANY = -2;
	static const int ERROR_SUB = -1;
	static const int UNDEF_STATE = 0; //timeout select
	static const int SINX = 1;
	static const int DATA = 2;
	static const int SINX_FOREIGN = 3;
	static const int END_TIMEOUT_SUB = -3;
	static const int IGNOR_REPLY = -4;
	static const unsigned short ETHERNET_TYPE_SAKSD = 0xbeef;
	static const unsigned short ETHERNET_TYPE_ALL = ETH_P_ALL;
	~cEthernetM(); 
};

#endif
