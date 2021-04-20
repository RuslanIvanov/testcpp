#include "c_ethernetM_Ext.h"

#define WRITE_SYSLOG //писать в сиситемный лог
#include "../libsyslog.h"

#include "../../../../drivers/chstime_hr_n/ioctl_chsthr.h"

int 	cEthernetM::m_countObj;
struct  param cEthernetM::m_sockets[maxObj];
fd_set  cEthernetM::m_rdfs;
char 	cEthernetM::m_filename[BUFSIZ] = "/dev/chthrksd0";
int  	cEthernetM::m_fd_timer;
int 	cEthernetM::m_maxfd;
int 	cEthernetM::m_lenSysInfo=0;
RAW_FRAME_ID cEthernetM::frm[MAX_SUB];

cEthernetM::cEthernetM()
{

	SYSLOG_TIME_COMPIL

	strcpy(&m_nameDev[0],"N/A");
	SYSLOG_PRINTF("I'm def constructor cEthernetM, name dev %s ",m_nameDev);

    	m_adr=2;
	m_oper=0;
    	m_thread_id=0;
    	m_isSuccess=0;

       // m_lenSysInfo=0;

	memset((void *)&m_arpH, 0, sizeof(struct ARP_HEADER));
    	memset((void *)&m_protoCommandH, 0, sizeof(struct PROTO_HEADER_COMMAND));
    	memset((void *)&m_protoAnswerH, 0, sizeof(struct PROTO_HEADER_ANSWER));

	memset((void*)&m_readBytes[0],0,LEN_BUF_ETHERNET);
	memset((void*)&m_writeBytes[0],0,LEN_BUF_ETHERNET);
	memset((void*)&m_macAddr[0],0,MAC_ADDR_LEN);

	memset((void*)&m_systemInfo[0],0x0,4);
	memset((void*)&m_state_eth,0,sizeof(STATE_ETH));

	m_sock = -1;

 	m_nTh=0;

	if(m_countObj<maxObj)
	{
		m_sockets[m_countObj].s = -1;
		m_sockets[m_countObj].p = this;

		m_isSuccess=1;
	}
	else m_isSuccess=0;

	m_indexObj = m_countObj++;

	m_tVal.tv_sec = 0;
        m_tVal.tv_usec = 10000; // ожидаем ответ 10 мсек  (макс 320 мсек)

	FD_ZERO(&m_rdfs);FD_SET(m_sock, &m_rdfs);
}

cEthernetM::cEthernetM(const char* pnameDev,unsigned short type)
{

	SYSLOG_TIME_COMPIL

	m_tVal.tv_sec = 0;
        m_tVal.tv_usec = 10000;

    	strcpy(&m_nameDev[0],pnameDev);

	pthread_mutexattr_init(&mattr);

	pthread_mutex_init(&m_lock_w,&mattr);
	pthread_mutex_init(&m_lock_r,&mattr);

	m_thread_id=0;
    	m_isSuccess=1;
    	m_adr =2;
	m_oper=0;
  	//m_lenSysInfo=0;

    	memset((void *)&m_arpH, 0, sizeof(struct ARP_HEADER));
    	m_arpH.type = type;//0xbeef;

	SYSLOG_PRINTF("cEthernetM::cEthernetM(type %x)",m_arpH.type);

    	memset((void *)&m_protoCommandH, 0, sizeof(struct PROTO_HEADER_COMMAND));
    	memset((void *)&m_protoAnswerH, 0, sizeof(struct PROTO_HEADER_ANSWER));

	memset((void*)&m_readBytes[0],0,LEN_BUF_ETHERNET);
	memset((void*)&m_writeBytes[0],0,LEN_BUF_ETHERNET);
	memset((void*)&m_macAddr[0],0,MAC_ADDR_LEN);

	memset((void*)&m_systemInfo[0],0x00,4);
	memset((void*)&m_state_eth,0,sizeof(STATE_ETH));

	if(m_countObj<maxObj)
	{
		//создать сокет
    		m_sock = createSocket(&m_nameDev[0]);
    		if(m_sock==-1)
		{
        		SYSLOG_ERROR("cEthernetM: error create socket");
        		m_isSuccess = 0;
			m_sockets[m_countObj].s = -1;
			m_sockets[m_countObj].p = NULL;
			return;
		}

		m_sockets[m_countObj].s = m_sock;
		m_sockets[m_countObj].p = this;

		if(!m_countObj) 
		{
			FD_ZERO(&m_rdfs);
			m_fd_timer = initTimer(m_filename);
			SYSLOG_PRINTF("cEthernetM:: init timer '%s', fd =  %d",m_filename,m_fd_timer);
			if(m_fd_timer>=0)
			{
				FD_SET(m_fd_timer, &m_rdfs); //добавить в набор при  readEth
				SYSLOG_PRINTF("cEthernetM:: timer fd =  %x",m_fd_timer);
			}else {  SYSLOG_PRINTF("cEthernetM:: error %i for timer, error open '%s'",m_fd_timer,&m_filename[0]); }

		}

		FD_SET(m_sockets[m_countObj].s, &m_rdfs);
		SYSLOG_PRINTF("cEthernetM:: socket[%d] fd = %x",m_countObj,m_sockets[m_countObj].s);

		m_isSuccess=1;

	}
	else m_isSuccess=0;

	m_indexObj = m_countObj++;  //m_indexObj сперва присваивается изначальное значение m_countObj, потом к m_countObj прибавляется 1
	m_nTh=m_countObj;


    	//setParamForSend();
    	//if(getMac(&m_nameDev[0])!=0) {close(m_sock); return;}

    	//if(setAttributsThread()==0)
        // 	createThread();

   	SYSLOG_PRINTF("cEthernetM: dev->%s,mac->%x: %x:%x:%x:%x:%x, obj %d",m_nameDev,
               m_macAddr[0],m_macAddr[1],m_macAddr[2],
               m_macAddr[3],m_macAddr[4],m_macAddr[5],m_indexObj);	
}

