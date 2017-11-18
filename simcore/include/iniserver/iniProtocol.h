#ifndef  _MAIN_INI_PROTOCOL_H_
#define _MAIN_INI_PROTOCOL_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*Протокол взаимодействия между ini Server и ini Client
*/

#ifndef USA

/*Константы***********************************************/
#define     RQ_GETFILE           0x2901
/*             1 Параметр - имя файла*/
#define     RQ_GETSECTION        0x2902
/*             1 Параметр - имя секции*/
#define     RQ_GETLINE           0x2903
/*             1 Параметр - имя секции*/
/*             2 Параметр - имя переменной*/
#define     RQ_WRITELINE         0x2904
/*             1 Параметр - строка целиком <имя> = <значение>*/

#define     RP_FILE              0x2911
/*к сообщению сзади добавляется файл, оканчивающийся \0*/
#define     RP_SECTION           0x2912
/*к сообщению сзади добавляется текст секции, оканчивающийся \0*/
#define     RP_LINE              0x2913
/*к сообщению сзади добавляется текст строки, оканчивающийся \0*/
#define     RP_WRITTEN           0x2914
/*К сообщению ничего не приложено*/
#define     RP_ERROR             0x2915
/*К сообщению ничего не приложено*/



/*Максимальный размер строки******************************/
#define     LINE_SIZE            100

struct TINI_RQ              /*Структура сообщения запроса Клиент->Сервер*/
{
   unsigned short RQId;          /*Код запроса*/

   char           RQParam1[LINE_SIZE+1]; /*1 Параметр запроса*/
   char           RQParam2[LINE_SIZE+1]; /*2 Параметр запроса*/
};

struct TINI_RP              /*Структура сообщения ответа от сервера к клиенту*/
{
   unsigned short RPId;          /*Код ответа*/
};
#else /* USA */

/*Константы***********************************************/
#define     RQ_GETFILE           0x7645
/*             1 Параметр - имя файла*/
#define     RQ_GETSECTION        0x7634
/*             1 Параметр - имя секции*/
#define     RQ_GETLINE           0x7683
/*             1 Параметр - имя секции*/
/*             2 Параметр - имя переменной*/
#define     RQ_WRITELINE         0x7665
/*             1 Параметр - строка целиком <имя> = <значение>*/

#define     RP_FILE              0x7629
/*к сообщению сзади добавляется файл, оканчивающийся \0*/
#define     RP_SECTION           0x7693
/*к сообщению сзади добавляется текст секции, оканчивающийся \0*/
#define     RP_LINE              0x7664
/*к сообщению сзади добавляется текст строки, оканчивающийся \0*/
#define     RP_WRITTEN           0x7625
/*К сообщению ничего не приложено*/
#define     RP_ERROR             0x7677
/*К сообщению ничего не приложено*/



/*Максимальный размер строки******************************/
#define     LINE_SIZE            140

struct TINI_RQ              /*Структура сообщения запроса Клиент->Сервер*/
{
   unsigned int RQId;          /*Код запроса*/

   char           RQParam1[LINE_SIZE+1]; /*1 Параметр запроса*/
   char           RQParam2[LINE_SIZE+1]; /*2 Параметр запроса*/
};

struct TINI_RP              /*Структура сообщения ответа от сервера к клиенту*/
{
   unsigned int RPId;          /*Код ответа*/
};

#endif /* USA */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _MAIN_INI_PROTOCOL_H_ */
