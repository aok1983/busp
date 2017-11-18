#ifndef __MAIN_LOG_SRV_PROTOCOL__
#define __MAIN_LOG_SRV_PROTOCOL__

#include <stdint.h>

/*Протокол взаимодействия между LogServer и LogClient*/

#ifndef USA

/*Константы, коды запросов*/

#define     LOG_RQ_SETFILENAME		0x3001		/*Установка имени лог файла(имя - в переменной message)*/

#define     LOG_RQ_CLOSEFILE		0x3002		/*Закрытие лог файла*/

#define		LOG_RQ_READNEW			0x3003		/*Читать только новые*/

#define		LOG_RQ_WRITERECORD		0x3004		/*Записать сообщение*/

#define		LOG_RQ_SETFILTER		0x3005		/*Установка условий фильтрации*/


#define     LOG_RP_RECORD              0x3011
/*к сообщению сзади добавляется текст выбранной записи*/

#define     LOG_RP_ERROR             0x3012
/*К сообщению ничего не приложено*/

#define     LOG_RP_FILENAME          0x3013
/*к сообщению сзади добавляется имя файла*/

#define		LOG_MESSAGE_SIZE		100			/*Размер сообщения*/

#else /*USA*/

/*Константы, коды запросов*/

#define     LOG_RQ_SETFILENAME		0x7887		/*Установка имени лог файла(имя - в переменной message)*/

#define     LOG_RQ_CLOSEFILE		0x7856		/*Закрытие лог файла*/

#define		LOG_RQ_READNEW			0x7858		/*Читать только новые*/

#define		LOG_RQ_WRITERECORD		0x7867		/*Записать сообщение*/

#define		LOG_RQ_SETFILTER		0x7833		/*Установка условий фильтрации*/


#define     LOG_RP_RECORD              0x7844
/*к сообщению сзади добавляется текст выбранной записи*/

#define     LOG_RP_ERROR             0x722
/*К сообщению ничего не приложено*/

#define     LOG_RP_FILENAME          0x7818
/*к сообщению сзади добавляется имя файла*/

#define		LOG_MESSAGE_SIZE		140			/*Размер сообщения*/


#endif /*USA*/


       /*Типы клиента лог сервера (определяются самим сервером по поведению клиента)*/
#define     LOG_CLIENT_READER    1   /*Клиент пишет сообщения в лог*/
#define     LOG_CLIENT_WRITER    2   /*Клиент читает сообщения из лога*/
#define     LOG_CLIENT_DISPOSABLE 3  /*Клиент выдает один запрос и отключается*/

struct TLOG_UNSEG_TIME_TYPE
{
	uint32_t Coarse;  /*Время в секундах от 00:00 1 Янв 1980*/
	uint32_t Fine;    /*Количество миллисекунд*/
};


/* Структура сообщения запроса Клиент->Сервер */
struct TLOG_RQ              
{
	uint16_t RQId;                           /* Код запроса */
	uint16_t MsgPriority;	                 /* Приоритет сообщения */
	struct TLOG_UNSEG_TIME_TYPE TargetTime;	 /* Бортовое время */
	char MsgSource[6];	                     /* Источник сообщения*/
	char MsgType[6];	                     /* Тип сообщения */
	char Message[LOG_MESSAGE_SIZE + 1];		 /* Сообщение */
};


/* Структура сообщения ответа от сервера к клиенту */
struct TLOG_RP              
{
	uint16_t RPId;                          /* Код ответа */
	uint16_t MsgPriority;                   /* Приортет сообщения */
	uint32_t MsgTime;                       /* Стендовое время */
	struct TLOG_UNSEG_TIME_TYPE TargetTime; /* Бортовое время */
	char MsgSource[6];                      /* Источник сообщения */
	char MsgType[6];                        /* Тип сообщения */
	char Message[LOG_MESSAGE_SIZE + 4];     /* Сообщение */
	uint32_t SourceIP;                      /* IP - адрес источника сообщения */
};


struct TLOG_Record
{
	uint32_t MsgId;                         /* Порядковый номер сообщения */
	uint32_t MsgTime;                       /* Стендовое время */
	struct TLOG_UNSEG_TIME_TYPE TargetTime; /* Бортовое время */
	uint16_t MsgPriority;                   /* Приортет сообщения */
	char MsgSource[8];                      /* Источник сообщения */
	char MsgType[8];                        /* Тип сообщения */
	char Message[LOG_MESSAGE_SIZE + 4];     /* Сообщение */
	uint32_t SourceIP;                      /* IP - адрес источника сообщения */
};


struct TLOG_FilterRecord
{
	uint16_t MsgPriority; /* Приортет сообщения */
	char MsgSource[6];    /* Источник сообщения */
	char MsgType[6];      /* Тип сообщения */
};

#endif /* __MAIN_LOG_SRV_PROTOCOL__ */
