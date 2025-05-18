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

char*     
yVAR_version       (void);

char
yVAR_debug         (char a_flag);


int        /*----: standard regex pattern testing ----------------------------*/
yVAR_regex (        /*  PURPOSE = STANDARD STRING REGEX PATTERN TESTING        */
      char     *a_format,        /*  requested format for testing             */
      char     *a_value)         /*  variable value to test                   */
;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yVAR_string             (cchar *a_test, cchar *a_expect, cchar *a_actual);
char        yVAR_round              (cchar *a_test, cchar *a_expect, cchar *a_actual);
char        yVAR_results            (char *a_exp, char *a_act, char *a_mod, char *a_fexp, char *a_fact);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yVAR_char               (char a_test [LEN_TERSE], uchar a_expect, uchar a_actual);
char        yVAR_integer            (char a_test [LEN_TERSE], llong a_expect, llong a_actual);
char        yVAR_pointer            (char a_test [LEN_TERSE], void *a_expect, void *a_actual);
char        yVAR_real               (char a_test [LEN_TERSE], ldouble a_expect, ldouble a_actual);

char        yVAR_chars              (char a_test [LEN_TERSE], uchar a_actual);
char        yVAR_ints               (char a_test [LEN_TERSE], llong a_actual);



char*      /*----: return the modified expected string -----------------------*/
yVAR_modded        (void);

char*      /*----: return the modified expected string -----------------------*/
yVAR_actual        (void);

char*      /*----: return the modified expected string -----------------------*/
yVAR_expect        (void);



void
yVAR_hex (
      int       a_range,         /*  how far off can it be                    */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
;

#endif
/*===[[ END ]]================================================================*/
