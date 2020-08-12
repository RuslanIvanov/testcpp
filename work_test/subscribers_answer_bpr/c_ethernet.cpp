#include "c_ethernet.h"
#include "c_event.h"

#define PRNT
//#define DBG
#include "debugPrint.h"

#define POLICY SCHED_RR
#define PRIO_TH_ETH  50 

int countTh = 0;

extern long  getTid();
 
namespace globalEvents
{
     cEvent eventLan;
     //cEvent eventSinx;
}

cEthernet::cEthernet()
{ 
	strcpy(&m_nameDev[0],"N/A");
    	PRINTF(("\n I'm def constructor cEthernet, name dev %s ",m_nameDev));

	m_adr=0;
	m_thread_id=0;
	m_isSuccess=0;

	m_lenSysInfo=0;

	memset((void *)&m_arpH, 0, sizeof(struct ARP_HEADER));
    	memset((void *)&m_protoCommandH, 0, sizeof(struct PROTO_HEADER_COMMAND));
    	memset((void *)&m_protoAnswerH, 0, sizeof(struct PROTO_HEADER_ANSWER));

	memset((void*)&m_readBytes[0],0,LEN_BUF);
	memset((void*)&m_writeBytes[0],0,LEN_BUF);
	memset((void*)&m_macAddr[0],0,MAC_ADDR_LEN);
	memset((void*)&m_systemInfo[0],0,LEN_SYSTEM_INFO);
	
    	m_sock = -1;
	m_sock2 = -1;
    	m_replaceRegim = 0;
    	m_regim = 0;
    	m_nTh=0;
}

cEthernet::cEthernet(const char* pnameDev)
{
    	m_nTh=countTh++;

    	strcpy(&m_nameDev[0],pnameDev);

	pthread_mutexattr_init(&mattr);

	pthread_mutex_init(&m_lock_w,&mattr);
	pthread_mutex_init(&m_lock_r,&mattr);

	m_thread_id=0;
    	m_isSuccess=1;
   	m_adr =0;
    	m_replaceRegim = 0;
    	m_regim = 0;

	m_lenSysInfo=0;
        
    	memset((void *)&m_arpH, 0, sizeof(struct ARP_HEADER));
    	m_arpH.type = 0xbeef;

    	memset((void *)&m_protoCommandH, 0, sizeof(struct PROTO_HEADER_COMMAND));
    	memset((void *)&m_protoAnswerH, 0, sizeof(struct PROTO_HEADER_ANSWER));

	memset((void*)&m_readBytes[0],0,LEN_BUF);
	memset((void*)&m_writeBytes[0],0,LEN_BUF);
	memset((void*)&m_macAddr[0],0,MAC_ADDR_LEN);
	memset((void*)&m_systemInfo[0],0,LEN_SYSTEM_INFO);

	//создать сокет
		m_sock2 = -1;
    	m_sock = createSocket(&m_nameDev[0]);
    	if(m_sock==-1)
	{
        	ERRORP(("\nUPU_ETH: error create socket"));
       		m_isSuccess = 0;
		return;
	}

    	//setParamForSend();
    	//if(getMac(&m_nameDev[0])!=0) {close(m_sock); return;}

    	if(setAttributsThread()==0)
       		createThread();

    	PRINTF(("\ndev->%s,mac->%x:%x:%x:%x:%x:%x",m_nameDev,
               m_macAddr[0],m_macAddr[1],m_macAddr[2],
               m_macAddr[3],m_macAddr[4],m_macAddr[5]));
}

cEthernet::~cEthernet() 
{

	/* проверяем, не завершился ли thread_child */
	if (pthread_kill(m_thread_id, 0) != ESRCH)
	{
		/* посылаем thread_child служебный сигнал, который ее завершает */
		pthread_cancel(m_thread_id);
		/* закрываем дескриптор thread_child */
       		pthread_join(m_thread_id, 0x00);
	}
	
	pthread_mutex_destroy(&m_lock_r);	
	pthread_mutex_destroy(&m_lock_w);
	m_thread_id = 0; 
    	DEBUGP(("\n destr %s",m_nameDev));

    	if(close(m_sock)!=0)
                {ERRORP(("\nUPU_ETH: error close cocket"));}
   	 m_sock = -1;
		m_sock2 = -1;
    	pthread_mutexattr_destroy(&mattr);

    	pthread_attr_destroy(&m_attr_thread);

     	PRINTF(("\n~cEthernet()"));
}

