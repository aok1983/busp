#ifndef  _TMSPY_LL_H_
#define  _TMSPY_LL_H_


/*������������-��������� ����������� ������������� ������*/
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
/*��������� ��������� ��� ������ � ����������*/
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
	unsigned int msgId;	/*��� ���������*/
	unsigned int msgCounter;/*����� ��������� (�������� ��������� ��������� � �������)*/
	unsigned int dataLen;	/*����� ������*/
	unsigned char data[CTM_MaxDataLength];
}CTMDatagram;
/*\��������� ��������� ��� ������ � ����������*/

#if defined(VXWORKS)
#pragma pack()
#else
#pragma pack(pop)
#endif 

#define TMLL_BUFSIZE 32/*������� ������!*/
#define TMLL_COUNTER0 0/*��������� �������� ��� ��������� ������� (���� CTMDatagram::msgCounter)*/

typedef struct
{
		CTMDatagram dgram;
		CSTimer_t t;
}CTMDatagramRec;

typedef struct
{
	/* ����, � �������� ��� ������������� ������ ������������� ��������� ������� */
    unsigned short serverPort;
	/* �����, ����� ���� ���������� � �������� */
	SOCKET sock;
	/* ����� ������ ������� ���������� */
	struct sockaddr_in destAddr; 

	/* 
		!=0 ���� ���������� �����������(����� � �����: ���������� �� � ������ TCP,
		�� ������� ���������)
	*/
	int connectedFlag;

	/*�������� ��� ����������*/
	
	/*��������� ������ sendto*/
	int sendErrno;			
	/*���������� ������ ��� ��������*/
	int sendError;			
	/*���������� ������ ��� ������*/
	int recvError; 		

	/*���������� ������� TMLLSendData*/
	int sendNum;			
	/*���������� �������������� ������� */
	int ackNum;			
	/*���������� �������, ��������� ��� ��������(�� ���������� �������������)*/
	/*������ ����������� sendNum-ackNum==sendLossNum*/
	int sendLossNum;		
	
	/*���������� �������� �����*/
	int disconnectNum;		
	
	/* �������� ��� ���������� */

	/*���������� �������� �������*/
	int receivedNum;		
	/*���������� �������� � ������������ �������*/
	int processedNum;		
	/* ���������� �������, ��������� ��� ������(�� ��������� ������������������ ��������)*/
	int receiveLossNum;	
	

	/* ��������� ��������� ������� */
	CTMDatagram keepAliveDgram;
	CTMDatagram ackDgram;
	CTMDatagram receiveDgram;
	
	/* ��������� ���������� ������(���� ���������� ������) */
	CTMDatagramRec lastSended[TMLL_BUFSIZE]; 
	/* ����� ��� ���������� ������������� ������ */
	unsigned int nextCounter;

	/* ��������� �������� ������(���� ���������� ������) */
	CTMDatagramRec lastReceived[TMLL_BUFSIZE]; 
	/* ����� ���������� (������������� �� ������) ��������� ������ */
	unsigned int receivedCounter;
	/* ����� ���������� ������������� ������ */
	unsigned int processedCounter;

	/* ����� ���������� ������ */
	CSTimer_t recieveT;
	/* ����� ��������� �������� */
	CSTimer_t sendT;
	/* ��������� ������� ����� �������� TMLL5Hz */
	CSTimer_t t5Hz;
} CTMLL;

extern void TMLL(CTMLL *This);
extern void TMLLNewConnection(CTMLL *This);
extern void TMLL5Hz(CTMLL *This);
/* ����� �������� */
extern char TMLLSendLL(CTMLL *This, CTMDatagram *dgram); 
/* �������� � ������������ ��� ��������� ������� */
extern char TMLLSend(CTMLL *This, unsigned char msgId, unsigned int dataLen, 
					 unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif  /*_TMSPY_LL_H_*/
