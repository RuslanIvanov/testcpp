
#include <unistd.h>
#include <signal.h>
#include <sys/resource.h>
#include <sys/syscall.h>
#include <time.h>

#include "c_data.h"
#include "c_event.h"
#include "c_ethernet.h"
#include "c_timer.h"
#include "c_timersys.h"
#include "c_finddev.h"
#include "globals.h"

namespace globalEvents
{
	extern cEvent eventLan;
	extern cEvent eventSinx;
}
int nDev,initType;;
int count, adr;
cEthernet **pEth;
unsigned char nummsg;
unsigned char countU=0;
unsigned char countInit=0;
unsigned char countIsTrain=0;
unsigned char DELAY_INIT=1;
unsigned char DELAY_TRAIN=0;
unsigned char tx[512] = {0x88,0x0,0x0,0x99,0x43,0,0}; 
unsigned short nt=7;
char nameEth[2][80]={"enp2s0:0","dum0"};

void out(int);
void init();
void init2();
bool bOut;
bool bMsgRm;
bool bSysInfo;
bool isInInWork;
unsigned char NTrain;
unsigned char countTick;

unsigned short idTrain = 313;

void timerFunc1(sigval)
{

	if(countTick>=20)
	{
		printf("\nsubscriber '%xh': NO CONNECT with SERVER (ARM)\n",adr);
	}else{countTick++;}
}

void timerFunc2(sigval)
{
    //printf("\n..tick2");
}

long  getTid()
{
    long tid;
    tid = syscall(SYS_gettid);
    return tid;
}

