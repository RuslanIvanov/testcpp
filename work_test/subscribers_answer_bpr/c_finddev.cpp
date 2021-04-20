
#include "c_finddev.h"

cFindDevice::cFindDevice(const char* path,const char* pNameTemplate)
{
	m_pName=0;
	m_n=0;

	m_n=findDevice(path,pNameTemplate);
	if(m_n>0)
	{
		int i = 0;
		m_pName = new char[m_n][11];
        	for(;i<m_n;i++)
        	{
        	    char buf[10]= {0};
        	    //sprintf(buf,"eth%d\x00",i); //?
        	    sprintf(buf,"%s%d\x00",pNameTemplate,i);
		    strcpy(m_pName[i],buf);
        	    //printf("\nfind->%s;",buf);
		
        	}
    	}else {printf("\nError device %s!\n",pNameTemplate);}
}

cFindDevice::~cFindDevice()
{
	delete [] m_pName;
	m_pName=0;
	printf("\n~cFindDevice");
}

int cFindDevice::findDevice(const char* path,const char* pNameTemplate)
{/*
    функция ищет в указанном  каталоге path (/sys/class/net)
    имена определенных ОС устройств  
    по шаблону pNameTemplate ("eth") 
    Возвращает 0 в случае неудачи или
    если устройства не найдены и n=кол_ву найденных усторйств
 */
    int n = 0;
    DIR *pdir;
    struct dirent *ent;
    pdir = opendir(path);
    
    if(pdir==NULL)    
    {
	printf("\nopendir: %s: %s\n",path,strerror(errno));
	return 0;
    }

    int lenStr = strlen(pNameTemplate);
    
    while((ent=readdir(pdir))!=false)
    {
	if(strncmp(ent->d_name,pNameTemplate,lenStr)==0)
	{
    	    //printf("\n%s",ent->d_name);
    	    n++;
    	}
    }
    closedir(pdir);
    return n;
}

int cFindDevice::getCountDevice()
{
	return m_n;
}

const char* cFindDevice::getNameDevice(int id)
{
	return m_pName[id];
}

