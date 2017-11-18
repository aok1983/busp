#ifndef __M9_LOG_H__
#define __M9_LOG_H__

#include "sim_types.h"


/** Инициализация соединения с LogServer */
extern int32_t M9_LogInit(void);

/**
	Посылка отладочного сообщения в LogServer.
	Максимальная длина сообщения 1024 символа.
 */
extern int32_t M9_LogSendDebugMsg(char *format, ...);

/**
	Посылка номрального сообщения в LogServer.
	Максимальная длина сообщения 1024 символа.
*/
extern int32_t M9_LogSendNormalMsg(char *format, ...);

/**
	Посылка сообщения об ошибке в LogServer.
	Максимальная длина сообщения 1024 символа.
*/
extern int32_t M9_LogSendFailMsg(char *format, ...);

/**
	Закрытие соединения с LogServer.
*/
extern int32_t M9_LogClose(void);


#endif /* __M9_LOG_H__ */