cEthernetM::~cEthernetM()
{

	/* проверяем, не завершился ли thread_child */
	if(m_thread_id)
	if (pthread_kill(m_thread_id, 0) != ESRCH)
	{
		/* посылаем thread_child служебный сигнал, который ее завершает */
		pthread_cancel(m_thread_id);
		/* закрываем дескриптор thread_child */
       		// pthread_join(m_thread_id, 0x00);
	}
	
	pthread_mutex_destroy(&m_lock_r);	
	pthread_mutex_destroy(&m_lock_w);
	m_thread_id = 0; 
    	SYSLOG_PRINTF("~cEthernetM: %s",m_nameDev);

	if(m_indexObj<m_countObj)
	{
                FD_CLR(m_sockets[m_indexObj].s, &m_rdfs);

	    	if(close(m_sockets[m_indexObj].s)!=0)
	        	{ SYSLOG_ERROR("~cEthernetM: error close cocket"); }
	    	m_sockets[m_indexObj].s = -1;
	}

	if(m_countObj>0) m_countObj--;

	if(m_countObj==0) {  FD_CLR(m_fd_timer,&m_rdfs);  delTimer(m_fd_timer); }

    	m_sock = -1;

    	pthread_mutexattr_destroy(&mattr);

    	pthread_attr_destroy(&m_attr_thread);
}

void cEthernetM::clear()
{
	FD_CLR(m_sockets[m_nTh].s, &m_rdfs);
}

unsigned char cEthernetM::readAdr()
{// ф. читает установленный адрес абонента на шине
    return m_adr;
}

void cEthernetM::setAdr(unsigned char adr)
{//ф.устанавливает адрес абонента на шине по протоколу обмена
//или m_adr=1, 0=2; то server:  master / slave  

       	if(adr>=2 && adr<(MAX_SUB-1))// - SINX
       	{//subscriber
            	m_adr = adr;
            	SYSLOG_PRINTF("cEthernetM::setSubscriberAddr: apply m_adr %x", m_adr);
		MASK_ADDR = 0xC0; MASK_STATE=0x86;
       	} else 
	{
		SYSLOG_PRINTF("cEthernetM::SERVER MASTER OR SLAVE: m_adr %x ", m_adr);
		MASK_ADDR = 0x40; MASK_STATE=0x80;
		if(adr == 0 || adr>=(MAX_SUB-1))
		{
			 adr=2;//slave
		}

		m_adr = adr;
	}
}

void cEthernetM::setOper(unsigned char oper)
{//ф.устанавливает тип опреации с абонентом на момоент передачи
    	m_oper = oper& (~0x1f);
}

void cEthernetM::setDiagInfo(unsigned char* pBuf)
{	

	for(unsigned char s=0; s<m_lenSysInfo;s++)
            m_systemInfo[s] = pBuf[s];
}

void cEthernetM::getDiagInfo(unsigned char* pBuf)
{
	for(unsigned char s=0; s<m_lenSysInfo;s++)
                pBuf[s] =  m_systemInfo[s];
}

void cEthernetM::setDiagInfo(unsigned char addr, unsigned char lan)
{	
	unsigned char a = 0;
	addr=addr&0x1f;
	if(addr>=0 && addr<MAX_SUB)
	{
		++frm[addr].val;
		frm[addr].lan=lan;
		a=addr;
	}

	unsigned char *pBuf = (unsigned char*)&frm[a];

	for(unsigned char s=0; s<m_lenSysInfo;s++)
            m_systemInfo[s] = pBuf[s];
}

unsigned char cEthernetM::getDiagInfo()
{
	RAW_FRAME_ID tmp_frm;
	unsigned char *pBuf = ((unsigned char*)&tmp_frm);

	for(unsigned char s=0; s<m_lenSysInfo;s++)
                pBuf[s] =  m_systemInfo[s];			

	return tmp_frm.lan;// return tmp_frm;
	
}

