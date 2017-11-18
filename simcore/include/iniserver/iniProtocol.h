#ifndef  _MAIN_INI_PROTOCOL_H_
#define _MAIN_INI_PROTOCOL_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/*�������� �������������� ����� ini Server � ini Client
*/

#ifndef USA

/*���������***********************************************/
#define     RQ_GETFILE           0x2901
/*             1 �������� - ��� �����*/
#define     RQ_GETSECTION        0x2902
/*             1 �������� - ��� ������*/
#define     RQ_GETLINE           0x2903
/*             1 �������� - ��� ������*/
/*             2 �������� - ��� ����������*/
#define     RQ_WRITELINE         0x2904
/*             1 �������� - ������ ������� <���> = <��������>*/

#define     RP_FILE              0x2911
/*� ��������� ����� ����������� ����, �������������� \0*/
#define     RP_SECTION           0x2912
/*� ��������� ����� ����������� ����� ������, �������������� \0*/
#define     RP_LINE              0x2913
/*� ��������� ����� ����������� ����� ������, �������������� \0*/
#define     RP_WRITTEN           0x2914
/*� ��������� ������ �� ���������*/
#define     RP_ERROR             0x2915
/*� ��������� ������ �� ���������*/



/*������������ ������ ������******************************/
#define     LINE_SIZE            100

struct TINI_RQ              /*��������� ��������� ������� ������->������*/
{
   unsigned short RQId;          /*��� �������*/

   char           RQParam1[LINE_SIZE+1]; /*1 �������� �������*/
   char           RQParam2[LINE_SIZE+1]; /*2 �������� �������*/
};

struct TINI_RP              /*��������� ��������� ������ �� ������� � �������*/
{
   unsigned short RPId;          /*��� ������*/
};
#else /* USA */

/*���������***********************************************/
#define     RQ_GETFILE           0x7645
/*             1 �������� - ��� �����*/
#define     RQ_GETSECTION        0x7634
/*             1 �������� - ��� ������*/
#define     RQ_GETLINE           0x7683
/*             1 �������� - ��� ������*/
/*             2 �������� - ��� ����������*/
#define     RQ_WRITELINE         0x7665
/*             1 �������� - ������ ������� <���> = <��������>*/

#define     RP_FILE              0x7629
/*� ��������� ����� ����������� ����, �������������� \0*/
#define     RP_SECTION           0x7693
/*� ��������� ����� ����������� ����� ������, �������������� \0*/
#define     RP_LINE              0x7664
/*� ��������� ����� ����������� ����� ������, �������������� \0*/
#define     RP_WRITTEN           0x7625
/*� ��������� ������ �� ���������*/
#define     RP_ERROR             0x7677
/*� ��������� ������ �� ���������*/



/*������������ ������ ������******************************/
#define     LINE_SIZE            140

struct TINI_RQ              /*��������� ��������� ������� ������->������*/
{
   unsigned int RQId;          /*��� �������*/

   char           RQParam1[LINE_SIZE+1]; /*1 �������� �������*/
   char           RQParam2[LINE_SIZE+1]; /*2 �������� �������*/
};

struct TINI_RP              /*��������� ��������� ������ �� ������� � �������*/
{
   unsigned int RPId;          /*��� ������*/
};

#endif /* USA */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* _MAIN_INI_PROTOCOL_H_ */
