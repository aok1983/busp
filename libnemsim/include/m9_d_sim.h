/**
 * Диспетчер модельного ПО СМ. Инициализация таблиц задач.
 */

#ifndef __MSM_D_TASK_H__
#define	__MSM_D_TASK_H__

#include "sim_types.h"

/* Признак разрешения работы модели */
extern uint8_t M9_D_SimAlive;
/* Счетчик работы модели */
extern uint32_t M9_D_SimCounter;

/* Инициализация задач. */
extern void M9_D_SimInit(void);

/**
	Диспетчер 80 Гц.
	Если требуется 10 Гц диспетчер, параметр subFrameNumber должен быть равен 0.
*/
extern void M9_D_SimStep80Hz(uint32_t procFrameNumber, uint32_t subFrameNumber);

/* Завершение работы всех задач. */
extern void M9_D_SimClose(void);


#endif /* __M9_D_TASK_H__ */