void cEthernetM::usageDiagInfo(bool b)
{

        if(b) 
        {
                m_lenSysInfo = LEN_SYSTEM_INFO;

		srand(time(NULL));
		int mynode=getpid();
		for(int i=0; i<MAX_SUB; i++)
		{
			frm[i].val = rand();
			frm[i].src = mynode;
			frm[i].lan = 0;
		}

                SYSLOG_MSG("cEthernetM eth: USE ON SYSTEM INFORMATION");
        }
        else 
        { 
                m_lenSysInfo = 0;
                SYSLOG_MSG("cEthernetM eth: DO NOT USE SYSTEM INFORMATION");
        }
}


void  cEthernetM::createThread()
{
	m_param.par = 0; 
	m_param.p=this;

    	if(pthread_create(&m_thread_id,&m_attr_thread,&threadFunc,&m_param)!=0)
    	{
         	SYSLOG_ERROR("cEthernetM::createThread: Error create thread eth");
         	m_isSuccess = 0;
    	}
}

int cEthernetM::setAttributsThread(int _PRIO_TH_ETH, int _POLICY)
{// ф. устанавливает приоритет потока. 0 - успешно, -1 - неуспешно

    int ret=0;

    if(pthread_attr_init(&m_attr_thread)>0)
    {
        SYSLOG_ERROR("cEthernetM::setAttributsThread: error set attrib!");
        return -1;
    }

    if(pthread_attr_setinheritsched(&m_attr_thread,PTHREAD_EXPLICIT_SCHED)>0)
    {
        SYSLOG_ERROR("cEthernetM::setAttributsThread: error pthread_attr_setinheritsched in setAttributsThread()");
        return -1;
    }

    ret = pthread_attr_setscope(&m_attr_thread,PTHREAD_SCOPE_SYSTEM);//PTHREAD_SCOPE_PROCESS);
    if(ret>0)
    {
        SYSLOG_ERROR("cEthernetM::setAttributsThread: error run pthread_attr_setscope in createThreadSinx(): ");

        switch(ret)
        {
            case EINVAL:
                 SYSLOG_ERROR("cEthernetM::setAttributsThread: The value of contentionscope is not valid");
            break;
            case ENOTSUP:
                 SYSLOG_ERROR("cEthernetM::setAttributsThread: An attempt was made to set the attribute to an unsupported value");
            break;
        }

        return -1;
    }

    if(pthread_attr_setschedpolicy(&m_attr_thread,_POLICY)>0)
    {
        SYSLOG_ERROR("cEthernetM::setAttributsThread: error pthread_attr_setschedpolicy in setAttributsThread()");
        return -1;
    }

    sched_param sp;
    sp.sched_priority = _PRIO_TH_ETH;

    ret = pthread_attr_setschedparam(&m_attr_thread,&sp);
    if(ret>0)
    {
         SYSLOG_ERROR("cEthernetM::setAttributsThread: error pthread_attr_setschedparam in setAttributsThread(): ");
        switch(ret)
        {
        case EINVAL:
             SYSLOG_ERROR("cEthernetM::setAttributsThread: The value of param is not valid");
            break;
        case ENOTSUP:
             SYSLOG_ERROR("cEthernetM::setAttributsThread: An attempt was made to set the attribute to an unsupported value");
            break;
        }

        return -1;
    }

    return 0;
}

int cEthernetM::createSocket(char *dev_name)
{
	// Create communication socket and bind it with the specified net interface.
	// _in char *dev_name	- name of the net interface to use;
	// _out	int			- socket descriptor.

	int sockd;

	// create socket
    	sockd = socket(PF_PACKET, SOCK_RAW, htons(m_arpH.type));
	if (sockd < 0)
    	{ SYSLOG_ERROR("cEthernetM::createSocket: Can not create raw socket"); return -1;}

	fcntl(sockd, F_SETFL, O_NONBLOCK);

	// bind the socket to the specified net interface
   	memset((void *)&m_ifr, 0, sizeof(struct ifreq));
    	memcpy(m_ifr.ifr_name,dev_name,strlen(dev_name));

    	if (ioctl(sockd, SIOCGIFINDEX, &m_ifr) == -1)
    	{
          	SYSLOG_ERROR("cEthernetM::createSocket: No such interface: ");
          	close(sockd);
    	}

    	memset(&m_socket_address, 0, sizeof (m_socket_address));
    	m_socket_address.sll_family    = PF_PACKET;
    	m_socket_address.sll_ifindex   = m_ifr.ifr_ifindex;
    	m_socket_address.sll_protocol  = htons(m_arpH.type);

    	SYSLOG_PRINTF("cEthernetM::createSocket: interface %s->%d",m_ifr.ifr_name,m_socket_address.sll_ifindex);

    	if(bind(sockd,(struct sockaddr*)&m_socket_address,sizeof(m_socket_address))< 0)
    	{
         	SYSLOG_ERROR("cEthernetM::createSocket: Can not bind socket to the specified net interface!");
         	close(sockd);
         	return -1;
     	}

    	if (ioctl(sockd, SIOCGIFHWADDR, &m_ifr) < 0)
    	{SYSLOG_ERROR("cEthernetM::createSocket: error ioctl"); return -1;}

    	memcpy(m_macAddr,(char *)&(m_ifr.ifr_hwaddr.sa_data),6); // mac утройства

	//----------------------------------------------------------------------
	//SIOCGIFFLAGS - operstate:

	/*
	   1) open AF_NETLINK socket
	   2) bind it to sockaddr_nl with nl_groups = RTMGRP_LINK
	   3) send message RTM_GETLINK to kernel
	   4) make poll/epoll on socket to read RTM_NEWLINK and RTM_DELLINK messages
	   5) you will receive initial interfaces list and its changes in future
	*/

	return sockd; 
}