unsigned char cEthernet::readAdr()
{// ф. читает установленный адрес абонента на шине
    return m_adr;
}

void cEthernet::SetSock2(int s) 
{
	m_sock2 = s;
}

int cEthernet::GetSock2() 
{
	return m_sock;
}


void cEthernet::setAdr(unsigned char adr)
{//ф.устанавливает адрес абонента на шине по протоколу обмена
    m_adr = 0;
    if(adr>=10 && adr<=13)
    {
           m_adr = adr;
           PRINTF(("\nm_adr: UPU: %d\n", m_adr));
    }

    if(adr == 18) 
    {
	   m_adr = adr;
           PRINTF(("\nm_adr: ARM SHN: %d\n", m_adr));
    }
}

void cEthernet::setDiagInfoForArm(bool b)
{

	if(b) 
	{
		m_lenSysInfo = LEN_SYSTEM_INFO;
		PRINTF(("\nUPU_ETH: USE SYSTEN INFORM"));
	}
	else 
	{ 
		m_lenSysInfo = 0;
		PRINTF(("\nUPU_ETH: NO USE SYSTEN INFORM"));
	}

}

void  cEthernet::createThread()
{
	m_param.par = 0; 
	m_param.p=this;

    	if(pthread_create(&m_thread_id,&m_attr_thread,&threadFunc,&m_param)!=0)
    	{
         	ERRORP(("\nUPU_ETH: Error create thread eth"));
         	m_isSuccess = 0;
    	}
}

int cEthernet::setAttributsThread()
{// ф. устанавливает приоритет потока. 0 - успешно, -1 - неуспешно

    int ret=0;

    if(pthread_attr_init(&m_attr_thread)>0)
    {
        ERRORP(("\nUPU_ETH: error set attrib!"));
        return -1;
    }

    if(pthread_attr_setinheritsched(&m_attr_thread,PTHREAD_EXPLICIT_SCHED)>0)
    {
        ERRORP(("\nUPU_ETH: error pthread_attr_setinheritsched in setAttributsThread()"));
        return -1;
    }

    ret = pthread_attr_setscope(&m_attr_thread,PTHREAD_SCOPE_SYSTEM);//PTHREAD_SCOPE_PROCESS);
    if(ret>0)
    {
        ERRORP(("\nUPU_ETH: error run pthread_attr_setscope in createThreadSinx(): "));

        switch(ret)
        {
            case EINVAL:
                 ERRORP(("The value of contentionscope is not valid"));
            break;
            case ENOTSUP:
                 ERRORP(("An attempt was made to set the attribute to an unsupported value."));
            break;
        }

        return -1;
    }//*/

    if(pthread_attr_setschedpolicy(&m_attr_thread,POLICY)>0)
    {
        ERRORP(("\nUPU_ETH: error pthread_attr_setschedpolicy in setAttributsThread()"));
        return -1;
    }

    sched_param sp;
    sp.sched_priority = PRIO_TH_ETH;

    ret = pthread_attr_setschedparam(&m_attr_thread,&sp);
    if(ret>0)
    {
         ERRORP(("\nUPU_ETH: error pthread_attr_setschedparam in setAttributsThread(): "));
        switch(ret)
        {
        case EINVAL:
             ERRORP(("The value of param is not valid"));
            break;
        case ENOTSUP:
             ERRORP(("An attempt was made to set the attribute to an unsupported value"));
            break;
        }

        return -1;
    }

    return 0;
}

