#ifndef  _TMSPY_LL_H_
#define  _TMSPY_LL_H_


/*Платформенно-зависимые подключения заголовоочных файлов*/
#if defined(SOLARIS)
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <sys/filio.h>
#include <sys/socket.h>
#include <fcntl.h>
#endif
#if defined(LINUX)
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/tcp.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#define INVALID_SOCKET -1
#endif
#if defined(VXWORKS)
#include <sockLib.h>
#include <netinet/in.h>
#include <hostLib.h>
#include <netinet/tcp.h>
#include <ioLib.h>
#define INVALID_SOCKET -1
typedef int socklen_t;
#endif
#if defined(QNX)
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>

#define INVALID_SOCKET -1
#endif

#if defined(__QNXNTO__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <string.h>
#include <arpa/inet.h>
#include <ioctl.h>
#define INVALID_SOCKET -1
#endif

#if defined(_WIN32)
#include <winsock.h>
#include <windows.h>
typedef int socklen_t;
#else
#define SOCKET int
#define SOCKET_ERROR -1
#define SD_BOTH 2
#define closesocket close
#endif

#include "STimer.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(VXWORKS)
#pragma pack(1)
#else
#pragma pack(push,1)
#endif 
/*структура сообщений для обмена с источником*/
#define CTM_MaxDataLength 600

#define CTM_MsgEmpty		0
#define CTM_MsgAck			1
#define CTM_MsgKeepAlive	2
#define CTM_MsgConnect		3
#define CTM_MsgCommand		4
#define CTM_MsgTMI			5
#define CTM_MsgCommandSize	6 /* dataLen==4, data - unsigned int */

typedef struct 
{
	unsigned int msgId;	/*Код сообщения*/
	unsigned int msgCounter;/*Номер сообщения (сквозная нумерация сообщений с данными)*/
	unsigned int dataLen;	/*Длина данных*/
	unsigned char data[CTM_MaxDataLength];
}CTMDatagram;
/*\структура сообщений для обмена с источником*/

#if defined(VXWORKS)
#pragma pack()
#else
#pragma pack(pop)
#endif 

#define TMLL_BUFSIZE 32/*степень двойки!*/
#define TMLL_COUNTER0 0/*Начальное значение для нумерации пакетов (поле CTMDatagram::msgCounter)*/

typedef struct
{
		CTMDatagram dgram;
		CSTimer_t t;
}CTMDatagramRec;

typedef struct
{
	/* порт, к которому при инициализации должна привязываться серверная сторона */
    unsigned short serverPort;
	/* Сокет, через него собственно и работаем */
	SOCKET sock;
	/* Адрес другой стороны соединения */
	struct sockaddr_in destAddr; 

	/* 
		!=0 если соединение установлено(здесь и далее: соединение не в смысле TCP,
		но данного протокола)
	*/
	int connectedFlag;

	/*Счетчики для телеметрии*/
	
	/*последняя ошибка sendto*/
	int sendErrno;			
	/*количество ошибок при передаче*/
	int sendError;			
	/*количество ошибок при приеме*/
	int recvError; 		

	/*количество вызовов TMLLSendData*/
	int sendNum;			
	/*количество подтвержденных пакетов */
	int ackNum;			
	/*количество пакетов, потеряных при передаче(по отсутствию подтверждения)*/
	/*должно выполняться sendNum-ackNum==sendLossNum*/
	int sendLossNum;		
	
	/*количество разрывов связи*/
	int disconnectNum;		
	
	/* Счетчики для телеметрии */

	/*количество принятых пакетов*/
	int receivedNum;		
	/*количество принятых и обработанных пакетов*/
	int processedNum;		
	/* количество пакетов, потеряных при приеме(по нарушению последовательности счетчика)*/
	int receiveLossNum;	
	

	/* заготовки исходящих пакетов */
	CTMDatagram keepAliveDgram;
	CTMDatagram ackDgram;
	CTMDatagram receiveDgram;
	
	/* Последние отосланные пакеты(типа кольцевого буфера) */
	CTMDatagramRec lastSended[TMLL_BUFSIZE]; 
	/* номер для очередного отправляемого пакета */
	unsigned int nextCounter;

	/* Последние принятые пакеты(типа кольцевого буфера) */
	CTMDatagramRec lastReceived[TMLL_BUFSIZE]; 
	/* номер последнего (максимального по номеру) принятого пакета */
	unsigned int receivedCounter;
	/* номер последнего обработанного пакета */
	unsigned int processedCounter;

	/* время последнего приема */
	CSTimer_t recieveT;
	/* время последней отправки */
	CSTimer_t sendT;
	/* измерение периода между вызовами TMLL5Hz */
	CSTimer_t t5Hz;
} CTMLL;

extern void TMLL(CTMLL *This);
extern void TMLLNewConnection(CTMLL *This);
extern void TMLL5Hz(CTMLL *This);
/* голая отправка */
extern char TMLLSendLL(CTMLL *This, CTMDatagram *dgram); 
/* отправка с буферизацией для повторных попыток */
extern char TMLLSend(CTMLL *This, unsigned char msgId, unsigned int dataLen, 
					 unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif  /*_TMSPY_LL_H_*/
