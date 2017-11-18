#ifndef __M9_BUSP_H__
#define __M9_BUSP_H__

#include "sim_types.h"

/**
	Инициализация модели. Выполняется однократно при запуске модели.
	Возвращает 0 при отсутствии ошибок инициализации.
*/
extern int32_t m9_busp_init(void);

/**
	Такт работы модели.
*/
extern void m9_busp_run(void);

/**
	Освобождение системных ресурсов, выделенных при инициализации.
*/
extern int32_t m9_busp_close(void);


#endif /* __M9_BUSP_H__ */