int cEthernet::createSocket(char *dev_name)
{
	// Create communication socket and bind it with the specified net interface.
	// _in char *dev_name	- name of the net interface to use;
	// _out	int			- socket descriptor.

	int sockd;

	// create socket
    sockd = socket(PF_PACKET, SOCK_RAW, htons(m_arpH.type));
	if (sockd < 0)
    { ERRORP(("\nUPU_ETH: Can not create raw socket")); return -1;}

	// bind the socket to the specified net interface
    memset((void *)&m_ifr, 0, sizeof(struct ifreq));
    memcpy(m_ifr.ifr_name,dev_name,strlen(dev_name));

    if (ioctl(sockd, SIOCGIFINDEX, &m_ifr) == -1)
    {
          ERRORP(("\nUPU_ETH: No such interface: %d",errno));
          close(sockd);
    }

    memset(&m_socket_address, 0, sizeof (m_socket_address));
    m_socket_address.sll_family    = PF_PACKET;
    m_socket_address.sll_ifindex   = m_ifr.ifr_ifindex;
    m_socket_address.sll_protocol  = htons(m_arpH.type);

    PRINTF(("\nUPU_ETH: interface %s->%d",m_ifr.ifr_name,m_socket_address.sll_ifindex));
    PRINTF(("\n"));

    if(bind(sockd,(struct sockaddr*)&m_socket_address,sizeof(m_socket_address))< 0)
    {
         ERRORP(("\nUPU_ETH: Can not bind socket to the specified net interface!"));
         close(sockd);
         return -1;
     }//*/

    if (ioctl(sockd, SIOCGIFHWADDR, &m_ifr) < 0)
    {ERRORP(("\nUPU_ETH: error ioctl")); return -1;}

    memcpy(m_macAddr,(char *)&(m_ifr.ifr_hwaddr.sa_data),6); // mac утройства

	return sockd; 
}

int  cEthernet::getMac(char* dev_name)
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
    
    	//printf("\n%.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);

	for(int i=0; i<6; i++)
		m_macAddr[i]=mac[i];
	//system("touch info.txt;ifconfig | grep \"eth\" > info.txt");

	close(fd);
	return 0;
}

int cEthernet::isSuccessInitObj()
{return m_isSuccess;}

int cEthernet::task(void* par)
{
    while(1)
    {
	unsigned char tempRead[LEN_BUF] = {0};
	unsigned char tempWrite[LEN_BUF] = {0};

    int nr = recvfrom(m_sock,tempRead,LEN_BUF,0,NULL,NULL);
    if(nr>0) 
    {
            int rezR = Read(&tempRead[0],nr);
            if(rezR==2)
            {
                //globalEvents::eventLan.Set((unsigned int)this);
	        int nw = 0;
		if(Write(&tempWrite[0],&nw)==0) 
        	{
                    int rez = sendto(m_sock, tempWrite, nw,0,NULL,0);//,(struct sockaddr *)&m_socket_address,sizeof(m_socket_address));

		    int rez2 = -1;
		    //Дубль во вторую сеть
		    if(m_sock2 != -1 ) //&& m_sock2 != NULL)
		    { rez2 = sendto(m_sock2, tempWrite, nw,0,NULL,0); }

                    if( (rez>=0) || (rez2>=0) ) //отправка старых данных
                    {
                        //globalEvents::eventLan.Set((unsigned int)this);// а точно здесь?
			//globalEvents::eventLan.Set(reinterpret_cast<unsigned int>(this));
			globalEvents::eventLan.Set(this);	
			//char tmp[100]="";
			//sprintf(tmp,"%p",this);
			//unsigned int adr = atoi(tmp);
			//globalEvents::eventLan.Set(adr);
			printf("\nOBG %p, Set",this);
		    } else {

			        if(rez < 0)
				{ ERRORP(("\nUPU_ETH: error sendto in eth0")); }

				if(rez2 < 0)
				{ ERRORP(("\nUPU_ETH: error sendto in eth1")); }

				globalEvents::eventLan.Reset();
                           }
			}

	                   /* if(rez>=0) //отпправка старых данных
        	            {globalEvents::eventLan.Set((unsigned int)this);
		    		}else{ERRORP(("\nUPU_ETH: error sendto -> reset!"));
			        	//globalEvents::eventLan.Reset();
                    }}*/
		
            }
            if(rezR==1)
            {
               // globalEvents::eventSinx.Set(m_protoCommandH.comandByte);   // сброс в threadSinx()
            }
        }else { ERRORP(("\nUPU_ETH: error recvfrom!"));}
    }

    PRINTF(("\ncEthernet::task END..."));
    return 0;
}

