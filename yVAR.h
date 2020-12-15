/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_HGUARD
#define YVAR_HGUARD loaded


char      yVAR_expstr   [500];
char      yVAR_actstr   [500];
char      yVAR_modstr   [500];
typedef   const char  cchar;

/*===[[ FUNCTION PROTOTYPES ]]================================================*/

char*      /* ---- : return library versioning information -------------------*/
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

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_ustring (     /*  PURPOSE = complex string testing for yUNIT             */
      cchar    *a_test,          /*  name of the test                         */
      cchar    *a_expect,        /*  expected result                          */
      cchar    *a_actual)        /*  actual result                            */
;


char*      /*----: return the modified expected string -----------------------*/
yVAR_modded        (void);

char*      /*----: return the modified expected string -----------------------*/
yVAR_actual        (void);

char*      /*----: return the modified expected string -----------------------*/
yVAR_expect        (void);

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_integer(      /*  PURPOSE = STANDARD INTEGER TESTING (for yUNIT+)        */
      char     *a_test,          /*  name of the test                         */
      long long a_expect,        /*  expected result                          */
      long long a_actual)        /*  actual result                            */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_pointer(      /*  PURPOSE = STANDARD POINTER TESTING (for yUNIT+)        */
      char     *a_test,          /*  name of the test                         */
      void     *a_expect,        /*  expected result                          */
      void     *a_actual)        /*  actual result                            */
;

int                /*  return  = pos=good, neg=bad, 0=unknown                 */
yVAR_real (        /*  PURPOSE = STANDARD REAL NUM TESTING (for yUNIT+)       */
      char     *a_test,          /*  name of the test                         */
      double    a_expect,        /*  expected result                          */
      double    a_actual)        /*  actual result                            */
;

void
yVAR_hex (
      int       a_range,         /*  how far off can it be                    */
      char     *a_expect,        /*  expected result                          */
      char     *a_actual)        /*  actual result                            */
;

#endif
/*===[[ END ]]================================================================*/
