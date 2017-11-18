#ifndef __TEST_SUBA_H__
#define __TEST_SUBA_H__

/** Формирование команды СУБК */
extern int test_com_set(int id);
/** Сброс команды СУБК */
extern int test_com_clear(int id);
/** Получение значения дискретного телеметрического параметра */
extern int test_dpar(int id);
/** Получение значения аналогового телеметрического параметра */
extern double test_apar(int id);


#endif /* __TEST_SUBA_H__ */