void cEthernet::setParamForSend()
{
        memset(&m_socket_address,0,sizeof(m_socket_address));

        //RAW communication
        m_socket_address.sll_family = AF_PACKET;

        //m_socket_address.sll_ifindex=if_nametoindex("eth0");
        m_socket_address.sll_ifindex=m_ifr.ifr_ifindex;
        m_socket_address.sll_halen = ETH_ALEN;

}

void* cEthernet::threadFunc(void* par)
{ 
	char tmpLog[100];

	sprintf(tmpLog,"ETH TASK %ld",getTid());
	PRINTF(("\neth_t350: '%s'",tmpLog));

	((param*)par)->p->task(par); 
    
	return NULL;
}

void cEthernet::readEth(unsigned char* pRead,unsigned short* pn)
{
    	pthread_mutex_lock(&m_lock_r);//??

    	for(int i = 0;i<m_protoCommandH.N;i++)
	{
		pRead[i] = m_readBytes[i];
	}

    	//(*pn) = m_nR;
    	(*pn) = m_protoCommandH.N;

	pthread_mutex_unlock(&m_lock_r);
}

void cEthernet::writeEth(unsigned char* pWrite, unsigned short n)
{
	pthread_mutex_lock(&m_lock_w);

	for(int i = 0;i<n;i++)
	{
		m_writeBytes[i] = pWrite[i];
	}
    	//m_nW = n;
   	m_protoAnswerH.N = n;

	pthread_mutex_unlock(&m_lock_w);
}

int cEthernet::Read(unsigned char* pReadInBuf, int n) // куда пишет и скоько									
{// ф. возвращает 0 - данные не распознанны,
 // ф. возвращает 1 - пришла синхронизация, анализ режима работы СЦВС
 // ф. возвращает 2 - пришли данные

    //if(((pReadInBuf[14]&0x1f)!=0x1f && (pReadInBuf[14]&m_adr)!=m_adr)|| m_adr<=0) return 0; // (не широковещательная посылак и не адрес абонета) или адрес абонента не верен

    if(m_adr == 0 ) return 0;

    if((pReadInBuf[14+m_lenSysInfo]&0x1f)==0x1f ||(pReadInBuf[14+m_lenSysInfo]&(0x1f|0x40)) == (m_adr|0x40))
    {

    int rezS = defSinx(pReadInBuf[14+m_lenSysInfo]);
    if(rezS == -1) return 0;

    if (rezS == 1) // синхронизация (данных нет!)
    {
        m_protoCommandH.adrByte = pReadInBuf[14+m_lenSysInfo]&0x01f;
        m_protoCommandH.comandByte = pReadInBuf[15+m_lenSysInfo];
        return 1; // ответа по шине не будет при синхр.
    }

    // пришли данные
	for(int i=0;i<MAC_ADDR_LEN;i++)
	{//запомнил HEADER
		m_arpH.DstMac[i]=pReadInBuf[i]; //D0-D5 не нужно
	 	m_arpH.SrcMac[i]=pReadInBuf[i+MAC_ADDR_LEN];//D6-D11
	}

	pthread_mutex_lock(&m_lock_r);
    	m_protoCommandH.N = 0;
	pthread_mutex_unlock(&m_lock_r);

	//---системная информация 4 байта--------------
	for(int s=0; s<m_lenSysInfo;s++)
		m_systemInfo[s] = pReadInBuf[14+s];
	//---------------------------------------------

	if(n>=HEADER_ARP_LEN)
	{
		pthread_mutex_lock(&m_lock_r);
        	m_protoCommandH.N=pReadInBuf[16+m_lenSysInfo];
        	m_protoCommandH.N=(m_protoCommandH.N<<8)|pReadInBuf[17+m_lenSysInfo];
		
        	if(m_protoCommandH.N>MAX_ARP_DATA_LEN)
        	{
		
            		m_protoCommandH.N=0; 
			pthread_mutex_unlock(&m_lock_r);

			printf(" N>MAX ");
            		return 0;
		}
		

        	for(int i=0;i< m_protoCommandH.N;i++)
			m_readBytes[i]=pReadInBuf[i+HEADER_ARP_LEN+HEADER_PROTO_LEN+m_lenSysInfo];  // c D18
        	//m_protoCommandH.N;//всего  значимых данн.

        	//// перезаписывание адреса абонента для ответа
        	m_protoAnswerH.adrByte = pReadInBuf[14+m_lenSysInfo]&0x1f;
        	m_protoAnswerH.otvByte = 0x86;//def

		pthread_mutex_unlock(&m_lock_r);

        	return 2;
	}
    }

    return 0;
}