int  cEthernetM::getMac(char* dev_name)
{// ф. определения mac адреса устройства ,возвращает 0 в случае успеха, 1- - неудача
	int fd;
	struct ifreq ifr;
	unsigned char mac[6];

	fd=socket(AF_INET,SOCK_DGRAM,0);
	if(fd<0) return 1;
	memset(&ifr,0,sizeof(struct ifreq));
	memcpy(ifr.ifr_name,dev_name,strlen(dev_name));
	if(ioctl(fd,SIOCGIFHWADDR,&ifr)<0)
	{	
		close(fd);
        	m_isSuccess = 0;
		return 1;
	}
    	memcpy(mac,(char *)&(ifr.ifr_hwaddr.sa_data),sizeof(struct sockaddr));
    
    	SYSLOG_PRINTF("cEthernetM::mac %s: %.2x:%.2x:%.2x:%.2x:%.2x:%.2x",dev_name,mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

	for(int i=0; i<6; i++)
		m_macAddr[i]=mac[i];
    	//system("touch info.txt;ifconfig | grep \"eth\" > info.txt");

	close(fd);
	return 0;
}

int cEthernetM::isSuccessInitObj()
{return m_isSuccess;}

int cEthernetM::task(void* par)
{//rezerv
    return 0;
}

void cEthernetM::setParamForSend()
{
        memset(&m_socket_address,0,sizeof(m_socket_address));

        //RAW communication
        m_socket_address.sll_family = AF_PACKET;

        //m_socket_address.sll_ifindex=if_nametoindex("eth0");
        m_socket_address.sll_ifindex=m_ifr.ifr_ifindex;
        m_socket_address.sll_halen = ETH_ALEN;

}

void* cEthernetM::threadFunc(void* par)
{ 
	((param*)par)->p->task(par); 
    	return NULL;
}

void cEthernetM::readFromMemberMass(unsigned char* pRead,int* pn)
{
	pthread_mutex_lock(&m_lock_r);

	for(unsigned int i = 0;i<m_protoAnswerH.N;i++)
	{
		pRead[i] = m_readBytes[i];
	}

	(*pn) = m_protoAnswerH.N;

	pthread_mutex_unlock(&m_lock_r);
}

void cEthernetM::writeInMemberMass(unsigned char* pWrite, int n)
{
	pthread_mutex_lock(&m_lock_w);

	for(int i = 0;i<n;i++)
	{
		m_writeBytes[i] = pWrite[i];
	}

    	m_protoCommandH.N = n;

	pthread_mutex_unlock(&m_lock_w);
}

int cEthernetM::Read(unsigned char* pReadInBuf, int n) // куда пишет и скоько
{
// ф. возвращает -1 - абонент не готов или неисправен,
// ф. возвращает 0 - данные не распознанны или их нет,
// ф. возвращает 1 - пришла синхронизация,
// ф. возвращает 2 - пришли данные
// ф. возвращает 3 - пришел запрос от сервера-Master, нужно ответить
// ф. возвращает 4 - пришел запрос от сервера-Master - не отвечать
// распознает заголовок пакета от абонента + данные

	if((m_arpH.type == ETHERNET_TYPE_ALL) && ((pReadInBuf[12] != 0xbe) || (pReadInBuf[13] != 0xef))) { SYSLOG_ERROR("cEthernetM::Read: type"); return 0; }
   
    	int rezS = defSinx(pReadInBuf[14+m_lenSysInfo],pReadInBuf[15+m_lenSysInfo]);
    	if(rezS == -1) return -1; //не ГОТ и не ИСПР ... было ранее 0
	if(rezS == -2) return 0;  //error

	if(rezS == 1) // синхронизация (данных нет!)
    	{
	        m_protoAnswerH.adrByte = pReadInBuf[14+m_lenSysInfo]&0x1f;
        	m_protoAnswerH.otvByte = pReadInBuf[15+m_lenSysInfo];

		//printf("\nMAC: ");
		bool bSinxForeign = false;
		for(int i=0;i<MAC_ADDR_LEN;i++)
		{			
			//printf("%x--%x, ",m_macAddr[i],pReadInBuf[i+MAC_ADDR_LEN]);

			if(m_macAddr[i]!=pReadInBuf[i+MAC_ADDR_LEN])
			{	
				bSinxForeign = true;
				break;
			}
		}
		
		if(!bSinxForeign)
        	return 1; // ответа по шине не будет при синхр.
		else		
		return 3;
    	}

//-----------------------------------------------------------------------:
    	//пришли данные
	for(int i=0;i<MAC_ADDR_LEN;i++)
	{//запомнил HEADER
		m_arpH.DstMac[i]=pReadInBuf[i]; //D0-D5 не нужно
	 	m_arpH.SrcMac[i]=pReadInBuf[i+MAC_ADDR_LEN];//D6-D11
	}

	pthread_mutex_lock(&m_lock_r);
        m_protoAnswerH.N = 0;
        pthread_mutex_unlock(&m_lock_r);

	m_protoAnswerH.adrByte = pReadInBuf[14+m_lenSysInfo]&0x1f;
        m_protoAnswerH.otvByte = pReadInBuf[15+m_lenSysInfo];

	//if( !(m_adr ==  m_protoAnswerH.adrByte || m_adr == 1) ) { return 0; }

        //---системная информация 4 байта--------------
        for(int s=0; s<m_lenSysInfo;s++)
                m_systemInfo[s] = pReadInBuf[14+s];//14
	// + анализ, признак пререхода на другую сеть
        //---------------------------------------------
	if(n>=HEADER_ARP_LEN)
	{
		pthread_mutex_lock(&m_lock_r);

        	m_protoAnswerH.N=pReadInBuf[16+m_lenSysInfo];
        	m_protoAnswerH.N=(m_protoAnswerH.N<<8)|pReadInBuf[17+m_lenSysInfo];

        	if(m_protoAnswerH.N>LEN_BUF_ETHERNET)
        	{
	            	m_protoAnswerH.N=0; //printf(" N>MAX ");
			SYSLOG_MSG("cEthernetM::Read: N>MAX");
            		return 0;
		}

	        for(unsigned int i=0;i< m_protoAnswerH.N;i++)
			m_readBytes[i]=pReadInBuf[i+HEADER_ARP_LEN+HEADER_PROTO_LEN+m_lenSysInfo];  // c D18
        	//m_protoCommandH.N;//всего  значимых данн.

		pthread_mutex_unlock(&m_lock_r);

        	return 2;
        } else { SYSLOG_MSG("cEthernetM::Read: n>=HEADER_ARP_LEN"); }
 
	return 0;
}

int cEthernetM::Write(unsigned char *pWriteOutBuf,int* pn) 
{//ф. возвращает 0 в случае успеха, 1 - в случае неудачи
 //создает заголовок пакета + данные
	int iSuccess = 1;
	unsigned char  macAddrBroadcast[]={0xff,0xff,0xff,0xff,0xff,0xff};

	(*pn) = 0;
    	
    	//мен_м адр. ист. на адр. назн
    	//memcpy(m_arpH.DstMac,m_arpH.SrcMac,MAC_ADDR_LEN);
	memcpy(&m_arpH.DstMac[0],macAddrBroadcast,MAC_ADDR_LEN); //отв. широков. для рез. арм
	// в адр. ист подст. собста адр.
	memcpy(&m_arpH.SrcMac[0], m_macAddr, MAC_ADDR_LEN); // я источник
	
	for(int i=0;i<MAC_ADDR_LEN;i++)
	{	
		pWriteOutBuf[i]=m_arpH.DstMac[i]; //D0-D5
		pWriteOutBuf[i+MAC_ADDR_LEN]=m_arpH.SrcMac[i];//D6-D11
	}

	if(m_arpH.type == ETHERNET_TYPE_ALL) 
	{
		pWriteOutBuf[12]= (unsigned char)(ETHERNET_TYPE_SAKSD>>8);      //pWriteOutBuf[12]=0xbe;
        	pWriteOutBuf[13]= (unsigned char)ETHERNET_TYPE_SAKSD; 
	}else
	{
    		pWriteOutBuf[12]= (unsigned char)(m_arpH.type>>8);	//pWriteOutBuf[12]=0xbe;
    		pWriteOutBuf[13]= (unsigned char)m_arpH.type; 		//pWriteOutBuf[13]=0xef;
	}

	pthread_mutex_lock(&m_lock_r);// + учесть одиночный адресс абонента => не пускать SINX
	if((m_protoCommandH.adrByte & 0x1f) == 0x1f)
	{  
		if(m_adr ==1 || m_adr == 2 || m_adr == 0){pWriteOutBuf[14+m_lenSysInfo] = m_protoCommandH.adrByte;}
		else{ return iSuccess; }//свой адрес- не готов
	}//SINX
	else
	{//SUBSCRIBER or адресат 	
		pWriteOutBuf[14+m_lenSysInfo] = m_protoCommandH.adrByte;//0x40 || 0x60; //MASK_ADDR, MASK_STATE

//		if((m_protoCommandH.adrByte&0x60)==0x60) {m_bNoWait=true;}
	} //адр. байт:  данные |0x40, ком байт|0x80 - запрос (ЦВМ-ВУ-ЦВМ) или если абонент,то адр. байт + 0xС0 - ответ с данными, ком. байт 0x86: абоенет ГОТов

    	pWriteOutBuf[15+m_lenSysInfo] = m_protoCommandH.comandByte; 	  	   // командная строка + данные (ЦВМ-ВУ-ЦВМ)
        pthread_mutex_unlock(&m_lock_r);

	//---системная информация 4 байта--------------
	//+формирование системной инф.
	//m_systemInfo[0] = m_protoCommandH.adrByte ;m_systemInfo[1] = 1;
        for(int s=0; s<m_lenSysInfo;s++)
                pWriteOutBuf[14+s] = m_systemInfo[s];//14
        //---------------------------------------------
    
	pthread_mutex_lock(&m_lock_w);

    	pWriteOutBuf[16+m_lenSysInfo] = (unsigned char)(m_protoCommandH.N>>8);//20
	pWriteOutBuf[17+m_lenSysInfo] = (unsigned char)m_protoCommandH.N;//21

    	if(m_protoCommandH.N<=LEN_BUF_ETHERNET)
	{
            	for (unsigned int i = 0;i<m_protoCommandH.N; i++)
		{
			pWriteOutBuf[i+HEADER_ARP_LEN+HEADER_PROTO_LEN+m_lenSysInfo] = m_writeBytes[i];
		}

	        (*pn) = m_protoCommandH.N + HEADER_ARP_LEN+HEADER_PROTO_LEN+m_lenSysInfo;
		iSuccess = 0;
	} 

    	pthread_mutex_unlock(&m_lock_w);

	return iSuccess;
}

int cEthernetM::defSinx(unsigned char adrByte, unsigned char otvByte)
{//ф. оперделяет заданный режим работы 
    int success = -2;

    switch(adrByte&0xe0)
    {
        case 0: //посылка пришла без данных, принята синхронизация 
        {
            if((adrByte&0x1f) != 0x1f)
            {
                success = -2; //-1;
                SYSLOG_PRINTF("cEthernetM::defSinx: Error in thread %d",m_nTh);
                break;
            }

	    //SYSLOG_PRINTF("cEthernetM::defSinx: SINX adr %x",adrByte);
	    //who is who
	    //if(своя SINX)
            success = 1;
	    //if(чужая SINX) succes = 3 ;
        }
        break;
        case (0xC0)://Ответ с даннымии
        {//ГОТ + ИСПР
	    //if(((adrByte&0x1f) == m_adr) || (m_adr==1) || (m_adr==0))//???

	   if((otvByte&0xC0) == 0x40) // не ГОТ и не ИСПР
	   {
		success = -1;
      	   }else success = 0; //ГОТ и ИСПР
        }
        break;
	case (0x40)://Запрос 
        {
	   if((adrByte&0x1f) == m_adr) //|| (m_adr==1) || (m_adr==0))//???
	   {// если адрес сервера - Slave
	   	if((otvByte&0x80) == 0x80) //Запрос данных
	   	{
			success = 0; //ответить
      	   	}else success = 0; //не отвечать
	   } else success = -2;// данные не нужны, не распознаны
        }
        break;
    }

    return success;
}

int cEthernetM::writeEth(int addr,unsigned char comByte, unsigned char* pBuf, int len)
{
//return > 0 is send
//#define ETHWRITE_NOSEND  0, don't send 
//#define ETHWRITE_ERROR -1 (sendto)	


	unsigned char tempWrite[LEN_BUF_ETHERNET] = {0};
	int rez = 0;
	
	writeInMemberMass(pBuf,len);

    	m_protoCommandH.N = len;
	m_protoCommandH.adrByte = addr;
	m_protoCommandH.comandByte = comByte;

	int nw=0;

	//if(isConnectEth()) //если нет соединения
	if(Write(&tempWrite[0],&nw)==0)//make package from member mass
        {
		
        	rez = sendto(m_sock, tempWrite, nw,MSG_DONTWAIT,NULL,0);
                if(rez<0) 
                {
                	SYSLOG_ERROR("cEthernetM::task: error sendto -> reset!");
			perror("sendto");
			return rez;
                }

		if(rez != nw) { SYSLOG_ERROR("cEthernetM::task: error sendto: do not send all data!!!"); }
		
		//printf("\nsendto: pkg size %d: ",nw);
		//for(int i = 0; i<nw; i++){ printf("%x,",tempWrite[i]); }
		//printf("\n");
	} else rez=-1;

	return rez;
}

cEthernetM* cEthernetM::getObj(int index)
{
	if(index == m_sock)//m_indexObj)
	return this;
	else return NULL;
}

/*static*/
int cEthernetM::waitData(struct timeval* tVal,struct param* pparam)
{
	startTimer(0);

	FD_ZERO(&m_rdfs);

	for(int i = 0; i<m_countObj; i++)
		FD_SET(m_sockets[i].s,&m_rdfs);

	if(m_fd_timer>=0)
	FD_SET(m_fd_timer, &m_rdfs);

	m_maxfd = m_sockets[0].s;
        for(int i = 1; i<m_countObj; i++)
        {
                if(m_sockets[i].s>m_maxfd)
                m_maxfd = m_sockets[i].s;
        }

	//printf("\n fd_max %d",m_maxfd); 

	int rez = 0;

	rez = select(m_maxfd+1, &m_rdfs, NULL, NULL, tVal); // если tVal = NULL (нет времени ожидания - select будет ожидать изменений неопределенное время)

	if(rez < 0) {perror("select"); /*return rez;*/    SYSLOG_ERROR("cEthernetM::waitData: error<0 (select)");}
	//if(!rez)    {perror("wait select"); /*return 0;*/ SYSLOG_ERROR("cEthernetM::waitData: error=0 (wait select)");}
	if(rez==0)    {perror("wait select"); SYSLOG_ERROR("cEthernetM::waitData: error=0 (wait select)"); return 0; }

	if(rez>0) 
	{	int is=0;
		for(;is<m_countObj;is++)
                {
  			if(FD_ISSET(m_sockets[is].s, &m_rdfs))
			{
				pparam->s = m_sockets[is].s;
				pparam->p = m_sockets[is].p;
				//FD_CLR(m_fd_timer,&m_rdfs); // убрать из набора дескриптор таймера
				//stopTimer(0);!!!!

				return m_sockets[is].s;// 0 - есть 1 ответ, 1  - есть и второй ответ...5 - есть и 6 ответ
			}
		}

		if(FD_ISSET(m_fd_timer, &m_rdfs))
		{
			pparam->s = -1;
                        pparam->p = NULL;

			return m_fd_timer;
		}

	}

	return -1;
}

int cEthernetM::readEth(unsigned char* addr,unsigned char* answByte,unsigned char* pBuf, const unsigned int maxLen, int* pRecvLen)
{
// 1 - is OK, but sinx  #define  ETHREAD_SINX  (1)
// 2 - is OK  		#define  ETHREAD_ISOK  (2)
// 0 - no data  	#define  ETHREAD_NO_DATA  ( 0)
// -1- error 		#define  ETHREAD_ERROR_SUB (-1)
// -2 -error 		#define  ETHREAD_ERROR_SOCK (-2)

	int rez=0;
	unsigned char tempRead[LEN_BUF_ETHERNET] = {0};
	*addr=0; *pRecvLen=0; *answByte=0;

	int nr = recvfrom(m_sock,tempRead,LEN_BUF_ETHERNET,MSG_DONTWAIT,NULL,NULL);
	if(nr>0)
       	{
		int rezR = Read(tempRead,nr);//form member mass
       	    	if(rezR==2 && m_protoAnswerH.N<=maxLen)
       	    	{
			readFromMemberMass(pBuf,pRecvLen);
			*addr = m_protoAnswerH.adrByte;
			*answByte = m_protoAnswerH.otvByte;
			*pRecvLen = m_protoAnswerH.N;
			//printf("\ncEthernetM::readEth recvfrom %d\n",nr);
			rez = 2;//data
		} else if(rezR==1 || rezR ==3 ) { rez = rezR; *addr = m_protoAnswerH.adrByte;	*answByte = m_protoAnswerH.otvByte; *pRecvLen=0; }//sinx
			else { rez = /*-1*/ rezR;} // (0 | -1) - нет данных от абонента или не готов.неисправен абонент
	} else { rez = -2; /*nr;*/ }//no date, error recvfrom

	return rez;
}

int cEthernetM::readEthOnce(unsigned char* addr,unsigned char* answByte,unsigned char* pBuf, const unsigned int maxLen, int* pRecvLen,struct timeval* tVal)
{

// 1 - is OK, but sinx  #define  ETHREAD_SINX  (1)
// 2 - is OK            #define  ETHREAD_ISOK  (2)
// 0 - no data          #define  ETHREAD_NO_DATA  ( 0)
// -1- error            #define  ETHREAD_ERROR_SUB (-1)
// -2 -error            #define  ETHREAD_ERROR_SOCK (-2)

	FD_ZERO(&m_rdfs);//если для каждого канала в отдельности (индивидуально - последовательно)

	//if(m_bNoWait) {m_bNoWait=false; return 2;}

	FD_SET(m_sock, &m_rdfs);//по какому каналу 3апросили, по тому и ждет

	int rez = -2;
	// здесь таймер в наборе не учавствует
	rez = select(m_sock+1, &m_rdfs, NULL, NULL, tVal); // если tVal = NULL (нет времени ожидания - select будет ожидать изменений неопределенное время)

	//if(rez < 0) {perror("select");return rez;}
	//if(!rez) {perror("wait select"); return 0; }

	if(rez>0)
	{
	unsigned char tempRead[LEN_BUF_ETHERNET] = {0};
	*addr=0; *pRecvLen=0; *answByte=0;
  	if(FD_ISSET(m_sock, &m_rdfs))
	{
		int nr = recvfrom(m_sock,tempRead,LEN_BUF_ETHERNET,MSG_DONTWAIT,NULL,NULL);
		if(nr>0)
        	{
			int rezR = Read(tempRead,nr);//form member mass
        	    	if(rezR==2 && m_protoAnswerH.N<=maxLen)
        	    	{
				readFromMemberMass(pBuf,pRecvLen);
				*addr = m_protoAnswerH.adrByte;
				*answByte = m_protoAnswerH.otvByte;
				*pRecvLen = m_protoAnswerH.N;
				//printf("\ncEthernetM::readEthOnce recvfrom %d\n",nr);
				rez = 2;//data
			} else if(rezR==1 || rezR ==3 ) { rez = rezR; } //sinx
				else { rez= rezR;/*-1*/} // (0 | -1) - no date from sub or sub don't ready
		} else { rez = /*nr;*/ -2; } //error socket

	} else rez = 0;//no date 
	}

	return rez;
}

bool cEthernetM::isConnectEth()
{
	static bool bErrPrint;
	if (ioctl(m_sock, SIOCGIFFLAGS, &m_ifr) < 0)
	{
		char tmp[BUFSIZ];
		sprintf(tmp,"cEthernetM: SIOCGIFFLAGS (%s)",m_ifr.ifr_name);
		SYSLOG_ERROR(tmp);
          	return false;
    	}

	if((m_ifr.ifr_flags&IFF_UP) && (m_ifr.ifr_flags&IFF_RUNNING)) 
	{ return true; bErrPrint = false; }

	if(!bErrPrint)
	{
		bErrPrint = true;
		char tmp[BUFSIZ];
		sprintf(tmp,"cEthernetM: '%s' is NO CONNECT",m_ifr.ifr_name);
		SYSLOG_ERROR(tmp);
	}

	return false;
}

void cEthernetM::startTimer(int fd)
{

	if(m_fd_timer == -1) 
	{ 
		// SYSLOG_ERROR("cEthernetM::ioctl: KSDT_IOC_START_TIMER fd=0");
		 return; 
	}

        if(ioctl(m_fd_timer,KSDT_IOC_START_TIMER)<0) 
        {perror("ioctl: KSDT_IOC_START_TIMER"); SYSLOG_ERROR("cEthernetM::ioctl: KSDT_IOC_START_TIMER");}

}

bool  cEthernetM::waitTimerTick(int _fd)
{
	if(m_fd_timer==-1) return false;

	char bufr[1] = {0};
        if(read(m_fd_timer,bufr,1)<0) 
	{
		//perror("read"); 

		char tmp[BUFSIZ];
                sprintf(tmp,"cEthernetM: read timer");
                SYSLOG_ERROR(tmp);

		return false; 
	}

	return true;
}

int  cEthernetM:: initTimer(char* name)
{
	return open(name,O_RDONLY);
}

void  cEthernetM::delTimer(int _fd)
{
	if(m_fd_timer==-1) return;

	close(m_fd_timer);
}

int  cEthernetM::getPeriod(int fd)
{
	if(m_fd_timer == -1)
	{
		SYSLOG_ERROR("cEthernetM::getPeriod: m_fd_timer=-1");  
		return 0;
	}

	int per=0;
	if(ioctl(m_fd_timer,KSDT_IOCG_PERIOD,&per)<0) 
	{perror("ioctl: KSDT_IOCG_PERIOD");  SYSLOG_ERROR("cEthernetM: ioctl: KSDT_IOCG_PERIOD"); }

	SYSLOG_PRINTF("cEthernetM::timer ' %d ' mc", per);

	return per;
}

void  cEthernetM::setPeriod(int fd ,int period)
{
	if(m_fd_timer == -1) 
	{
		SYSLOG_ERROR("cEthernetM::setPeriod: m_fd_timer=-1"); 
		return;
	}

	if(ioctl(m_fd_timer,KSDT_IOCS_PERIOD,&period)<0) 
	{perror("ioctl: KSDT_IOCS_PERIOD"); SYSLOG_ERROR("cEthernetM::ioctl: KSDT_IOCS_PERIOD");}
}

void  cEthernetM::stopTimer(int fd)
{
        if(m_fd_timer == -1) 
	{  
		SYSLOG_ERROR("cEthernetM::stopTimer: m_fd_timer=-1"); 
		return; 
	}

        if(ioctl(m_fd_timer,KSDT_IOC_STOP_TIMER)<0) 
        {perror("ioctl: KSDT_IOC_STOP_TIMER"); SYSLOG_ERROR("cEthernetM::ioctl: KSDT_IOC_STOP_TIMER");}
}

void cEthernetM::resetTimer(int fd)
{
        if(m_fd_timer == -1) 
	{ 
		// SYSLOG_ERROR("cEthernetM::ioctl: KSDT_IOCRESET fd=0"); 
		return; 
	}

	if(ioctl(m_fd_timer,KSDT_IOCRESET)<0) 
        {perror("ioctl: KSDT_IOCRESET"); SYSLOG_ERROR("cEthernetM::ioctl: KSDT_IOCRESET");}
}

void cEthernetM::waitTimer(struct timeval *ptv)
{
	if( ptv == NULL ) return;

     	select(0,NULL,NULL,NULL,ptv);        
}
