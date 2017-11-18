#ifndef __MAIN_LOG_SRV_PROTOCOL__
#define __MAIN_LOG_SRV_PROTOCOL__

#include <stdint.h>

/*�������� �������������� ����� LogServer � LogClient*/

#ifndef USA

/*���������, ���� ��������*/

#define     LOG_RQ_SETFILENAME		0x3001		/*��������� ����� ��� �����(��� - � ���������� message)*/

#define     LOG_RQ_CLOSEFILE		0x3002		/*�������� ��� �����*/

#define		LOG_RQ_READNEW			0x3003		/*������ ������ �����*/

#define		LOG_RQ_WRITERECORD		0x3004		/*�������� ���������*/

#define		LOG_RQ_SETFILTER		0x3005		/*��������� ������� ����������*/


#define     LOG_RP_RECORD              0x3011
/*� ��������� ����� ����������� ����� ��������� ������*/

#define     LOG_RP_ERROR             0x3012
/*� ��������� ������ �� ���������*/

#define     LOG_RP_FILENAME          0x3013
/*� ��������� ����� ����������� ��� �����*/

#define		LOG_MESSAGE_SIZE		100			/*������ ���������*/

#else /*USA*/

/*���������, ���� ��������*/

#define     LOG_RQ_SETFILENAME		0x7887		/*��������� ����� ��� �����(��� - � ���������� message)*/

#define     LOG_RQ_CLOSEFILE		0x7856		/*�������� ��� �����*/

#define		LOG_RQ_READNEW			0x7858		/*������ ������ �����*/

#define		LOG_RQ_WRITERECORD		0x7867		/*�������� ���������*/

#define		LOG_RQ_SETFILTER		0x7833		/*��������� ������� ����������*/


#define     LOG_RP_RECORD              0x7844
/*� ��������� ����� ����������� ����� ��������� ������*/

#define     LOG_RP_ERROR             0x722
/*� ��������� ������ �� ���������*/

#define     LOG_RP_FILENAME          0x7818
/*� ��������� ����� ����������� ��� �����*/

#define		LOG_MESSAGE_SIZE		140			/*������ ���������*/


#endif /*USA*/


       /*���� ������� ��� ������� (������������ ����� �������� �� ��������� �������)*/
#define     LOG_CLIENT_READER    1   /*������ ����� ��������� � ���*/
#define     LOG_CLIENT_WRITER    2   /*������ ������ ��������� �� ����*/
#define     LOG_CLIENT_DISPOSABLE 3  /*������ ������ ���� ������ � �����������*/

struct TLOG_UNSEG_TIME_TYPE
{
	uint32_t Coarse;  /*����� � �������� �� 00:00 1 ��� 1980*/
	uint32_t Fine;    /*���������� �����������*/
};


/* ��������� ��������� ������� ������->������ */
struct TLOG_RQ              
{
	uint16_t RQId;                           /* ��� ������� */
	uint16_t MsgPriority;	                 /* ��������� ��������� */
	struct TLOG_UNSEG_TIME_TYPE TargetTime;	 /* �������� ����� */
	char MsgSource[6];	                     /* �������� ���������*/
	char MsgType[6];	                     /* ��� ��������� */
	char Message[LOG_MESSAGE_SIZE + 1];		 /* ��������� */
};


/* ��������� ��������� ������ �� ������� � ������� */
struct TLOG_RP              
{
	uint16_t RPId;                          /* ��� ������ */
	uint16_t MsgPriority;                   /* �������� ��������� */
	uint32_t MsgTime;                       /* ��������� ����� */
	struct TLOG_UNSEG_TIME_TYPE TargetTime; /* �������� ����� */
	char MsgSource[6];                      /* �������� ��������� */
	char MsgType[6];                        /* ��� ��������� */
	char Message[LOG_MESSAGE_SIZE + 4];     /* ��������� */
	uint32_t SourceIP;                      /* IP - ����� ��������� ��������� */
};


struct TLOG_Record
{
	uint32_t MsgId;                         /* ���������� ����� ��������� */
	uint32_t MsgTime;                       /* ��������� ����� */
	struct TLOG_UNSEG_TIME_TYPE TargetTime; /* �������� ����� */
	uint16_t MsgPriority;                   /* �������� ��������� */
	char MsgSource[8];                      /* �������� ��������� */
	char MsgType[8];                        /* ��� ��������� */
	char Message[LOG_MESSAGE_SIZE + 4];     /* ��������� */
	uint32_t SourceIP;                      /* IP - ����� ��������� ��������� */
};


struct TLOG_FilterRecord
{
	uint16_t MsgPriority; /* �������� ��������� */
	char MsgSource[6];    /* �������� ��������� */
	char MsgType[6];      /* ��� ��������� */
};

#endif /* __MAIN_LOG_SRV_PROTOCOL__ */
