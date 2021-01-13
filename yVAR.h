/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_HGUARD
#define YVAR_HGUARD loaded


char      yVAR_expstr   [500];
char      yVAR_actstr   [500];
char      yVAR_modstr   [500];
typedef   const char  cchar;
typedef   long long   llong;

/*===[[ FUNCTION PROTOTYPES ]]================================================*/

char*     
yVAR_version       (void);

char
yVAR_debug         (char a_flag);


int        /*----: standard regex pattern testing ----------------------------*/
yVAR_regx (        /*  PURPOSE = STANDARD STRING REGEX PATTERN TESTING        */
      char     *a_format,        /*  requested format for testing             */
      char     *a_value)         /*  variable value to test                   */
;



/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yVAR_string             (cchar *a_test, cchar *a_expect, cchar *a_actual);
char        yVAR_round              (cchar *a_test, cchar *a_expect, cchar *a_actual);
char        yVAR_results            (char *a_exp, char *a_act, char *a_mod, char *a_fexp, char *a_fact);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yVAR_integer            (char *a_test, llong a_expect, llong a_actual);
char        yVAR_pointer            (char *a_test, void *a_expect, void *a_actual);
char        yVAR_real               (char *a_test, double a_expect, double a_actual);




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
