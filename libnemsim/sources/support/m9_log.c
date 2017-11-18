#include <stdarg.h>
#include <stdio.h>

#include "logsrv_writerAPI.h"
#include "m9_log.h"

#define RIG_SERVER_NAME "inihost"


int32_t M9_LogInit(void)
{
	if (1 == log_Connect(RIG_SERVER_NAME))
		return 0;
	return -1;
}


int32_t M9_LogSendDebugMsg (char *format, ...)
{
	int n = -1;
	char message[1024] = {0};
	va_list ap;
	va_start(ap, format);
	n = vsnprintf(message, sizeof(message), format, ap);
	va_end(ap);

	if (0 <= n)
		return log_WriteConnected(10, 0, 0, "NEMSIM", "DEBUG", message);
	return -1;
}


int32_t M9_LogSendNormalMsg (char *format, ...)
{
	int n = -1;
	char message[1024] = {0};
	va_list ap;
	va_start(ap, format);
	n = vsnprintf(message, sizeof(message), format, ap);
	va_end(ap);

	if (0 <= n)
	    return log_WriteConnected(3, 0, 0, "NEMSIM", "NORMAL", message);
	return -1;
}


int32_t M9_LogSendFailMsg (char *format, ...)
{
		int n = -1;
	char message[1024] = {0};
	va_list ap;
	va_start(ap, format);
	n = vsnprintf(message, sizeof(message), format, ap);
	va_end(ap);

	if (0 <= n)
		return log_WriteConnected(1, 0, 0, "NEMSIM", "FAIL", message);
	return -1;
}


int32_t M9_LogClose(void)
{
	log_CloseConnect();
	return 0;
}
