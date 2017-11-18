#ifndef __M9_D_TASK_TABLE_H__
#define __M9_D_TASK_TABLE_H__

#include "sim_types.h"
#include "m9_d_sim.h"

/** Максимальное количество задач в таблице */
#define M9_D_TASK_COUNT_MAX 100

/** Максимальная длина имени задачи */
#define M9_D_TASK_NAME_MAX 256

/* Прототип основных функций модели. */
typedef void (*TaskFuncMain)(void);

/* Прототип функций инициализации модели. */
typedef int32_t (*TaskFuncInit)(void);

/* Прототип функций завершения модели. */
typedef int32_t (*TaskFuncClose)(void);


/* Частота работы задачи. */
typedef enum M9_D_TASK_FREQ_t
{
	M9_D_TASK_FREQ_80HZ,
	M9_D_TASK_FREQ_10HZ,
	M9_D_TASK_FREQ_5HZ,
	M9_D_TASK_FREQ_1HZ,
} M9_D_TASK_FREQ_t;


/** Описание задачи. */
typedef struct M9_D_TaskConf_t
{
	char const name[M9_D_TASK_NAME_MAX]; /**< Название задачи */
	TaskFuncInit init; /**< Инициализация задачи. */
	TaskFuncMain main; /**< Основной такт работы задачи. */
	TaskFuncClose close; /**< Действия по прекращению работы задачи. */

	M9_D_TASK_FREQ_t frequency; /**< Частота работы задачи. */

	/**
		Номер фрейма (0 - 99) для запуска задачи.
		Для 10Гц задач данный параметр не имеет значения, так как запуск производится на каждом такте.
		Для 5Гц задач данный параметр может быть равен 0 (четный фрейм) или 1 (нечетный фрейм).
		Для 1 Гц задач данный параметр может принимать значения от 0 до 9.
	 */
	uint8_t frameNumber;
	/**
		Номер сабфрейма (0 - 7) для запуска задачи.
		Данный параметр может принимать значения от 0 до 7.
	 */
	uint8_t subFrameNumber;

	/**
		Признак разрешения работы при запуске модели.
	 */
	uint8_t isEnable;

} M9_D_TaskConf_t;


extern const M9_D_TaskConf_t M9_D_TaskConf[M9_D_TASK_COUNT_MAX];

#endif /* __M9_D_TASK_TABLE_H__ */
