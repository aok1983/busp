#ifndef __SIM_MIL1553_H__
#define __SIM_MIL1553_H__

#include "sim_types.h"

/* направление обмена */
#define SD_RCV    0    /* BC-->RT */
#define SD_TRX    1    /* RT-->BC */
#define SD_BOTH   2    /* BC<->RT */

/* номер processing frame 00..99 */
extern int sei7_pf;         

/* Широковещательное время */ 
extern unsigned short sei7_bt[8];

/** 
	Проверка обновления данных от контроллера шины на предыдущем 100 мс такте обмена.
 
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
	\returns 0 нет обновления информации, остальные значения означают наличие обновленной информации.
 */
extern int milbus_buffer_updated(int bus, int rt, int sa);


/** 
	Проверка обновления данных от контроллера шины на текущем 100 мс такте обмена.
 
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
	\returns 0 нет обновления информации, остальные значения означают наличие обновленной информации.
*/
extern int milbus_buffer_updated_da(int bus, int rt, int sa);


/** 
	Получение указателя на буфер данных для получения информации или выдачи.
 
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
	\param [in] tr входной буфер(SD_RCV)/выходной буфер (SD_TRX) 
	\return указатель на буфер размером 64 байта.
*/
extern unsigned short * milbus_rtsa_buffer (int bus, int rt, int sa, int tr);


/** 
	Проверка обращения контроллера шины к оконечному устройству на предыдущем 100мс такте обмена.
 
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
	\returns 0 не было обращения контроллера шины к оконечному устройству
		остальные значения означают что контроллер шины обращался.
*/
extern int milbus_buffer_last_rtbc (int bus, int rt, int sa);


/** 
	Получение данных с предыдущего 100мс такта обмена.
 
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
	\param [in] VBUF указатель на буфер данных
	\param [in] buf_sz размер буфера данных в байтах
	\returns количество принятых слов данных.
*/
extern int milbus_buffer_recv( int bus, int rt, int sa, void *VBUF, int buf_sz );



/**
	Выдача данных на следующем 100мс такте обмена.
 
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
	\param [in] BUF указатель на буфер данных
*/
extern int milbus_buffer_transmit(int bus, int rt, int sa, unsigned  short* BUF);


/** 
	Разрешение выдачи данных на следующем 100мс такте обмена.

	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] sa подадрес оконечного устройства
*/
extern void milbus_buffer_write (int bus, int rt, int sa);


/** 
	Управление состояние оконечного устройства.

	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] lane_a 0 выключить обмен по каналу А, 1 разрешить обмен по каналу А
	\param [in] lane_b 0 выключить обмен по каналу Б, 1 разрешить обмен по каналу Б
*/
extern void milbus_rt_enable(int bus, int rt, int lane_a, int lane_b);


/* ответное слово */
#if defined(BEND)
typedef union
{
	struct  
	{
		uint16_t rt_addr         : 5;
		uint16_t error_bit       : 1;
		uint16_t instr_bit       : 1;
		uint16_t service_bit     : 1;
		uint16_t unused          : 3;
		uint16_t bcast_rcv_bit   : 1;
		uint16_t busy_bit        : 1;
		uint16_t subsys_bit      : 1;
		uint16_t bus_ctrl_accept : 1;
		uint16_t tf_bit          : 1;
	} b;
	uint16_t  w;
} SW_t;

#else
typedef union
{
	struct  
	{
		uint16_t tf_bit          : 1;
		uint16_t bus_ctrl_accept : 1;
		uint16_t subsys_bit      : 1;
		uint16_t busy_bit        : 1;
		uint16_t bcast_rcv_bit   : 1;
		uint16_t unused          : 3;
		uint16_t service_bit     : 1;
		uint16_t instr_bit       : 1;
		uint16_t error_bit       : 1;
		uint16_t rt_addr         : 5;
	} b;
	uint16_t  w;
} SW_t;
#endif



/**
	Установка признаков в ответном слове оконечного устройства.

	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] set1 требуемые биты для выставки, остальные признаки не меняются
	\param [in] set0 требуемые биты для снятия, остальные признаки не менятся
	\return структуру с текущим состоянием признаков ответного слова
*/
extern SW_t seiSetRtSw(int bus, int rt, SW_t set1, SW_t set0);



/** 
	Проверка получения команд управления оконечным устройством (mode codes)
	\param [in] bus шина данных
	\param [in] rt адрес оконечного устройства
	\param [in] mc код команды
	\returns 0 нет команды, остальные значения означают получение данной команды.
*/
extern int seiCheckRtMc(int bus, int rt, int mc);

#endif

