#ifndef __M9_LOG_H__
#define __M9_LOG_H__

#include "sim_types.h"


/** ������������� ���������� � LogServer */
extern int32_t M9_LogInit(void);

/**
	������� ����������� ��������� � LogServer.
	������������ ����� ��������� 1024 �������.
 */
extern int32_t M9_LogSendDebugMsg(char *format, ...);

/**
	������� ����������� ��������� � LogServer.
	������������ ����� ��������� 1024 �������.
*/
extern int32_t M9_LogSendNormalMsg(char *format, ...);

/**
	������� ��������� �� ������ � LogServer.
	������������ ����� ��������� 1024 �������.
*/
extern int32_t M9_LogSendFailMsg(char *format, ...);

/**
	�������� ���������� � LogServer.
*/
extern int32_t M9_LogClose(void);


#endif /* __M9_LOG_H__ */