int main(int argc, char* argv[])
{
	signal (SIGINT, out); // установить сигнал SIGINT
	signal (SIGTERM, out);

	int opt;
   	while((opt= getopt(argc, argv, "sha:n:e:E:i:t:D:")) != -1)
    	switch(opt)
    	{
	    case 'a': sscanf(optarg,"%d",&adr); break;
		case 'n': sscanf(optarg,"%hhu",&NTrain);
		 // if(NTrain) bMsgRm = true; 
		break;
		case 's': bSysInfo = true; break;
		case 'e': sscanf(optarg,"%s",&nameEth[0][0]); nDev++; initType=2; break;
        case 'E': sscanf(optarg,"%s",&nameEth[1][0]); nDev++; initType=2; break;
		case 'i': sscanf(optarg,"%d",&initType); break;
		case 't': sscanf(optarg,"%hu",&idTrain); break;
		case 'D': sscanf(optarg,"%hhu",&DELAY_INIT); break;

	    case 'h':
        printf("\t-h\t help (this message)\n");
		printf("\t-n\t N train\n");
        printf("\t-a\t address UPU or SHN (10,11,12,13, 18 - ARM_SHN)\n");
	    printf("\t-n\t set system information for new QFleet in ver.5.5.5 and more\n");
		printf("\t-e\t eth0 name\n");
	    printf("\t-E\t eth1 name\n");
		printf("\t-i\t init type: if type=2 use '-e' and '-E' param else auto find ethernet\n");
		printf("\t-t\t id train\n");
		printf("\t-D\t Delay init in ehternet takts\n");
       	return 0;
    	}

		if(initType==2)
			init2();
		else
			init();

		cTimerrt t(450);
	        if(t.setTimerrt(timerFunc1)==-1) {perror("setTimerrt 1"); return 0;}


        	bMsgRm = false;
		nummsg=0;

		while(bOut == false)
		{
			//unsigned int p=0;
			void* p=0;
			if(globalEvents::eventLan.Wait(&p)==true)
			{
				globalEvents::eventLan.Reset();   
		 		if(p==0) return 0;
				printf("\nOBG %p Reset",((cEthernet*)p));

				countTick=0;
				unsigned char rx[1550]={0};
				unsigned short n=0;

				printf("\naddress obj eth '%p', addr subscriber '%x'",((cEthernet*)p),adr);

				((cEthernet*)p)->readEth(&rx[0],&n); // предоставляет только те данные, кот., нужны РМ 

			    	printf("\nrx->[%d]: ",n);
				for(int i = 0;i<n;i++)
					printf(".%x",rx[i]);

				if(adr>=10 && adr<=13)
				{

					//if(countIsTrain>100)// поезд на ГСП
					{
						tx[19] = 1; tx[20]=0;
					//	if(countIsTrain>200)
						if(((rx[1]&0x1)==0x1) && ((rx[1]&0x2)==0x2))
            					{
	                				bMsgRm=true; 
							tx[19] = 1; tx[20]=0;
        	    				} //countIsTrain++;
					} //else countIsTrain++;

					switch(rx[4])
					{//COD
					case 0xFF: 
					{
						tx[4] = 0x43;
						printf("\n\t\tRESET RM"); 

						for(int i=5; i<8; i++)
						{
								tx[i] = 0; 
						}
						bMsgRm = false; 
						countInit=0;
						break; 
					}
					case 0xFE:
                    			{
                      				printf("\n\t\tSTOP INIT RM"); 
					}
					break;
					case 0x1:  
					tx[4] = 0xc0; for(int i=5;i<8;i++)
					{
						tx[i] = rx[i]; 
					}
					
					if(isInInWork)
					countIsTrain++;

					break;
					case 0x2:  
					tx[4] = 0x40;
					for(int i=5;i<8;i++){tx[i] = rx[i]; } 
		
					if(isInInWork)
					countIsTrain++;

					break;
					case 0x3: 
					{				

						if((rx[5]&0x3f)==0) 
						{
							tx[4] = 0x43; 
							for(int i=5; i<8; i++)
							{
								tx[i] = 0; 
							}
							break;
						}	

						if(countInit>=DELAY_INIT)
						{
						
						if((rx[5]&0x80)==0x80)
						{
							tx[4] = 0xC0;
						}else
						{
							tx[4] = 0x40;
						}

						for(int i=5;i<8;i++)
						{
							tx[i] = rx[i];
						}
 
						bMsgRm = false;  
						isInInWork = true;

						}else
						{ 
							countInit++;
							 printf("\n\t\tDELAY %d INIT RM",countInit);
						}
						
					}
					break;
					}
			//--

			if( ((rx[1]&0x1)==0) && ((rx[1]&0x2)==0) ) { countU=0; bMsgRm=false; nt=7; tx[6] = 0; tx[1] = 0x0; tx[2] = 0x0; printf("\nNO TRAIN"); }
			//--
			//if( nummsg==3 ) { countU=0; nummsg=0; tx[6] = 0; tx[1] = 0x0; tx[2] = 0x0; nt=7; bMsgRm=false; printf("\nNtrain 0"); }
			//--
			tx[18] = rx[18]; //счетик

			tx[19]  = 1; 
			//31/01/2020//////////////////////
			if((rx[1]&0x1)==0x1)
			{
				tx[1] |= 0x20; // вкл = испр
				printf("\nadr %xh: DP1 ON",adr);

			}else {
					tx[1] &= ~0x30;
					printf("\nadr %xh: DU1 OFF",adr);
				  }

			if((rx[1]&0x2)==0x2)
			{
				tx[2] |= 0x20; // вкл = испр
				printf("\nadr %xh: DU2 ON",adr);
			}else{
					tx[2] &= ~0x30;
					printf("\nadr %xh: DU2 OFF",adr);
				 }
			//////////////////////////////////
		
			//--------------------------------
			nt = 17;
			if(bMsgRm)
			{
					tx[19]=1; // ЧП
					tx[20]=52;// данные
					tx[21]=1; // Номер версии
	
					tx[22] = 0xff;
					tx[23] = 0xff;
					tx[24] = idTrain>>8;
					tx[25] = idTrain;
					
					tx[26] = idTrain>>8;
					tx[27] = idTrain;
					tx[28]++;//==10

					tx[29] =  rx[29];

					tx[30] = 52-10;

					for(unsigned char i=31;i<42;i++)
					{
							tx[i] = 1;
					}

					nt = 52+9+5+3;


                                        if(countU>=20 && countU<=151)
                                        {     
                                            tx[1] = 0x30;// вкл датчик1 и инф
					}

					if(countU>=150 && countU<=151)
                                        {
                                                tx[2] = 0x30;// вкл датчик2 и инф

                                        }

					if(countU>=254)
					{
						//nummsg=3;

						if((rx[1]&0x1)!=0x1) //31/01/2020///////////
						{
							tx[1] = 0x0; //выкл должен по команде
							printf("\nadr%xh: Ntrain 3, OFF 1 ",adr);
						}
						if((rx[1]&0x2)!=0x2) //31/01/2020//
						{	tx[2] = 0x0; //выкл
							printf("\nadr%xh: Ntrain 3, OFF 2 ",adr);
						}/////////////////////////////////////////////

						countIsTrain=0;

					}

					if(countU<255)
					{
						 countU++; 
					}

					printf("\nNtrain\n");

			}

		}else if(adr==18)
		{
			time_t* pt = (time_t*)&rx[0];
			printf("  |%s",ctime(pt));

			//for(int i=0;i<n;i++)
			//	tx[i] = rx[i];
	    } else continue;

		((cEthernet*)p)->writeEth(&tx[0],nt);

        printf("\ntx->[%d]: ",nt);

        for(int i = 0;i<nt;i++)
       		printf(".%x", tx[i]);
		printf("\n");

		}
	}

	//////////////////////////////////////////
	for(int i=0;i<count; i++)
        {
            delete pEth[i];
        }
        delete [] pEth;
        pEth=0;count=0;

        printf("\n***EXIT!***\n\n");

	return 0;
}

