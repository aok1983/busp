#ifndef __M9_BUSP_H__
#define __M9_BUSP_H__

#include "sim_types.h"

/**
	������������� ������. ����������� ���������� ��� ������� ������.
	���������� 0 ��� ���������� ������ �������������.
*/
extern int32_t m9_busp_init(void);

/**
	���� ������ ������.
*/
extern void m9_busp_run(void);

/**
	������������ ��������� ��������, ���������� ��� �������������.
*/
extern int32_t m9_busp_close(void);


#endif /* __M9_BUSP_H__ */
