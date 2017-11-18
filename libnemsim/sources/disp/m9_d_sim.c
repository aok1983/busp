/**
 * ��������� ���������� �� ���.
 */

#include <stdlib.h>
#include <string.h>
#include "sim_utils.h"
#include "m9_d_sim.h"
#include "m9_d_task_table.h"
#include "m9_log.h"

uint8_t M9_D_SimAlive = 0;
uint32_t M9_D_SimCounter = 0;

char M9_D_TaskName[M9_D_TASK_NAME_MAX] = {0};
uint8_t M9_D_TaskDisableCmd = 0;
uint8_t M9_D_TaskEnableCmd = 0;


/* ������� ���������� ����� */
static uint8_t _taskCount = 0;


/* ��������� ������ ������, ������� ����� �������� � �������� ������. */
typedef struct M9_D_Task_t
{
	char const *name;
	/* ������� ���������� ������. */
	uint8_t isEnable;
	/* ������� ������� ������ */
	uint32_t counter;
	/* ����������������� ������ ������, ������������. */
	double currTime;
	/* ������������ ����� ������ ������, ������������ */
	double maxTime;
} M9_D_Task_t;

M9_D_Task_t M9_D_Task[M9_D_TASK_COUNT_MAX];

typedef struct
{
	/* ������������ ������ ���� ����� �� ������� 100 �� �����, ������������ */
	double currAllTasks100ms;
	/* ������������ ������������ ������ ���� ����� �� ������� 100 �� �����, ������������ */
	double maxAllTasks100ms;

	/* ������������ ������ ���� ����� �� ������� 12,5 �� ���������, ������������ */
	double currAllTasks12ms;
	/* ������������ ������������ ������ ���� ����� �� ������� 12,5 �� ���������, ������������ */
	double maxAllTasks12ms;

	/* ������������ ������ ���� ����� �� ������� 12,5 �� ���������, ������������ */
	double pfCurrAllTasks[100][8];
	/* ������������ ������������ ������ ���� ����� �� ������� 12,5 �� ���������, ������������ */
	double pfMaxAllTasks[100][8];

} M9_D_Timing_t;

M9_D_Timing_t M9_D_Timing;


static void _startTaskMain(uint32_t id);
static void _checkSubFrame(uint32_t id, uint32_t subFrameNumber);
static void _disableTask(char const *name);
static void _enableTask(char const *name);


/* ������������� ���� �����. */
void M9_D_SimInit(void)
{
	uint32_t i = 0;

	memset(M9_D_Task, 0, sizeof(M9_D_Task));
	memset(&M9_D_Timing, 0, sizeof(M9_D_Timing));
	_taskCount = 0;

	for (i = 0; i < M9_D_TASK_COUNT_MAX; ++i)
	{
		if (NULL != M9_D_TaskConf[i].name)
		{
			M9_D_Task[i].name = M9_D_TaskConf[i].name;
			if (M9_D_TaskConf[i].isEnable && (NULL != M9_D_TaskConf[i].init))
				M9_D_TaskConf[i].init();
			M9_D_Task[i].isEnable = M9_D_TaskConf[i].isEnable;
			++_taskCount;
		}
	}
	M9_D_SimAlive = 1;
}


/* ���������� ������ ���� �����. */
void M9_D_SimClose(void)
{
	uint32_t i;
	for (i = 0; i < _taskCount; ++i)
	{
		if (NULL != M9_D_TaskConf[i].close)
			M9_D_TaskConf[i].close();
		M9_D_Task[i].isEnable = 0;
	}
	M9_D_SimAlive = 0;
}


