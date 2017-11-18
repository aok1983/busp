
#ifndef AFX_STIMER_H__1423fdd4_3b9d_4283_8d66_b8dd7562bbd9__INCLUDED_
#define AFX_STIMER_H__1423fdd4_3b9d_4283_8d66_b8dd7562bbd9__INCLUDED_



#if defined(__cplusplus)
extern "C"{
#endif

#if defined(_WIN32)
	typedef unsigned __int64 CSTimer_t;
#elif defined(__QNX__)
	#include <stdint.h>
	typedef uint64_t CSTimer_t;
#elif defined(__RST__) || defined(__MBVS__)
    #include <stdint.h>
    typedef uint64_t CSTimer_t;
    extern uint32_t _ticks_per_sec;
#elif defined(VXWORKS)
	#include <time.h>
	typedef clock_t CSTimer_t;
#else
	#include <time.h>
	typedef struct timespec CSTimer_t;
#endif

void STTimer(CSTimer_t *This);

double STReset(CSTimer_t *This, double dt); /* возвращает время в секундах, прошедшее с предыдущего вызова Reset(...)*/
						/* при этом в качестве текущего времени берет текущее время+dt*/
						/* (полезно, если нужно сдвинуть момент засечки от текущего времени)*/

double STCheck(CSTimer_t *This); /* возвращает время в секундах, прошедшее с предыдущего вызова Reset(...)*/


#ifdef __cplusplus

}//extern "C"

class CSTimer  //Класс для измерения времени
{
	CSTimer_t t;

public:

	double Reset(double dt=0.0) /* возвращает время в секундах, прошедшее с предыдущего вызова Reset(...)*/
	{						/* при этом в качестве текущего времени берет текущее время+dt*/
							/* (полезно, если нужно сдвинуть момент засечки от текущего времени)*/

		return STReset(&t,dt);
	}

	double Check(void) /* возвращает время в секундах, прошедшее с предыдущего вызова Reset(...)*/
	{

		return STCheck(&t);
	}

	CSTimer(void)
	{
		STTimer(&t);
	}

	CSTimer(const CSTimer &st):t(st.t){}
	CSTimer operator=(const CSTimer &st){t=st.t;return *this;}
};

#endif /*defined(__cplusplus)*/

#endif /* !defined(AFX_STIMER_H__1423fdd4_3b9d_4283_8d66_b8dd7562bbd9__INCLUDED_)*/
