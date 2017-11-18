#ifndef  _TMSPY_API_H_
#define  _TMSPY_API_H_


#include "TMSpyLL.h"

#ifdef __cplusplus
extern "C"
{
#endif


extern CTMLL tmSpyLL_;

#if defined(__QNX__)
void TMSpyShow1(void);
#endif /*defined(__QNX__)*/

extern void TMSpy5Hz(void);
extern unsigned int TMSpyReceive(unsigned char *msgId /*можно NULL*/, 
								 unsigned int *dataLen /*можно NULL*/, 
								 unsigned char *data /*можно NULL*/);

extern char TMSpySend(unsigned char msgId, unsigned int dataLen, unsigned char *data);
extern void TMSpy5HzEx(CTMLL *tmSpyLL);
extern unsigned int TMSpyReceiveEx(CTMLL *tmSpyLL,
								   unsigned char *msgId /*можно NULL*/,
								   unsigned int *dataLen /*можно NULL*/,
								   unsigned char *data /*можно NULL*/);
extern char TMSpySendEx(CTMLL *tmSpyLL, unsigned char msgId, unsigned int dataLen, 
						unsigned char *data);

#ifdef __cplusplus
}
#endif

#endif  /*_TMSPY_API_H_*/
