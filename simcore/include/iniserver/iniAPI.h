#ifndef   _MAIN_INI_API_H_
#define  _MAIN_INI_API_H_

#include "iniProtocol.h"

#ifdef __cplusplus
#include <map>
#include <vector>
#include <string>

using namespace std;

typedef  map<string, string, less<string> > iniTable_row_t;
typedef  map<int, iniTable_row_t, less<int> > iniTable_map_t;

extern "C"
{
#else

typedef  struct
{
	char * curPos;
	char * sectionBegin;
	char * sectionEnd;
	struct TINIAPI_RP_SECTION *section;
	char header[20][101];
	int headerNum;
}iniTable_map_t;

#endif 

/*Функции для получения информации от ини-сервера*/

  /*Получить строку*/
int ini_ReadString(const char *hostname, const char *section, const char *varname, char *value);

  /*Получить целое значение*/
int ini_ReadInteger(const char *hostname, const char *section, const char *varname, int *value);

  /*Получить значение с плавающей точкой*/
int ini_ReadDouble(const char *hostname, const char *section, const char *varname, double *value);


   /*Получить секцию*/
int ini_ReadSection(const char *hostname, const char *section, iniTable_map_t *iniTable);


#ifdef __cplusplus
}  /*Конец модификатора Extern "C"*/
#else

int ini_ReadSectionNext(iniTable_map_t*iniTable);

int ini_ReadSectionString(iniTable_map_t *iniTable, const char *varname, char *value);
int ini_ReadSectionInteger(iniTable_map_t *iniTable, const char *varname, int *value);
int ini_ReadSectionDouble(iniTable_map_t *iniTable, const char *varname, double *value);

#endif

#endif  /*_MAIN_INI_API_H_*/