void M9_D_SimStep80Hz(uint32_t pf, uint32_t sbf)
{
	uint32_t i;

	++M9_D_SimCounter;

	if (0 == M9_D_SimAlive)
		return;

	if (0 == sbf)
		M9_D_Timing.currAllTasks100ms = 0;

	M9_D_Timing.currAllTasks12ms = 0;
	M9_D_Timing.pfCurrAllTasks[pf][sbf] = 0;


	/* �������� ��� ������� ����� � ������� ������ ��������� */
	for (i = 0; i < _taskCount; ++i)
	{
		/* �������� ����� ������ ������� ������ */
		M9_D_Task[i].currTime = 0;
		/* ���� ���� ��� ��������� */
		if (M9_D_Task[i].isEnable && (NULL != M9_D_TaskConf[i].main))
		{
			/* ������� ����������� ������ */
			if (M9_D_TASK_FREQ_80HZ == M9_D_TaskConf[i].frequency)
			{
				_startTaskMain(i);
			}
			else if (M9_D_TASK_FREQ_10HZ == M9_D_TaskConf[i].frequency)
			{
				_checkSubFrame(i, sbf);
			}
			else if (M9_D_TASK_FREQ_5HZ == M9_D_TaskConf[i].frequency)
			{
				/* ���������� ��������/���������� ������ */
				uint32_t const evenOdd = pf % 2;
				/* ���� �� ��� ����  */
				if (evenOdd == M9_D_TaskConf[i].frameNumber)
					_checkSubFrame(i, sbf);
			}
			else if (M9_D_TASK_FREQ_1HZ == M9_D_TaskConf[i].frequency)
			{
				/* ���������� ��������� ������ �� 1��� ��������� */
				uint32_t const t = pf % 10;
				/* ���� �� ��� ����  */
				if (t == M9_D_TaskConf[i].frameNumber)
					_checkSubFrame(i, sbf);
			}
			else
			{
				/* ��������� ��������� �� ������. */
			}
		}
		M9_D_Timing.currAllTasks100ms += M9_D_Task[i].currTime;
		M9_D_Timing.currAllTasks12ms += M9_D_Task[i].currTime;
		M9_D_Timing.pfCurrAllTasks[pf][sbf] += M9_D_Task[i].currTime;
	}
	if (M9_D_Timing.currAllTasks100ms > M9_D_Timing.maxAllTasks100ms)
		M9_D_Timing.maxAllTasks100ms = M9_D_Timing.currAllTasks100ms;
	if (M9_D_Timing.currAllTasks12ms > M9_D_Timing.maxAllTasks12ms)
		M9_D_Timing.maxAllTasks12ms = M9_D_Timing.currAllTasks12ms;
	if (M9_D_Timing.pfCurrAllTasks[pf][sbf] > M9_D_Timing.pfMaxAllTasks[pf][sbf])
		M9_D_Timing.pfMaxAllTasks[pf][sbf] = M9_D_Timing.pfCurrAllTasks[pf][sbf];

	if (0 != M9_D_TaskDisableCmd && 0 != M9_D_TaskName[0])
	{
		M9_D_TaskDisableCmd = 0;
		_disableTask(M9_D_TaskName);
	}

	if (0 != M9_D_TaskEnableCmd && 0 != M9_D_TaskName[0])
	{
		M9_D_TaskEnableCmd = 0;
		_enableTask(M9_D_TaskName);
	}
}

static void _checkSubFrame(uint32_t id, uint32_t subFrameNumber)
{
	/* ���� ���� ���������� ���������� ������ */
	if (M9_D_Task[id].isEnable)
	{
		/* ���� ������� ����� ��������� ��������� � �������� */
		if (M9_D_TaskConf[id].subFrameNumber == subFrameNumber)
		{
			/* ��������� ������ */
			_startTaskMain(id);
		}
	}
}


static void _startTaskMain(uint32_t id)
{
	uint64_t start, finish;
	++M9_D_Task[id].counter;
	start = osUsClock();
	/* ��������� ������ */
	M9_D_TaskConf[id].main();
	finish = osUsClock();
	M9_D_Task[id].currTime = (double)((finish - start)) / 1000.0;
	if (M9_D_Task[id].currTime > M9_D_Task[id].maxTime)
		M9_D_Task[id].maxTime = M9_D_Task[id].currTime;
}


static void _disableTask(char const *name)
{
	int32_t i;
	/* ����� �� ������� ������� ����� */
	for (i = 0; i < _taskCount; ++i)
	{
		/* ���� ����� ��������� */
		if (0 == strncmp(name, M9_D_Task[i].name, M9_D_TASK_NAME_MAX))
		{
			M9_D_Task[i].isEnable = 0;
			M9_LogSendNormalMsg("������ %s ���������", name);
			return;
		}
	}
}


static void _enableTask(char const *name)
{
	int32_t i;
	/* ����� �� ������� ������� ����� */
	for (i = 0; i < _taskCount; ++i)
	{
		/* ���� ����� ��������� */
		if (0 == strncmp(name, M9_D_Task[i].name, M9_D_TASK_NAME_MAX))
		{
			M9_D_Task[i].isEnable = 1;
			M9_LogSendNormalMsg("������ %s ��������", name);
			return;
		}
	}
}
