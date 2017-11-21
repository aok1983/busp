#ifndef __SIM_MIL1553_H__
#define __SIM_MIL1553_H__

#include "sim_types.h"

/* ����������� ������ */
#define SD_RCV    0    /* BC-->RT */
#define SD_TRX    1    /* RT-->BC */
#define SD_BOTH   2    /* BC<->RT */

/* ����� processing frame 00..99 */
extern int sei7_pf;         

/* ����������������� ����� */ 
extern unsigned short sei7_bt[8];

/** 
	�������� ���������� ������ �� ����������� ���� �� ���������� 100 �� ����� ������.
 
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
	\returns 0 ��� ���������� ����������, ��������� �������� �������� ������� ����������� ����������.
 */
extern int milbus_buffer_updated(int bus, int rt, int sa);


/** 
	�������� ���������� ������ �� ����������� ���� �� ������� 100 �� ����� ������.
 
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
	\returns 0 ��� ���������� ����������, ��������� �������� �������� ������� ����������� ����������.
*/
extern int milbus_buffer_updated_da(int bus, int rt, int sa);


/** 
	��������� ��������� �� ����� ������ ��� ��������� ���������� ��� ������.
 
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
	\param [in] tr ������� �����(SD_RCV)/�������� ����� (SD_TRX) 
	\return ��������� �� ����� �������� 64 �����.
*/
extern unsigned short * milbus_rtsa_buffer (int bus, int rt, int sa, int tr);


/** 
	�������� ��������� ����������� ���� � ���������� ���������� �� ���������� 100�� ����� ������.
 
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
	\returns 0 �� ���� ��������� ����������� ���� � ���������� ����������
		��������� �������� �������� ��� ���������� ���� ���������.
*/
extern int milbus_buffer_last_rtbc (int bus, int rt, int sa);


/** 
	��������� ������ � ����������� 100�� ����� ������.
 
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
	\param [in] VBUF ��������� �� ����� ������
	\param [in] buf_sz ������ ������ ������ � ������
	\returns ���������� �������� ���� ������.
*/
extern int milbus_buffer_recv( int bus, int rt, int sa, void *VBUF, int buf_sz );



/**
	������ ������ �� ��������� 100�� ����� ������.
 
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
	\param [in] BUF ��������� �� ����� ������
*/
extern int milbus_buffer_transmit(int bus, int rt, int sa, unsigned  short* BUF);


/** 
	���������� ������ ������ �� ��������� 100�� ����� ������.

	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] sa �������� ���������� ����������
*/
extern void milbus_buffer_write (int bus, int rt, int sa);


/** 
	���������� ��������� ���������� ����������.

	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] lane_a 0 ��������� ����� �� ������ �, 1 ��������� ����� �� ������ �
	\param [in] lane_b 0 ��������� ����� �� ������ �, 1 ��������� ����� �� ������ �
*/
extern void milbus_rt_enable(int bus, int rt, int lane_a, int lane_b);


/* �������� ����� */
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
	��������� ��������� � �������� ����� ���������� ����������.

	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] set1 ��������� ���� ��� ��������, ��������� �������� �� ��������
	\param [in] set0 ��������� ���� ��� ������, ��������� �������� �� �������
	\return ��������� � ������� ���������� ��������� ��������� �����
*/
extern SW_t seiSetRtSw(int bus, int rt, SW_t set1, SW_t set0);



/** 
	�������� ��������� ������ ���������� ��������� ����������� (mode codes)
	\param [in] bus ���� ������
	\param [in] rt ����� ���������� ����������
	\param [in] mc ��� �������
	\returns 0 ��� �������, ��������� �������� �������� ��������� ������ �������.
*/
extern int seiCheckRtMc(int bus, int rt, int mc);

#endif

