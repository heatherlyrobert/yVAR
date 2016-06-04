/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YVAR_priv_hguard
#define YVAR_priv_hguard loaded

#define    _GNU_SOURCE          /* to allow asprintf()                        */
#include <stdio.h>        /* printf(), snprintf()                             */
#include <stdlib.h>
#include <string.h>
#include <regex.h>        /* regcomp(), regexec(), regfree()                  */


#include    <yLOG.h>                    /* heatherly program logger            */
#include    "yVAR.h"



typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
};
extern  tLOCAL its;
#define     DEBUG_YVAR     if (its.debug == 'y')


char        yVAR_testquiet     (void);
char        yVAR_testloud      (void);
char*       yVAR_getter        (char *a_question, int a_num);





#endif
