#ifndef __M9_D_TASK_TABLE_H__
#define __M9_D_TASK_TABLE_H__

#include "sim_types.h"
#include "m9_d_sim.h"

/** ������������ ���������� ����� � ������� */
#define M9_D_TASK_COUNT_MAX 100

/** ������������ ����� ����� ������ */
#define M9_D_TASK_NAME_MAX 256

/* �������� �������� ������� ������. */
typedef void (*TaskFuncMain)(void);

/* �������� ������� ������������� ������. */
typedef int32_t (*TaskFuncInit)(void);

/* �������� ������� ���������� ������. */
typedef int32_t (*TaskFuncClose)(void);


/* ������� ������ ������. */
typedef enum M9_D_TASK_FREQ_t
{
	M9_D_TASK_FREQ_80HZ,
	M9_D_TASK_FREQ_10HZ,
	M9_D_TASK_FREQ_5HZ,
	M9_D_TASK_FREQ_1HZ,
} M9_D_TASK_FREQ_t;


/** �������� ������. */
typedef struct M9_D_TaskConf_t
{
	char const name[M9_D_TASK_NAME_MAX]; /**< �������� ������ */
	TaskFuncInit init; /**< ������������� ������. */
	TaskFuncMain main; /**< �������� ���� ������ ������. */
	TaskFuncClose close; /**< �������� �� ����������� ������ ������. */

	M9_D_TASK_FREQ_t frequency; /**< ������� ������ ������. */

	/**
		����� ������ (0 - 99) ��� ������� ������.
		��� 10�� ����� ������ �������� �� ����� ��������, ��� ��� ������ ������������ �� ������ �����.
		��� 5�� ����� ������ �������� ����� ���� ����� 0 (������ �����) ��� 1 (�������� �����).
		��� 1 �� ����� ������ �������� ����� ��������� �������� �� 0 �� 9.
	 */
	uint8_t frameNumber;
	/**
		����� ��������� (0 - 7) ��� ������� ������.
		������ �������� ����� ��������� �������� �� 0 �� 7.
	 */
	uint8_t subFrameNumber;

	/**
		������� ���������� ������ ��� ������� ������.
	 */
	uint8_t isEnable;

} M9_D_TaskConf_t;


extern const M9_D_TaskConf_t M9_D_TaskConf[M9_D_TASK_COUNT_MAX];

#endif /* __M9_D_TASK_TABLE_H__ */