void init()
{
	cFindDevice fd("/sys/class/net","eth");
	count = fd.getCountDevice();

	pEth = new cEthernet*[count]; // массив указателей на объект
	int item=0;
	while(item<count)
	{
		printf("-->>%s",fd.getNameDevice(item));
		pEth[item] = new cEthernet(fd.getNameDevice(item));
		item++;
	}

	for(int i=0;i<count;i++)
    if(pEth[i]->isSuccessInitObj()==1) // иниц. объекта успешна, сокет открыт, создан поток..
    {
		pEth[i]->setAdr(adr);
		pEth[i]->setDiagInfoForArm(bSysInfo);
	}


	if(count==2)
	{//два устройства есть - есть смысл передавать дескрииптор сокета второму
			if(pEth[1]->isSuccessInitObj()==1) { int s = pEth[1]->GetSock2(); pEth[0]->SetSock2(s); printf("\nmain: setSock2 for sock 1 is OK"); }
			if(pEth[0]->isSuccessInitObj()==1) { int s = pEth[0]->GetSock2(); pEth[1]->SetSock2(s); printf("\nmain: setSock2 for sock 2 is OK"); }
	}
}

void init2()
{
        count = nDev;
        printf("\ndevices: %d ",nDev);
        pEth = new cEthernet*[count]; // массив указателей на объект
        int item=0;
        while(item<count)
        {
                printf("\n[ %s ]",nameEth[item]);
                pEth[item] = new cEthernet(nameEth[item]);
                item++;
        }

        for(int i=0;i<count;i++)
        if(pEth[i]->isSuccessInitObj()==1) // иниц. объекта успешна, сокет открыт, создан поток..
        {
                pEth[i]->setAdr(adr);
                pEth[i]->setDiagInfoForArm(bSysInfo);
        }

		if(count==2)
		{//два устройства есть - есть смысл передавать дескрииптор сокета второму
			if(pEth[1]->isSuccessInitObj()==1) { int s = pEth[1]->GetSock2(); pEth[0]->SetSock2(s); printf("\nmain: setSock2 for sock 1 is OK"); }
			if(pEth[0]->isSuccessInitObj()==1) { int s = pEth[0]->GetSock2(); pEth[1]->SetSock2(s); printf("\nmain: setSock2 for sock 2 is OK"); }
		}
}


void out(int sig)
{
	if(sig==SIGTERM||sig == SIGINT)
    	{
                bOut=true;
        	printf("\nGoodbye (signal %d)\n",sig);
	        globalEvents::eventLan.Set((void*)NULL);
		globalEvents::eventLan.Set((void*)NULL);
		globalEvents::eventLan.Set((void*)NULL);

	}

}

