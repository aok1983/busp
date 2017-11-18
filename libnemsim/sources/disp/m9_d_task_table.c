#include <stdlib.h>

#include "m9_d_task_table.h"

#include "m9_suba.h"
#include "m9_busp.h"


#define INIT_ITEM(name, freq, pfn, sbfn, ena)\
	{#name, m9_##name##_init, m9_##name##_run, m9_##name##_close, M9_D_TASK_FREQ_##freq##HZ, pfn, sbfn, ena}

#define END_OF_TABLE { "", NULL, NULL, NULL, M9_D_TASK_FREQ_10HZ, 0, 0, 0 }


/* список задач модели */
const M9_D_TaskConf_t M9_D_TaskConf[M9_D_TASK_COUNT_MAX] =
{
    /* name frequency pfn sbfn isEnable */
	INIT_ITEM(suba, 10, 0, 0, 1),
	INIT_ITEM(busp, 10, 0, 0, 1),
	END_OF_TABLE
};

