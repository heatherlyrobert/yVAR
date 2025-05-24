/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_HGUARD
#define YVAR_HGUARD loaded


#include <ySTR_solo.h>


extern    char      yVAR_expstr   [500];
extern    char      yVAR_actstr   [500];
extern    char      yVAR_modstr   [500];
typedef   unsigned char  uchar;
typedef   const char     cchar;
typedef   long long      llong;
typedef   long double    ldouble;

/*===[[ FUNCTION PROTOTYPES ]]================================================*/



/*===[[ yVAR_base.c ]]========================================================*/
/*········· ´······················ ´·········································*/
char*       yVAR_version            (void);
char        yVAR_debug              (char a_flag);



/*===[[ yVAR_num.c ]]=========================================================*/
/*········· ´······················ ´·········································*/
char        yVAR_char               (char a_test [LEN_TERSE], uchar a_expect, uchar a_actual);
char        yVAR_chars              (char a_test [LEN_TERSE], uchar a_actual);
char        yVAR_integer            (char a_test [LEN_TERSE], llong a_expect, llong a_actual);
char        yVAR_ints               (char a_test [LEN_TERSE], llong a_actual);
char        yVAR_pointer            (char a_test [LEN_TERSE], void *a_expect, void *a_actual);
char        yVAR_ptrs               (char a_test [LEN_TERSE], void *a_actual);
char        yVAR_real               (char a_test [LEN_TERSE], ldouble a_expect, ldouble a_actual);
char        yVAR_reals              (char a_test [LEN_TERSE], ldouble a_actual);



/*===[[ yVAR_string.c ]]======================================================*/
/*········· ´······················ ´·········································*/
char        yVAR_string             (char a_test [LEN_TERSE], char a_expect [LEN_RECD], char a_actual [LEN_RECD]);
char        yVAR_strs               (char a_test [LEN_TERSE], char a_actual [LEN_RECD]);
char        yVAR_round              (char a_test [LEN_TERSE], char a_expect [LEN_RECD], char a_actual [LEN_RECD]);
char        yVAR_yunit              (char a_expect [LEN_RECD], char a_actual [LEN_RECD], char r_modify [LEN_RECD]);



/*===[[ yVAR_regex.c ]]=======================================================*/
/*········· ´······················ ´·········································*/
char        yVAR_regex              (char a_format [LEN_TERSE], char a_regex [LEN_RECD], char a_actual [LEN_RECD]);
char        yVAR_regexs             (char a_test [LEN_TERSE], char a_actual [LEN_RECD]);



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yVAR_results            (char *a_exp, char *a_act, char *a_mod, char *a_fexp, char *a_fact);
char*       yVAR_modded             (void);
char*       yVAR_actual             (void);
char*       yVAR_expect             (void);



void        yVAR_hex (int a_range, char *a_expect, char *a_actual);


#endif
/*===[[ END ]]================================================================*/
