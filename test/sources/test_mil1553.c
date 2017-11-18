#include "sim_mil1553.h"

#include <stdlib.h>


int sei7_pf;         /* номер processing frame 00..99 */
unsigned short sei7_bt[8];



int milbus_buffer_updated (int bus, int rt, int sa)
{
	return 0;
}


int milbus_buffer_updated_da(int bus, int rt, int sa)
{
	return 0;
}


unsigned short * milbus_rtsa_buffer (int bus, int rt, int sa, int tr)
{
	return NULL;
}


int milbus_buffer_last_rtbc (int bus, int rt, int sa)
{
	return 0;
}


int milbus_buffer_recv( int bus, int rt, int sa, void *VBUF, int buf_sz )
{
	return 0;
}


int milbus_buffer_transmit(int bus, int rt, int sa, unsigned  short* BUF)
{
	return 0;
}


void milbus_buffer_write (int bus, int rt, int sa)
{

}


void milbus_rt_enable(int bus, int rt, int lane_a, int lane_b)
{

}


SW_t seiSetRtSw (int bus, int rt, SW_t set1, SW_t set0)
{
	SW_t ret_val = {0};
	return ret_val;
}


int seiCheckRtMc(int bus, int rt, int mc)
{
	return 0;
}