int cEthernet::Write(unsigned char *pWriteOutBuf,int* pn) 
{//ф. возвращает 0 в случае успеха, 1 - в случае неудачи

	int iSuccess = 1;
	unsigned char  macAddrBroadcast[]={0xff,0xff,0xff,0xff,0xff,0xff};

	(*pn) = 0;

	if(((m_protoAnswerH.adrByte)&0x1f) == 18 )  	return iSuccess;     	
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

    	pWriteOutBuf[12]= (unsigned char)(m_arpH.type>>8);//pWriteOutBuf[12]=0xbe;
    	pWriteOutBuf[13]= (unsigned char)m_arpH.type; //pWriteOutBuf[13]=0xef;

    	pthread_mutex_lock(&m_lock_r);
    	pWriteOutBuf[14+m_lenSysInfo] = 0xc0|(m_protoAnswerH.adrByte);// отв. байт + данные ??
    	pWriteOutBuf[15+m_lenSysInfo] = m_protoAnswerH.otvByte;//+ - тут вставлять диагностику от рм
    	pthread_mutex_unlock(&m_lock_r);

	//---системная информация 4 байта--------------
	for(int s=0; s<m_lenSysInfo;s++)
		pWriteOutBuf[14+s] = m_systemInfo[s];
	//---------------------------------------------

    	pthread_mutex_lock(&m_lock_w);

    	pWriteOutBuf[16+m_lenSysInfo] = (unsigned char)(m_protoAnswerH.N>>8);
    	pWriteOutBuf[17+m_lenSysInfo] = (unsigned char)m_protoAnswerH.N;

    	if(m_protoAnswerH.N<=LEN_BUF)
	{
        	for (int i = 0;i<m_protoAnswerH.N; i++)
		{
			pWriteOutBuf[i+HEADER_ARP_LEN+HEADER_PROTO_LEN+m_lenSysInfo]= m_writeBytes[i];
		}
            	(*pn) = m_protoAnswerH.N + HEADER_ARP_LEN+HEADER_PROTO_LEN+m_lenSysInfo;
		iSuccess = 0;
	}

    	pthread_mutex_unlock(&m_lock_w);

	return iSuccess;
}

void cEthernet::setDiagByte(unsigned char diag)
{
    pthread_mutex_lock(&m_lock_r);
    m_protoAnswerH.otvByte = diag;
    pthread_mutex_unlock(&m_lock_r);
}

int cEthernet::defSinx(unsigned char adrByte)
{//ф. оперделяет заданный режим работы СЦВС
    int success = -1;

    switch(adrByte&0xe0)
    {
        case 0: //посылка от АРМ без данных, принята синхронизация от АРМ
        {
            if((adrByte&0x1f) != 0x1f)
            {
                success = -1;
                ERRORP(("\nUPU_ETH: Error in thread%d",m_nTh));
                break;
            }
            success = 1;
        }
        break;
        case 0x40: //Посылка от АРМ с данными
        {
            success = 0;
        }
        break;
    }
    return success;
}


