/**
 * ��������� ���������� �� ��. ������������� ������ �����.
 */

#ifndef __MSM_D_TASK_H__
#define	__MSM_D_TASK_H__

#include "sim_types.h"

/* ������� ���������� ������ ������ */
extern uint8_t M9_D_SimAlive;
/* ������� ������ ������ */
extern uint32_t M9_D_SimCounter;

/* ������������� �����. */
extern void M9_D_SimInit(void);

/**
	��������� 80 ��.
	���� ��������� 10 �� ���������, �������� subFrameNumber ������ ���� ����� 0.
*/
extern void M9_D_SimStep80Hz(uint32_t procFrameNumber, uint32_t subFrameNumber);

/* ���������� ������ ���� �����. */
extern void M9_D_SimClose(void);


#endif /* __M9_D_TASK_H__ */
