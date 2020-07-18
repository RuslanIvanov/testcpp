#ifndef FINDDEV
#define FINDDEV

// класс занимется поиском устройсв в заданном (системном) каталоге по заданному шаблону
// хранение имени и индекса устройства

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <unistd.h>
#include <netdb.h>
#include <dirent.h>
#include <errno.h>

class cFindDevice
{
private:
	
	char (*m_pName)[11];//указатель на имена найденных устройств
	
	int m_n; // колл-во найденнных устройсв по шаблону
	int findDevice(const char* path,const char* pNameTemplate); //ф. поиска устройств
public:
	cFindDevice(const char* path,const char* pNameTemplate); //поиск заказанных устройств в каталоге
	~cFindDevice();
	
	const char* getNameDevice(int);
	int getCountDevice();

};
#endif
