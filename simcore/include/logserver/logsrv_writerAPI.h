#ifndef  _MAIN_LOG_WRITER_API_H_
#define  _MAIN_LOG_WRITER_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "logsrvProtocol.h"

        /*константы - имена секций и переменных ини-файла*/
#define    LOG_INISECTION		"LogServer"
#define    LOG_INIPORT			"LogServer_Port"
#define    LOG_INIIP          "LogServer_IP"


/*‘ункции дл€ взаимодействи€ с лог-сервером*/

	/*«аписать сообщение (с открытием и закрытием соединени€) - дл€ разовых соединений*/
extern int log_WriteRecord(const char *hostname, unsigned short MsgPriority,
                    unsigned long int Time_Seconds, unsigned long int Time_mSeconds,
                    const char *MsgSource, const char *MsgType, const char *Message);
               /*врем€ = структура?*/

   /*ќткрыть сокет (дл€ посто€нных соединений)*/
int log_Connect(char *hostname);

   /*«аписать сообщение в открытый сокет*/
extern int log_WriteConnected(unsigned short MsgPriority,
                    unsigned long int Time_Seconds, unsigned long int Time_mSeconds,
                    const char *MsgSource, const char *MsgType, const char *Message);

   /*–азорвать соединение*/
int log_CloseConnect();

#ifdef __cplusplus
}
#endif

#endif  /*_MAIN_LOG_WRITER_API_H_*/
