#ifndef  _MAIN_LOG_WRITER_API_H_
#define  _MAIN_LOG_WRITER_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "logsrvProtocol.h"

        /*��������� - ����� ������ � ���������� ���-�����*/
#define    LOG_INISECTION		"LogServer"
#define    LOG_INIPORT			"LogServer_Port"
#define    LOG_INIIP          "LogServer_IP"


/*������� ��� �������������� � ���-��������*/

	/*�������� ��������� (� ��������� � ��������� ����������) - ��� ������� ����������*/
extern int log_WriteRecord(const char *hostname, unsigned short MsgPriority,
                    unsigned long int Time_Seconds, unsigned long int Time_mSeconds,
                    const char *MsgSource, const char *MsgType, const char *Message);
               /*����� = ���������?*/

   /*������� ����� (��� ���������� ����������)*/
int log_Connect(char *hostname);

   /*�������� ��������� � �������� �����*/
extern int log_WriteConnected(unsigned short MsgPriority,
                    unsigned long int Time_Seconds, unsigned long int Time_mSeconds,
                    const char *MsgSource, const char *MsgType, const char *Message);

   /*��������� ����������*/
int log_CloseConnect();

#ifdef __cplusplus
}
#endif

#endif  /*_MAIN_LOG_WRITER_API_H_*/
